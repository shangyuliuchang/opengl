#include<GL/freeglut.h>
#include<math.h>
#include<Windows.h>

struct recData
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
};

class draw {
public:
	static void rec(recData* data) {
		glBegin(GL_LINES);
		glVertex2f(data->x1, data->y1);
		glVertex2f(data->x2, data->y2);
		glVertex2f(data->x2, data->y2);
		glVertex2f(data->x3, data->y3);
		glVertex2f(data->x3, data->y3);
		glVertex2f(data->x4, data->y4);
		glVertex2f(data->x4, data->y4);
		glVertex2f(data->x1, data->y1);
		glEnd();
	}
};

class car {
public:
	float x, y, angle, type;
	float width = 0.05, length = 0.1;
	car(int type_) {
		x = y = angle = 0;
		type = type_;
	}
	void display() {
		if (type == 0) {
			recData recD;
			recD.x1 = x + sin(angle)*width + cos(angle)*length;
			recD.x2 = x - sin(angle)*width + cos(angle)*length;
			recD.x3 = x - sin(angle)*width - cos(angle)*length;
			recD.x4 = x + sin(angle)*width - cos(angle)*length;
			recD.y1 = y + cos(angle)*width + sin(angle)*length;
			recD.y2 = y - cos(angle)*width + sin(angle)*length;
			recD.y3 = y - cos(angle)*width - sin(angle)*length;
			recD.y4 = y + cos(angle)*width - sin(angle)*length;
			draw::rec(&recD);
		}
	}
};
car firstcar(0);
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	firstcar.display();
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutCreateWindow("the Graph of Function!");
	glClearColor(0, 0, 0, 1);
	glutIdleFunc(&display);
	glutMainLoop();
	return 0;
}