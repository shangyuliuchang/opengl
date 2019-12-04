#include<GL/freeglut.h>
#include<math.h>
#include<Windows.h>
#include<iostream>

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
int occupation[12];
class car {
public:
	static car* cars[100];
	float x, y, angle, type, v;
	float width = 0.1, length = 0.2;
	int dir, state, position, out, reverse;
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
		reverse = 0;
	}
	static void generate(car** cars, int n) {
		for (int i = 0; i < n; i++) {
			cars[i] = new car(0);
		}
	}
	static void deletecars(car** cars, int n) {
		for (int i = 0; i < n; i++) {
			delete cars[i];
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
	void move(car** cars, int n, int no) {
		float dx, dy, distance;
		v = 0.005f;
		for (int i = 0; i < n; i++) {
			if (i != no) {
				dx = cars[no]->x - cars[i]->x;
				dy = cars[no]->y - cars[i]->y;
				distance = sqrt(dx * dx + dy * dy);
				if (distance < 0.3) {
					if (reverse == 0)v += (0.3f - distance) / 10.0f / distance * (dx*cos(angle) + dy * sin(angle));
					//if (reverse == 1)v += (0.3f - distance) / 10.0f / distance * (dx*cos(angle) + dy * sin(angle));
				}
			}
		}
		if (v > 0.005f)v = 0.005f;
		if (v < -0.005f)v = -0.005f;

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

		if (y > 5.0f) {
			v = 0;
		}

		if (dir == 2 && state == 0 && y <= -0.8f) {
			v = 0;
			reverse = 0;
			if (out == 1) {
				v = 0.005f;
				dir = 0;
				state = 0;
				angle = PI / 2;
			}
		}
		if (dir == 0 && state == 0 && y >= 0.8f && x > -0.6f) {
			v = 0;
			reverse = 0;
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

		if (out == 0 && position < 6 && dir == 3 && state == 0 && x >= -0.4f + position * 0.2f && x <= -0.39f + position * 0.2f) {
			dir = 1;
			state = 1;
			angle = (angle + PI);
			if (angle >= 2 * PI) {
				angle -= PI * 2;
			}
			reverse = 1;
		}
		if (out == 0 && position >= 6 && dir == 1 && state == 0 && x >= 0.39f - (position - 6) * 0.2f && x <= 0.4f - (position - 6) * 0.2f) {
			dir = 3;
			state = 1;
			angle = (angle + PI);
			if (angle >= 2 * PI) {
				angle -= PI * 2;
			}
			reverse = 1;
		}

		y += v * sin(angle);
		x += v * cos(angle);

		if (state == 2) {
			angle -= v * 10;
		}
		if (state == 1) {
			angle += v * 10;
		}
	}
};
car* cars[100];
int totalnumber = 1;
void display(void) {
	static float time = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < totalnumber; i++) {
		cars[i]->display();
		cars[i]->move(cars, totalnumber, i);
	}
	parking::draw();
	glutSwapBuffers();
	Sleep(10);
	time += 0.002;
}
int mousex, mousey;
void mousecallback(int a, int b, int c, int d) {
	int no;
	if (b == 1) {
		no = (int)((mousex - 200) / 100);
		if (mousey < 200) {
			no = 11 - no;
		}
		else if (mousey > 800) {

		}
		else {
			no = -1;
		}
		if (no >= 0) {
			if (occupation[no] == 0) {
				occupation[no] = 1;
				cars[totalnumber] = new car(0);
				cars[totalnumber]->position = no;
				totalnumber++;
			}
			else {
				for (int i = 0; i < totalnumber; i++) {
					if (cars[i]->position == no) {
						cars[i]->goout();
						occupation[no] = 0;
					}
				}
			}
		}
	}

}
void mousemotion(int x, int y) {
	mousex = x;
	mousey = y;
}

int main(int argc, char *argv[]) {
	cars[0] = new car(0);
	occupation[0] = 1;
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutCreateWindow("the Graph of Function!");
	glutMouseFunc(&mousecallback);
	glutPassiveMotionFunc(&mousemotion);
	glClearColor(0, 0, 0, 1);
	glutIdleFunc(&display);
	glutMainLoop();
	return 0;
}