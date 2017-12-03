#include "inc.h" //Include global
#include <GL/glut.h>
#include "app.h"
#include <iostream>
#include <stdio.h>
#include "timing.h" 


class PewpewApp : public Application
{

enum ShotType
    {
        UNUSED = 0,
        SHOT,
        CATAPULT
    };

    struct ShotsFired
    {
        Particle particle;
        ShotType type;
        unsigned startTime;

        void render()
        {
            Vector3D position;
            particle.getPosition(&position);

            glColor3f(255, 255, 255);
            glPushMatrix();
            glTranslatef(position.getX(), position.getY(), position.getZ());
            glutSolidSphere(0.3f, 5, 4);
            glPopMatrix();
        }
    };

    const static int shotNumber =100;
    ShotsFired shots[shotNumber];
    ShotType currentShotType;
    void fire();

public:

    virtual const char* getTitle();

    virtual void update();

    virtual void display();

    virtual void mouse(int button, int state, int x, int y);

    virtual void key(unsigned char key);
};

const char* PewpewApp::getTitle()
{
    return "DiceShard > PewPew";
}

void PewpewApp::fire()
{
    ShotsFired *shot;
   for (shot = shots; shot < shots+shotNumber; shot++)
    {
        if (shot->type == UNUSED) break;
    }

    // si pas de munition / on ne tire pas
    if (shot >= shots+shotNumber) return;

    switch(currentShotType)
    {
    case SHOT:
        shot->particle.setMass(2.0f); // 2.0kg
        shot->particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
        shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);
        shot->particle.setDamping(0.99f);
        break;

    case CATAPULT:
        shot->particle.setMass(200.0f); // 200.0kg
        shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
        shot->particle.setAcceleration(0.0f, -20.0f, 0.0f);
        shot->particle.setDamping(0.99f);
        break;
    }

    shot->particle.setPosition(0.0f, 1.5f, 0.0f);
    shot->startTime = TimingData::get().lastFrameTimestamp;
    shot->type = currentShotType;
    shot->particle.clearAccumulator();
}

void PewpewApp::update()
{
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    for (ShotsFired *shot = shots; shot < shots+shotNumber; shot++)
    {
        if (shot->type != UNUSED)
        {
            shot->particle.integrate(duration);
            if (shot->particle.getPosition().getY() < 0.0f ||
                shot->startTime+5000 < TimingData::get().lastFrameTimestamp ||
                shot->particle.getPosition().getZ() > 200.0f)
            {
                shot->type = UNUSED;
            }
        }
    }

    Application::update();
}

void PewpewApp::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(80.0, 25.0, 80.0,  0.0, 25.0, 70.0,  0.0, 1.0, 0.0);

    
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
               glVertex3f(-5.0f, 0.0f, 0.0f); // vertex 1
               glVertex3f(5.0f, 0.0f, 0.0f); // vertex 2
               glVertex3f(5.0f, 0.0f, 150.0f); // vertex 3
               glVertex3f(-5.0f, 0.0f, 150.0f); // vertex 4
    glEnd();

    for (ShotsFired *shot = shots; shot < shots+shotNumber; shot++)
    {
        if (shot->type != UNUSED)
        {
            shot->render();
        }
    }
}

void PewpewApp::mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) fire();
}

void PewpewApp::key(unsigned char key)
{
    switch(key)
    {
    case '1': currentShotType = SHOT; break;
    case '2': currentShotType = CATAPULT; break;
    }
}

Application* getApplication()
{
    return new PewpewApp();
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