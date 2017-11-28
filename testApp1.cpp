#include <GL/glut.h>
#include <iostream>
#include "inc.h" //truc d'aurel avec tout dedans
#include "app.h"
#include "timing.h"

Vector3D *vect = new Vector3D(0.0f,40.0f,0.0f);//In heap for long time use (return pointer)

class VectDemo : public Application
{
void reset();
public:
    /** Creates a new demo object. */
    VectDemo();

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

VectDemo::VectDemo()
{

}

void VectDemo::reset(){
}

const char* VectDemo::getTitle()
{
    return "DiceShard->Vecteurs";
}

void VectDemo::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON) {
        exit(0);
    }
}

void VectDemo::key(unsigned char key)
{
     switch(key)
    {
    case '1': exit(0);
    }
}

void VectDemo::update()
{
    // Find the duration of the last frame in seconds
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;
    vect->setY(vect->getY()+1);
    Application::update();
}

void VectDemo::display()
{
    const static real size = 0.1f;

    // Clear the viewport and set the camera direction
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //gluLookAt(0.0, 4.0, 10.0,  0.0, 4.0, 0.0,  0.0, 1.0, 0.0);

    // Render each firework in turn
    glBegin(GL_QUADS);

    glVertex3f(0, 0, 0);
        glVertex3f(vect->getX(), vect->getY(), vect->getZ());
    glEnd();
}

Application* getApplication()
{
    return new VectDemo();
}

extern Application* getApplication();

// Store the global application object.
Application* app;

/**
 * Creates a window in which to display the scene.
 */
void createWindow(const char* title)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,320);
    glutInitWindowPosition(0,0);
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