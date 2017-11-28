#include <GL/glut.h>
#include <iostream>
#include "vector3D.h" //truc d'aurel avec tout dedans
#include "app.h"
#include "timing.h"

Vector3D *vect = new Vector3D(0,40,0);//In heap for long time use (return pointer)


class vectDemo : public Application
{

public:
    /** Creates a new demo object. */
    vectDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Update the particle positions. */
    virtual void update();

    /** Display the particle positions. */
    virtual void display();

    /** Handle a mouse click. */
    virtual void mouse(int button, int state, int x, int y);

    /** Handle a keypress. */
    virtual void key(unsigned char key);
};

const char* vectDemo::getTitle()
{
    return "DiceShard->Vecteurs";
}

void vectDemo::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON) {
        exit(0);
    }
}

void vect::key(unsigned char key)
{
    if (c == 27) {
        exit(0);
    }
}

void VectDemo::update()
{
    // Find the duration of the last frame in seconds
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;
    vect->setY() = vect.getY()+1;
    Application::update();
}

void FireworksDemo::display()
{
    const static cyclone::real size = 0.1f;

    // Clear the viewport and set the camera direction
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 4.0, 10.0,  0.0, 4.0, 0.0,  0.0, 1.0, 0.0);

    // Render each firework in turn
    glBegin(GL_QUADS);

    glVertex3f(0, 0, 0);
        glVertex3f(vect->getX(), vect->getY(), vect->getZ());
    glEnd();
}

Application* getApplication()
{
    return new vectDemo();
}