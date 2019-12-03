#include<GL/freeglut.h>
int main() {
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