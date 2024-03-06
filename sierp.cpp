#include <GL/glut.h>

GLfloat v[3][2] =
{
	{0.0, 0.732},
	{1.0, -1.0},
	{-1.0, -1.0}
};

int n;
int win;
bool isPaused = true;

void triangle(GLfloat* a, GLfloat* b, GLfloat* c)
{
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{
	GLfloat v0[2], v1[2], v2[2];
	int j;
	if (m > 0)
	{
		for (j = 0; j < 2; j++) v0[j] = (a[j] + b[j]) / 2; //for every edge, find the midpoint
		for (j = 0; j < 2; j++) v1[j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 2; j++) v2[j] = (b[j] + c[j]) / 2;
		divide_triangle(a, v0, v1, m - 1);
		divide_triangle(c, v1, v2, m - 1);
		divide_triangle(b, v2, v0, m - 1);
	}
	else
		triangle(a, b, c);
}

void special(int key, int, int) {
	switch (key)
	{
		case GLUT_RIGHT_BUTTON: isPaused = true; break;
		case GLUT_LEFT_BUTTON: isPaused = false; break;
		case GLUT_KEY_DOWN: 
			glutDestroyWindow(win);
			break;
		default: return;
	}
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_triangle(v[0], v[1], v[2], n);
	glEnd();
	glFlush();
}

void init()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.8, 0.6);
}

int main(int argc, char** argv)
{
	n = 9;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(70, 70);
	glutInitWindowSize(800, 800);
	int win = glutCreateWindow("sierpinski-triangle");
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	init();
	glutMainLoop();
}
