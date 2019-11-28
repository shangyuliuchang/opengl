#include <windows.h> 
#include <GL/freeglut.h> 
#define PI 3.1415
#include <math.h>
void display() {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw scene */
   //glutWireTeapot(.5); 
   /* flush drawing routines to the window */
	float x, y, z, angle;
	//glPushMatrix();
	//glTranslatef(300,200,0);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	for (angle = 0.0; angle < 2 * PI; angle += 0.01)
	{
		x = 1 * sin(angle);
		y = 1 * cos(angle);
		glVertex2f(x, y);
	}
	glEnd();
	//glPopMatrix();
	glFlush();
}
int main(int argc, char *argv[]) {
	/* initialize GLUT, using any commandline parameters passed to the program */
	glutInit(&argc, argv);
	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB);
	/* create and set up a window */
	glutCreateWindow("hello, teapot!");
	glutDisplayFunc(&display);
	/* tell GLUT to wait for events */
	glutMainLoop();
	return 0;
}