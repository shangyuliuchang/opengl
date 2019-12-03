#include<GL/freeglut.h>
#include<math.h>
float *funx, *funy;
int n;
void display() {
	glBegin(GL_LINES);
	glColor4f(1,1,1,1);
	glVertex2f(funx[0], funy[0]);
	for (int i = 0; i < n; i++) {
		glVertex2f(funx[i], funy[i]);
		glVertex2f(funx[i], funy[i]);
	}
	glEnd();
	glFlush();
}
float f(float x) {
	return (sin(1 / x)*log(fabs(x)+0.1)/3);
}
void calculate(float* x, float*y, int* number, float begin, float end) {
	float n = 3.0f;
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
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("the Graph of Function!");
	glClearColor(0, 0, 0, 1);
	glutDisplayFunc(&display);
	glutMainLoop();
	return 0;
}