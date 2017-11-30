#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "inc.h" //Include global
#include "app.h"
#include "timing.h"


class Firework : public Particle
{
public:
    /** Fireworks have an integer type, used for firework rules. */
    unsigned type;

    /**
     * The age of a firework determines when it detonates. Age gradually
     * decreases, when it passes zero the firework delivers its payload.
     * Think of age as fuse-left.
     */
    real age;

    /**
     * Updates the firework by the given duration of time. Returns true
     * if the firework has reached the end of its life and needs to be
     * removed.
     */
    bool update(real duration)
    {
        // Update our physical state
        integrate(duration);

        // We work backwards from our age to zero.
        age -= duration;
        return (age < 0) || (position.getY() < 0);
    }
};

/**
 * Firework rules control the length of a firework's fuse and the
 * particles it should evolve into.
 */
struct FireworkRule
{
    /** The type of firework that is managed by this rule. */
    unsigned type;

    /** The minimum length of the fuse. */
    real minAge;

    /** The maximum legnth of the fuse. */
    real maxAge;

    /** The minimum relative velocity of this firework. */
    Vector3D minVelocity;

    /** The maximum relative velocity of this firework. */
    Vector3D maxVelocity;

    /** The damping of this firework type. */
    real damping;

    /**
     * The payload is the new firework type to create when this
     * firework's fuse is over.
     */
    struct Payload
    {
        /** The type of the new particle to create. */
        unsigned type;

        /** The number of particles in this payload. */
        unsigned count;

        /** Sets the payload properties in one go. */
        void set(unsigned type, unsigned count)
        {
            Payload::type = type;
            Payload::count = count;
        }
    };

    /** The number of payloads for this firework type. */
    unsigned payloadCount;

    /** The set of payloads. */
    Payload *payloads;

    FireworkRule()
    :
    payloadCount(0),
    payloads(NULL)
    {
    }

    void init(unsigned payloadCount)
    {
        FireworkRule::payloadCount = payloadCount;
        payloads = new Payload[payloadCount];
    }

    ~FireworkRule()
    {
        if (payloads != NULL) delete[] payloads;
    }

    /**
     * Set all the rule parameters in one go.
     */
    void setParameters(unsigned type, real minAge, real maxAge,
        const Vector3D &minVelocity, const Vector3D &maxVelocity,
        real damping)
    {
        FireworkRule::type = type;
        FireworkRule::minAge = minAge;
        FireworkRule::maxAge = maxAge;
        FireworkRule::minVelocity = minVelocity;
        FireworkRule::maxVelocity = maxVelocity;
        FireworkRule::damping = damping;
    }

    /**
     * Creates a new firework of this type and writes it into the given
     * instance. The optional parent firework is used to base position
     * and velocity on.
     */
    void create(Firework *firework, const Firework *parent = NULL) const
    {
        firework->type = type;
        firework->age = 5;//crandom.randomReal(minAge, maxAge);

        Vector3D vel;
        if (parent) {
            // The position and velocity are based on the parent.
            firework->setPosition(parent->getPosition());
            vel += parent->getVelocity();
        }
        else
        {
            Vector3D start;
            int x = 2;//(int)crandom.randomInt(3) - 1;
            start.setX(5.0f * real(x));
            firework->setPosition(start);
        }

        vel = Vector3D(1,1,1);/*crandom.randomVector(minVelocity, maxVelocity);*/;
        firework->setVelocity(vel);

        // We use a mass of one in all cases (no point having fireworks
        // with different masses, since they are only under the influence
        // of gravity).
        firework->setMass(1);

        firework->setDamping(damping);

        firework->setAcceleration(Vector3D(0,-9.81,0));

        firework->clearAccumulator();
    }
};



class FireWorkApp : public Application
{

 /**
     * Holds the maximum number of fireworks that can be in use.
     */
    const static unsigned maxFireworks = 1024;

    /** Holds the firework data. */
    Firework fireworks[maxFireworks];

    /** Holds the index of the next firework slot to use. */
    unsigned nextFirework;

    /** And the number of rules. */
    const static unsigned ruleCount = 9;

    /** Holds the set of rules. */
    FireworkRule rules[ruleCount];

    /** Dispatches a firework from the origin. */
    void create(unsigned type, const Firework *parent=NULL);

    /** Dispatches the given number of fireworks from the given parent. */
    void create(unsigned type, unsigned number, const Firework *parent);

    /** Creates the rules. */
    void initFireworkRules();

    void reset();

public:
    /** Creates a new demo object. */
    FireWorkApp();
    ~FireWorkApp();

    /** Sets up the graphic rendering. */
    virtual void initGraphics();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Update the particle positions. */
    virtual void update();

    /** Display the particle positions. */
    virtual void display();

    /** Handle a keypress. */
    virtual void key(unsigned char key);
};

FireWorkApp::FireWorkApp()
:
nextFirework(0)
{
    // Make all shots unused
    for (Firework *firework = fireworks;
         firework < fireworks+maxFireworks;
         firework++)
    {
        firework->type = 0;
    }

    // Create the firework types
    initFireworkRules();
}

FireWorkApp::~FireWorkApp()
{} //Destructeur

void FireWorkApp::initFireworkRules()
{
    // Go through the firework types and create their rules.
    rules[0].init(2);
    rules[0].setParameters(
        1, // type
        0.5f, 1.4f, // age range
        Vector3D(-5, 25, -5), // min velocity
        Vector3D(5, 28, 5), // max velocity
        0.1 // damping
        );
    rules[0].payloads[0].set(3, 5);
    rules[0].payloads[1].set(5, 5);

    rules[1].init(1);
    rules[1].setParameters(
        2, // type
        0.5f, 1.0f, // age range
        Vector3D(-5, 10, -5), // min velocity
        Vector3D(5, 20, 5), // max velocity
        0.8 // damping
        );
    rules[1].payloads[0].set(4, 2);

    rules[2].init(0);
    rules[2].setParameters(
        3, // type
        0.5f, 1.5f, // age range
        Vector3D(-5, -5, -5), // min velocity
        Vector3D(5, 5, 5), // max velocity
        0.1 // damping
        );

    rules[3].init(0);
    rules[3].setParameters(
        4, // type
        0.25f, 0.5f, // age range
        Vector3D(-20, 5, -5), // min velocity
        Vector3D(20, 5, 5), // max velocity
        0.2 // damping
        );

    rules[4].init(1);
    rules[4].setParameters(
        5, // type
        0.5f, 1.0f, // age range
        Vector3D(-20, 2, -5), // min velocity
        Vector3D(20, 18, 5), // max velocity
        0.01 // damping
        );
    rules[4].payloads[0].set(3, 5);

    rules[5].init(0);
    rules[5].setParameters(
        6, // type
        3, 5, // age range
        Vector3D(-5, 5, -5), // min velocity
        Vector3D(5, 10, 5), // max velocity
        0.95 // damping
        );

    rules[6].init(1);
    rules[6].setParameters(
        7, // type
        4, 5, // age range
        Vector3D(-5, 50, -5), // min velocity
        Vector3D(5, 60, 5), // max velocity
        0.01 // damping
        );
    rules[6].payloads[0].set(8, 10);

    rules[7].init(0);
    rules[7].setParameters(
        8, // type
        0.25f, 0.5f, // age range
        Vector3D(-1, -1, -1), // min velocity
        Vector3D(1, 1, 1), // max velocity
        0.01 // damping
        );

    rules[8].init(0);
    rules[8].setParameters(
        9, // type
        3, 5, // age range
        Vector3D(-15, 10, -5), // min velocity
        Vector3D(15, 15, 5), // max velocity
        0.95 // damping
        );
    // ... and so on for other firework types ...
}

void FireWorkApp::initGraphics()
{
    // Call the superclass
    Application::initGraphics();

    // But override the clear color
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

const char* FireWorkApp::getTitle()
{
    return "DiceShard->FireWorks";
}

void FireWorkApp::create(unsigned type, const Firework *parent)
{
    // Get the rule needed to create this firework
    FireworkRule *rule = rules + (type - 1);

    // Create the firework
    rule->create(fireworks+nextFirework, parent);

    // Increment the index for the next firework
    nextFirework = (nextFirework + 1) % maxFireworks;
}

void FireWorkApp::create(unsigned type, unsigned number, const Firework *parent)
{
    for (unsigned i = 0; i < number; i++)
    {
        create(type, parent);
    }
}

void FireWorkApp::key(unsigned char key)
{
    switch (key)
    {
    case '1': create(1, 1, NULL); break;
    case '2': create(2, 1, NULL); break;
    case '3': create(3, 1, NULL); break;
    case '4': create(4, 1, NULL); break;
    case '5': create(5, 1, NULL); break;
    case '6': create(6, 1, NULL); break;
    case '7': create(7, 1, NULL); break;
    case '8': create(8, 1, NULL); break;
    case '9': create(9, 1, NULL); break;
    }
}

void FireWorkApp::update()
{
    // Find the duration of the last frame in seconds
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    for (Firework *firework = fireworks;
         firework < fireworks+maxFireworks;
         firework++)
    {
        // Check if we need to process this firework.
        if (firework->type > 0)
        {
            // Does it need removing?
            if (firework->update(duration))
            {
                // Find the appropriate rule
                FireworkRule *rule = rules + (firework->type-1);

                // Delete the current firework (this doesn't affect its
                // position and velocity for passing to the create function,
                // just whether or not it is processed for rendering or
                // physics.
                firework->type = 0;

                // Add the payload
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

void FireWorkApp::display()
{
    const static real size = 0.1f;

    // Clear the viewport and set the camera direction
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 4.0, 10.0,  0.0, 4.0, 0.0,  0.0, 1.0, 0.0);

    // Render each firework in turn
    glBegin(GL_QUADS);
    for (Firework *firework = fireworks;
        firework < fireworks+maxFireworks;
        firework++)
    {
        // Check if we need to process this firework.
        if (firework->type > 0)
        {
            switch (firework->type)
            {
            case 1: glColor3f(1,0,0); break;
            case 2: glColor3f(1,0.5f,0); break;
            case 3: glColor3f(1,1,0); break;
            case 4: glColor3f(0,1,0); break;
            case 5: glColor3f(0,1,1); break;
            case 6: glColor3f(0.4f,0.4f,1); break;
            case 7: glColor3f(1,0,1); break;
            case 8: glColor3f(1,1,1); break;
            case 9: glColor3f(1,0.5f,0.5f); break;
            };

            Vector3D pos = firework->getPosition();
            glVertex3f(pos.getX()-size, pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, pos.getY()+size, pos.getZ());
            glVertex3f(pos.getX()-size, pos.getY()+size, pos.getZ());

            // Render the firework's reflection
            glVertex3f(pos.getX()-size, -pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, -pos.getY()-size, pos.getZ());
            glVertex3f(pos.getX()+size, -pos.getY()+size, pos.getZ());
            glVertex3f(pos.getX()-size, -pos.getY()+size, pos.getZ());
        }
    }
    glEnd();
}

Application* getApplication()
{
    return new FireWorkApp();
}

extern Application* getApplication();

// Store the global application object.
Application* app;

/**
 * Creates a window in which to display the scene.
 */
void createWindow(const char* title)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow(title);
}

/**
 * Called each frame to update the 3D scene. Delegates to
 * the application.
 */
void update()
{
    // Update the timing.
    TimingData::get().update();

    // Delegate to the application.
    app->update();
}

/**
 * Called each frame to display the 3D scene. Delegates to
 * the application.
 */
void display()
{
    app->display();
    // Update the displayed content.
    glFlush();
    glutSwapBuffers();
}

/**
 * Called when a mouse button is pressed. Delegates to the
 * application.
 */
void mouse(int button, int state, int x, int y)
{
    app->mouse(button, state, x, y);
}

/**
 * Called when the display window changes size.
 */
void reshape(int width, int height)
{
    app->resize(width, height);
}

/**
 * Called when a key is pressed.
 */
void keyboard(unsigned char key, int x, int y)
{
    // Note we omit passing on the x and y: they are rarely needed.
    app->key(key);
}

/**
 * Called when the mouse is dragged.
 */
void motion(int x, int y)
{
    app->mouseDrag(x, y);
}


int main(int argc, char** argv){


    // Set up GLUT and the timers
    glutInit(&argc, argv);
    TimingData::init();

    // Create the application and its window
    app = getApplication();
    createWindow(app->getTitle());

    // Set up the appropriate handler functions
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // Run the application
    app->initGraphics();
    glutMainLoop();

    // Clean up the application
    app->deinit();
    delete app;
    TimingData::deinit();
};