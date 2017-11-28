#include <GL/glut.h>
#include <iostream>
#include "vector3D.h"

void render(void);

void keyboard(unsigned char c, int x, int y);

void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Simple GLUT Application");

	glutDisplayFunc(render);	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
}

void keyboard(unsigned char c, int x, int y) {
	if (c == 27) {
		exit(0);
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON) {
		exit(0);
	}
}

void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Vector3D vect;//In stack for short time use (return object)
    Vector3D *vect2 = new Vector3D(0,40,0);//In heap for long time use (return pointer)
    Vector3D *vect3 = new Vector3D(10,50,50);
	glBegin(GL_LINES);
 		glVertex3f(0, 0, 0);
  		glVertex3f(vect2->getX(), vect2->getY(), vect2->getZ());

  		glVertex3f(0, 0, 0);
  		glVertex3f(vect3->getX(), vect3->getY(), vect3->getZ());
	glEnd();


	glutSwapBuffers();
}