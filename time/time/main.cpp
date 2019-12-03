#include<GL/freeglut.h>
#include<math.h>
#include<Windows.h>

#define PI 3.1415926535

struct recData
{
	int number;
	float x[100], y[100];
};

class draw {
public:
	static void drawlines(recData* data) {
		glBegin(GL_LINES);
		for (int i = 0; i < data->number - 1; i++) {
			glVertex2f(data->x[i], data->y[i]);
			glVertex2f(data->x[i+1], data->y[i+1]);
		}
		glVertex2f(data->x[0], data->y[0]);
		glVertex2f(data->x[data->number-1], data->y[data->number - 1]);
		glEnd();
	}
	static void transform(float x, float y, float angle, float orix, float oriy, float* truex, float* truey) {
		*truex = x - oriy * sin(angle) + orix * cos(angle);
		*truey = y + oriy * cos(angle) + orix * sin(angle);
	}
};
class parking {
public:
	static void draw() {
		glBegin(GL_LINES);
		for (float x = -0.6f; x <= 0.6f; x += 0.2) {
			glVertex2f(x, -1.0f);
			glVertex2f(x, -0.6f);
		}
		for (float x = -0.6f; x <= 0.6f; x += 0.2) {
			glVertex2f(x, 1.0f);
			glVertex2f(x, 0.6f);
		}
		glEnd();
		recData cen;
		cen.x[0] = -0.6f; cen.y[0] = -0.2f;
		cen.x[1] = 0.6f; cen.y[1] = -0.2f;
		cen.x[2] = 0.6f; cen.y[2] = 0.2f;
		cen.x[3] = -0.6f; cen.y[3] = 0.2f;
		draw::drawlines(&cen);
	}
};
class car {
public:
	float x, y, angle, type;
	float width = 0.1, length = 0.2;
	car(int type_) {
		x = -0.8;
		y = -1.1;
		angle = PI / 2;
		type = type_;
	}
	void display() {
		if (type == 0) {
			recData recD;
			recD.number = 4;
			for (int i = 0; i < 4; i++) {
				draw::transform(x, y, angle, length / 2 * (i == 0 || i == 3 ? 1 : -1), width / 2 * (i < 2 ? 1 : -1), &recD.x[i], &recD.y[i]);
			}
			draw::drawlines(&recD);
		}
	}
	void move() {
		y += 0.001f*sin(angle);
		x += 0.001f*cos(angle);
	}
};
car firstcar(0);
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	firstcar.display();
	firstcar.move();
	parking::draw();
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