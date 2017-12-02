#include "inc.h" //Include global
#include <GL/glut.h>
#include "app.h"
#include <iostream>
#include <stdio.h>
#include "timing.h"


class Firework : public Particle //Un feu d'artifice est un certain type de particule
{


public:
	//Type de feu
    int type;

    /**
    Temps avant explosion de notre feu d'artifice.
     */
    real age;

    /**
     * Mise a jour de l'état de la particule - vérification que le compte a rebours avant explosion est pas arrivé
     * et qu'elle a pas atteint le sol
     */
    bool update(real duration)
    {
        // Update de l'état de la particule
        integrate(duration);

        //maj du compte a rebours et vérification
        age -= duration;
        return (age < 0) || (position.getY() < -5);
    }
};

/**
 * Définition des caractéristiques des feux d'artifices
 * 
 */
struct FireworkRule
{
    int type;

    /* Damping de la particule */
    real damping;

    /**
     * Effet explosion de la particule
     */
    struct Payload
    {
        /** type de particule crée */
        int type;

        /** nombre de particules crées */
        int count;

      	/*setter*/
        void set(unsigned type, unsigned count)
        {
            Payload::type = type;
            Payload::count = count;
        }
    };

    /** nombre de payload par particule */
    int payloadCount;

    Payload *payloads;

    FireworkRule():payloadCount(0),payloads(NULL){}

    void init(unsigned payloadCount)
    {
        FireworkRule::payloadCount = payloadCount;
        payloads = new Payload[payloadCount];
    }

    ~FireworkRule()
    {
        if (payloads != NULL) delete[] payloads;
    }

    //setter
    void setParameters(unsigned type,real damping)
    {
        FireworkRule::type = type;
        FireworkRule::damping = damping;
    }

    /**
     * Crée le firework
     */
    void create(Firework *firework, const Firework *parent = NULL) const
    {
        firework->type = type;
        firework->age = rand()%2+1;

        Vector3D vel;
        if (parent) {
            //position et velocité par rapport a son parent
            firework->setPosition(parent->getPosition());
            vel += parent->getVelocity();
        }
        else //si pas de parent
        {
            Vector3D start;
            firework->setPosition(start);
        }

        vel = Vector3D (rand()%10-5,rand()%5+10,rand()%5);
        firework->setVelocity(vel);
        
        firework->setMass(1);

        firework->setDamping(damping);

        firework->setAcceleration(Vector3D(0,-9.81,0));

        firework->clearAccumulator();
    }
};



class FireWorkApp : public Application
{

    const static int maxFireworks = 1024;

    Firework fireworks[maxFireworks];

    int nextFirework;

    const static int ruleCount = 3;

    FireworkRule rules[ruleCount];

    void create(int type, const Firework *parent=NULL);

    void create(int type, int number, const Firework *parent);

    void initFireworkRules();

    void reset();

public:
    FireWorkApp();
    ~FireWorkApp();

    virtual void initGraphics();

    virtual const char* getTitle();

    virtual void update();

    virtual void display();

    virtual void key(unsigned char key);
};

FireWorkApp::FireWorkApp()
:
nextFirework(0)
{
    for (Firework *firework = fireworks;
         firework < fireworks+maxFireworks;
         firework++)
    {
        firework->type = 0;
    }

    initFireworkRules();
}

FireWorkApp::~FireWorkApp()
{} //Destructeur

void FireWorkApp::initFireworkRules()
{
    // Les regles regissant les particules.
    rules[0].init(2);
    rules[0].setParameters(
        1, // type
        0.1 // damping
        );
    rules[0].payloads[0].set(3, 5);
    rules[0].payloads[1].set(5, 5);

    rules[1].init(1);
    rules[1].setParameters(
        2, // type
        0.8 // damping
        );
    rules[1].payloads[0].set(2, 2);

    rules[2].init(0);
    rules[2].setParameters(
        3, // type
        0.1 // damping
        );
}

void FireWorkApp::initGraphics()
{
    Application::initGraphics(); //initgraphics depuis la superclasse
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); //On surcharge la couleur
}

const char* FireWorkApp::getTitle()
{
    return "DiceShard->FireWorks";
}

void FireWorkApp::create(int type, const Firework *parent)
{
    FireworkRule *rule = rules + (type - 1); //creation de l'application
    rule->create(fireworks+nextFirework, parent);
    nextFirework = (nextFirework + 1) % maxFireworks;
}

void FireWorkApp::create(int type, int number, const Firework *parent)
{
    for (unsigned i = 0; i < number; i++)
    {
        create(type, parent);
    }
}

void FireWorkApp::key(unsigned char key) //listener des touches
{
    switch (key) //ici chaque touche va creer un feu different
    {
    case '1': create(1, 1, NULL); break;
    case '2': create(2, 1, NULL); break;
    case '3': create(3, 1, NULL); break;
    }
}

void FireWorkApp::update()
{
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    for (Firework *firework = fireworks;
         firework < fireworks+maxFireworks;
         firework++)
    {
        if (firework->type > 0)
        {
            if (firework->update(duration))
            {
                FireworkRule *rule = rules + (firework->type-1);
                firework->type = 0;

                for (unsigned i = 0; i < rule->payloadCount; i++)
                {
                    FireworkRule::Payload * payload = rule->payloads + i;
                    create(payload->type, payload->count, firework);
                }
            }
        }
    }

    Application::update();
}

void FireWorkApp::display() //fonction pour afficher notre feu d'artifice
{
    const static real size = 0.1f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
    for (Firework *firework = fireworks;
        firework < fireworks+maxFireworks;
        firework++)
    {
        if (firework->type > 0)
        {
            switch (firework->type)
            {
            case 1: glColor3f(1,0,0); break;
            case 2: glColor3f(1,0.5f,0); break;
            case 3: glColor3f(0,1,1); break;
            };

            const Vector3D &pos = firework->getPosition();
            glVertex3f(pos.getX()-size, pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, pos.getY()+size, pos.getZ());
            glVertex3f(pos.getX()-size, pos.getY()+size, pos.getZ());           
        }
    }
    glEnd();
}

Application* getApplication()
{
    return new FireWorkApp();
}

extern Application* getApplication();

Application* app;

void createWindow(const char* title) //creation de la fenetre d'affichage
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow(title);
}


void update() 
{
    TimingData::get().update();
    app->update();
}


void display()
{
    app->display();
    // Update the displayed content.
    glFlush();
    glutSwapBuffers();
}


void mouse(int button, int state, int x, int y)
{
    app->mouse(button, state, x, y);
}


void reshape(int width, int height)
{
    app->resize(width, height);
}


void keyboard(unsigned char key, int x, int y)
{
    app->key(key);
}

void motion(int x, int y)
{
    app->mouseDrag(x, y);
}


int main(int argc, char** argv){

	srand(time(NULL));
    glutInit(&argc, argv);
    TimingData::init();

    app = getApplication();
    createWindow(app->getTitle());

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    app->initGraphics();
    glutMainLoop();

    app->deinit();
    delete app;
    TimingData::deinit();
};