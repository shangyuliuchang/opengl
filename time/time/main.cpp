#include<GL/freeglut.h>
#include<math.h>
#include<Windows.h>
float *funx, *funy;
int n;
float parameter = 1;
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor4f(1, 1, 1, 1);
	glVertex2f(funx[0] * parameter, funy[0] * parameter);
	for (int i = 0; i < n; i++) {
		glVertex2f(funx[i]*parameter, funy[i]*parameter);
		glVertex2f(funx[i]*parameter, funy[i]*parameter);
	}
	glEnd();
	glutSwapBuffers();
	parameter *= 1.001;
	Sleep(10);
}
float f(float x) {
	return (sin(1 / x)*fabs(x));
}
void calculate(float* x, float*y, int* number, float begin, float end) {
	float n = 5.0f;
	float delta = (end - begin) / n;
	for (float mid = begin + delta; mid <= end - delta; mid++) {
		if (fabs((f(begin)*(end - mid) + f(end)*(mid - begin)) / (end - begin) - f(mid)) > 0.00001f && (*number) < 99999 && (end-begin)>0.0001f) {
			x[*number] = mid;
			y[*number] = f(mid);
			(*number)++;
			calculate(x, y, number, begin, mid);
			calculate(x, y, number, mid, end);
		}
	}
}
void rerange(float* x, float* y, int n) {
	float ex;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (x[i] > x[j]) {
				ex = x[i];
				x[i] = x[j];
				x[j] = ex;
				ex = y[i];
				y[i] = y[j];
				y[j] = ex;
			}
		}
	}
}
int main(int argc, char *argv[]) {
	int number = 0;
	float x[100000], y[100000];
	x[0] = -1.0f;
	x[1] = 1.0f;
	y[0] = f(x[0]);
	y[1] = f(x[1]);
	number = 2;
	calculate(x, y, &number, x[0], x[1]);
	funx = x;
	funy = y;
	n = number;
	rerange(x, y, number);
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