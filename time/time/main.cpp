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
	static car* cars[100];
	float x, y, angle, type, v;
	float width = 0.1, length = 0.2;
	int dir, state, position, out;
	car(int type_) {
		x = -0.8;
		y = -1.1;
		angle = PI / 2;
		type = type_;
		v = 0.005f;
		dir = 0;
		state = 0;
		position = 0;
		out = 0;
	}
	static void generate(car** cars, int n) {
		for (int i = 0; i < n; i++) {
			cars[i] = new car(0);
		}
	}
	void goout() {
		out = 1;
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
		y += v * sin(angle);
		x += v * cos(angle);

		if (dir == 0 && state == 0 && y > -0.5f && y < -0.49f) {
			state = 2;
		}
		if (dir == 3 && state == 0 && x > 0.7f && x < 0.71f) {
			state = 1;
		}
		if (dir == 0 && state == 0 && y > 0.3f && y < 0.31f) {
			state = 1;
		}
		if (dir == 1 && state == 0 && x<-0.7f && x>-0.71f) {
			state = 2;
		}
		if (dir == 2 && state == 0 && y <= 0.5f && y >= 0.49f) {
			state = 2;
		}

		if (y > 1.1f) {
			v = 0;
		}
		if (dir == 2 && state == 0 && y <= -0.8f) {
			v = 0;
			if (out == 1) {
				v = 0.005f;
				dir = 0;
				state = 0;
				angle = PI / 2;
			}
		}
		if (dir == 0 && state == 0 && y >= 0.8f && x > -0.6f) {
			v = 0;
			if (out == 1) {
				v = 0.005f;
				dir = 2;
				state = 0;
				angle = 3.0f / 2.0f * PI;
			}
		}

		if ((state == 1 || state == 2) && fabs((angle)-((dir - state * 2 + 4) % 4)*PI / 2) <= 0.1f) {
			dir = (dir - state * 2 + 7) % 4;
			state = 0;
			angle = ((dir + 1) % 4)*PI / 2;
		}
		
		if (state == 2) {
			angle -= v * 10;
		}
		if (state == 1) {
			angle += v * 10;
		}

		if (out==0 && position < 6 && dir == 3 && state == 0 && x >= -0.4f + position * 0.2f && x <= -0.39f + position * 0.2f) {
			dir = 1;
			state = 1;
			angle = (angle + PI);
			if (angle >= 2 * PI) {
				angle -= PI * 2;
			}
		}
		if (out==0 && position >= 6 && dir == 1 && state == 0 && x >= 0.39f - (position - 6) * 0.2f && x <= 0.4f - (position - 6) * 0.2f) {
			dir = 3;
			state = 1;
			angle = (angle + PI);
			if (angle >= 2 * PI) {
				angle -= PI * 2;
			}
		}
	}
};

void display(void) {
	static float time = 0;
	static car* cars[12];
	if (time == 0) {
		car::generate(cars, 12);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < time && i < 12; i++) {
		cars[i]->position = i;
		cars[i]->display();
		cars[i]->move();
	}
	for (int i = 0; i < time - 3 && i < 15; i++) {
		cars[i]->goout();
	}
	parking::draw();
	glutSwapBuffers();
	Sleep(10);
	time += 0.002;
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