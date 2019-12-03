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
		glVertex2f(data->x1, data->y1);glVertex2f(data->x2, data->y2);
		glVertex2f(data->x2, data->y2);glVertex2f(data->x3, data->y3);
		glVertex2f(data->x3, data->y3);glVertex2f(data->x4, data->y4);
		glVertex2f(data->x4, data->y4);glVertex2f(data->x1, data->y1);
		glEnd();
	}
	static void transform(float x, float y, float angle, float orix, float oriy, float* truex, float* truey) {
		*truex = x - oriy * sin(angle) + orix * cos(angle);
		*truey = y + oriy * cos(angle) + orix * sin(angle);
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
			draw::transform(x, y, angle, length / 2, width / 2, &recD.x1, &recD.y1);
			draw::transform(x, y, angle, length / -2, width / 2, &recD.x2, &recD.y2);
			draw::transform(x, y, angle, length / -2, width / -2, &recD.x3, &recD.y3);
			draw::transform(x, y, angle, length / 2, width / -2, &recD.x4, &recD.y4);
			draw::rec(&recD);
		}
	}
};
car firstcar(0);
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	firstcar.display();
	firstcar.angle += 0.01f;
	firstcar.x += 0.001f;
	glutSwapBuffers();
	Sleep(10);
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