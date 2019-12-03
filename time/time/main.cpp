#include<GL/freeglut.h>
#include<math.h>
#include<Windows.h>

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutCreateWindow("the Graph of Function!");
	glClearColor(0, 0, 0, 1);
	//glutIdleFunc(&display);
	glutMainLoop();
	return 0;
}