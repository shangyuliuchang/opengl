#include<GL/glut.h>
#include<math.h>
#include<Windows.h>
#include<iostream>

#define PI 3.1415926535
struct recData
{
	int number;
	float x[100], y[100], z[100];
	float r, g, b;
};
class draw {
public:
	static void drawlines(recData* data) {
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
		GLfloat mat_shininess[] = { 100 };               //高光指数
		mat_specular[0] = data->r;
		mat_specular[1] = data->g;
		mat_specular[2] = data->b;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		glBegin(GL_POLYGON);
		for (int i = 0; i < data->number; i++)
			glVertex3f(data->x[i], data->y[i], data->z[i]);
		glEnd();
	}
	static void transform(float x, float y, float ancx, float ancy, float angle, float orix, float oriy, float* truex, float* truey) {
		*truex = x - (oriy - ancy) * sin(angle) + (orix - ancx) * cos(angle);
		*truey = y + (oriy - ancy) * cos(angle) + (orix - ancx) * sin(angle);
	}
};
class parking {
public:
	static void draw() {
		recData cen;
		cen.number = 4;
		cen.g = cen.b = cen.r = 1;
		for (float x = -0.6f; x <= 0.6f; x += 0.2) {
			cen.x[0] = cen.x[1] = x - 0.01f;
			cen.x[2] = cen.x[3] = x + 0.01;
			cen.y[0] = cen.y[3] = -1.0f;
			cen.y[1] = cen.y[2] = -0.6f;
			draw::drawlines(&cen);
		}
		for (float x = -0.6f; x <= 0.6f; x += 0.2) {
			cen.x[0] = cen.x[1] = x - 0.01f;
			cen.x[2] = cen.x[3] = x + 0.01;
			cen.y[0] = cen.y[3] = 1.0f;
			cen.y[1] = cen.y[2] = 0.6f;
			draw::drawlines(&cen);
		}
		cen.x[0] = -0.6f; cen.y[0] = -0.2f;
		cen.x[1] = 0.6f; cen.y[1] = -0.2f;
		cen.x[2] = 0.6f; cen.y[2] = 0.2f;
		cen.x[3] = -0.6f; cen.y[3] = 0.2f;
		cen.z[0] = cen.z[1] = cen.z[2] = cen.z[3] = 0;
		draw::drawlines(&cen);
	}
};
int occupation[12];
class car {
public:
	static car* cars[2000];
	static int totalnumber;
	float x, y, angle, v;
	float width = 0.1, length = 0.2;
	int dir, state, position, out, reverse, type;
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
		for (int i = 0; i < n; i++) cars[i] = new car(0);
	}
	static void deletecars(car** cars, int n) {
		for (int i = 0; i < n; i++) delete cars[i];
	}
	void goout() {
		out = 1;
	}
	void display() {
		if (true) {
			recData recD;
			recD.number = 4;
			recD.r = recD.g = recD.b = 1;
			for (int i = 0; i < 4; i++) {
				draw::transform(x, y, 0, 0, angle, length / 2 * (i == 0 || i == 3 ? 1 : -1), width / 2 * (i < 2 ? 1 : -1), &recD.x[i], &recD.y[i]);
				recD.z[i] = 0;
			}
			draw::drawlines(&recD);

			for (int i = 0; i < 4; i++) {
				draw::transform(x, y, 0, 0, angle, length / 2 * (i == 0 || i == 3 ? 0 : -1), width / 2 * (i < 2 ? 1 : -1), &recD.x[i], &recD.y[i]);
				recD.z[i] = -0.1f;
			}
			draw::drawlines(&recD);

			recD.number = 5;
			recD.r = 1; recD.g = 0.8f; recD.b = 0.5f;
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * -1, &recD.x[0], &recD.y[0]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * -1, &recD.x[1], &recD.y[1]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * -1, &recD.x[2], &recD.y[2]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * -1, &recD.x[3], &recD.y[3]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 0, width / 2 * -1, &recD.x[4], &recD.y[4]);
			recD.z[0] = -0.05f; recD.z[1] = 0;  recD.z[2] = 0; recD.z[3] = recD.z[4] = -0.1f;
			draw::drawlines(&recD);

			recD.r = 1; recD.g = 0.8f; recD.b = 0.5f;
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * 1, &recD.x[0], &recD.y[0]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * 1, &recD.x[1], &recD.y[1]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * 1, &recD.x[2], &recD.y[2]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * 1, &recD.x[3], &recD.y[3]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 0, width / 2 * 1, &recD.x[4], &recD.y[4]);
			recD.z[0] = -0.05f; recD.z[1] = 0;  recD.z[2] = 0; recD.z[3] = recD.z[4] = -0.1f;
			draw::drawlines(&recD);

			recD.number = 4;
			recD.r = 0.5f; recD.g = 0.5f; recD.b = 0.5f;
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * 1, &recD.x[0], &recD.y[0]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * -1, &recD.x[1], &recD.y[1]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * -1, &recD.x[2], &recD.y[2]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * 1, &recD.x[3], &recD.y[3]);
			recD.z[0] = 0; recD.z[1] = 0;  recD.z[2] = -0.05f; recD.z[3] = -0.05f;
			draw::drawlines(&recD);

			recD.r = 0.5f; recD.g = 0.5f; recD.b = 0.5f;
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * 1, &recD.x[0], &recD.y[0]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * -1, &recD.x[1], &recD.y[1]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * -1, &recD.x[2], &recD.y[2]);
			draw::transform(x, y, 0, 0, angle, length / 2 * -1, width / 2 * 1, &recD.x[3], &recD.y[3]);
			recD.z[0] = 0; recD.z[1] = 0;  recD.z[2] = -0.1f; recD.z[3] = -0.1f;
			draw::drawlines(&recD);

			recD.r = 0.2f; recD.g = 0.2f; recD.b = 0.2f;
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * 1, &recD.x[0], &recD.y[0]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 0, width / 2 * 1, &recD.x[1], &recD.y[1]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 0, width / 2 * -1, &recD.x[2], &recD.y[2]);
			draw::transform(x, y, 0, 0, angle, length / 2 * 1, width / 2 * -1, &recD.x[3], &recD.y[3]);
			recD.z[0] = -0.05f; recD.z[1] = -0.1f;  recD.z[2] = -0.1f; recD.z[3] = -0.05f;
			draw::drawlines(&recD);
		}
	}
	void move(car** cars, int n, int no) {
		float dx, dy, distance;
		float x_1, y_1, x_2, y_2;
		v = 0.005f;
		if (reverse == 1) v *= -1;
		for (int i = 0; i < n; i++) {
			if (i != no) {
				draw::transform(cars[no]->x, cars[no]->y, 0, 0, angle, 0, 0, &x_1, &y_1);
				draw::transform(cars[i]->x, cars[i]->y, 0, 0, angle, 0, 0, &x_2, &y_2);
				dx = x_1 - x_2;
				dy = y_1 - y_2;
				distance = sqrt(dx * dx + dy * dy);
				if (distance < 0.3)
					if (reverse == 0) v += (0.3f - distance) / 5.0f / distance * (dx*cos(angle) + dy * sin(angle));
			}
		}
		if (v > 0.005f)v = 0.005f;
		if (v < -0.005f)v = -0.005f;

		if (dir == 0 && state == 0 && y > -0.5f && y < -0.49f && reverse == 0) state = 2;
		if (dir == 2 && state == 0 && y <= 0.5f && y >= 0.49f && reverse == 0) state = 2;
		if (dir == 3 && state == 0 && x > 0.7f && x < 0.71f) state = 1;
		if (dir == 0 && state == 0 && y > 0.3f && y < 0.31f) state = 1;
		if (dir == 1 && state == 0 && x < -0.7f && x > -0.71f) state = 2;

		if (dir == 0 && state == 0 && y <= -0.8f && reverse == 1) {
			v = 0;
			if (out == 1) {
				reverse = 0;
				v = 0.005f;
				dir = 0;
				state = 0;
			}
		}
		if (dir == 2 && state == 0 && y >= 0.8f && x > -0.6f && reverse == 1) {
			v = 0;
			if (out == 1) {
				reverse = 0;
				v = 0.005f;
				dir = 2;
				state = 0;
			}
		}

		if ((state == 1 || state == 2) && fabs((angle)-((dir - (state * 2 - 3)*(1 - reverse * 2) + 1) % 4)*PI / 2) <= 0.1f) {
			dir = (dir - (state * 2 - 3)*(1 - reverse * 2) + 4) % 4;
			state = 0;
			angle = ((dir + 1) % 4)*PI / 2;
		}

		if ((out == 0 && position < 6 && dir == 3 && state == 0 && x >= -0.4f + position * 0.2f && x <= -0.39f + position * 0.2f) ||
			(out == 0 && position >= 6 && dir == 1 && state == 0 && x >= 0.39f - (position - 6) * 0.2f && x <= 0.4f - (position - 6) * 0.2f)) {
			state = 2;
			reverse = 1;
		}

		y += v * sin(angle);
		x += v * cos(angle);

		if (state == 2) angle -= v * 10;
		if (state == 1) angle += v * 10;
		if (angle >= 2 * PI) angle -= 2 * PI;
		if (angle < 0) angle += 2 * PI;
	}
};
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	parking::draw();

	for (int i = 0; i < car::totalnumber; i++) {
		car::cars[i]->display();
		car::cars[i]->move(car::cars, car::totalnumber, i);
	}
	glutSwapBuffers();

	int j = 0;
	while(j<car::totalnumber){
		if (car::cars[j]->y > 1.1f) {
			delete car::cars[j];
			for (int i = j; i < car::totalnumber; i++) {
				car::cars[i] = car::cars[i + 1];
			}
			car::totalnumber--;
		}
		else j++;
	}

	Sleep(10);
}
int mousex, mousey;
void mousecallback(int a, int b, int c, int d) {
	int no;
	if (b == 1) {
		no = (int)((mousex - 200) / 100);
		if (mousey < 200) no = 11 - no;
		if (mousey >= 200 && mousey <= 800 || mousey < 0 || mousey>1000 || mousex < 200 || mousex>800) no = -1;
		if (no >= 0) {
			if (occupation[no] == 0) {
				occupation[no] = 1;
				car::cars[car::totalnumber] = new car(car::totalnumber);
				car::cars[car::totalnumber]->position = no;
				car::totalnumber++;
			}
			else {
				for (int i = 0; i < car::totalnumber; i++) {
					if (car::cars[i]->position == no) {
						car::cars[i]->goout();
						occupation[no] = 0;
					}
				}
			}
		}
	}

}
void mousemotion(int x, int y) {
	float t;
	t = 1 / sqrt(24.0);
	mousey = 0.5f * ((x - 500) / (t*sqrt(3.0)) + (y - 500) / t) / 2.0f + 500.0f;
	mousex = -0.5f * (-1 * (x - 500) / (t*sqrt(3.0)) + (y - 500) / t) / 2.0f + 500.0f;
}
int car::totalnumber = 0;
car* car::cars[2000];
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("the Graph of Function!");
	glutMouseFunc(&mousecallback);
	glutPassiveMotionFunc(&mousemotion);
	glClearColor(0, 0, 0, 1);
	gluLookAt(0.01, 0.01, 0.01, 0, 0, 0, 0, 0, -1);

	GLfloat light_position[] = { 0, 0, 0.2, 1.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   

	glShadeModel(GL_SMOOTH);        

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(&display);
	glutMainLoop();
	return 0;
}