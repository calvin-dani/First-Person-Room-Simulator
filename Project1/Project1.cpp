#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<string.h>

static GLfloat theta[] = { 0.0,0.0,0.0 };
static GLint axis = 2;
static GLdouble viewer[] = { 3.3, 1.0, 1.0 };
char message[10];



void chairleg(double thick, double len)
{
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void chair(double topWid, double topThick, double legThick, double legLen)
{
	//draw the table - a top and four legs
	//draw the top first
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	chairleg(legThick, legLen);
	glTranslated(0.0, 0.0, -2 * dist);
	chairleg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	chairleg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	chairleg(legThick, legLen);
	glPopMatrix();

}

void wall(double thickness)
{
	//draw thin wall with top = xz-plane, corner at origin
	glPushMatrix();
	
	//glTranslated(0.5, 0.5 * thickness, 0.5);
	//glScaled(1.0, thickness, 1.0);
	//glutSolidCube(1.0);
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	

	glEnd();
	glPopMatrix();
}

void wallx(double thickness)
{
	//draw thin wall with top = yz-plane, corner at origin
	glPushMatrix();
	glTranslated(0.5, 1.0, 0.5);
	glScaled(1.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

//draw one table leg
void tableLeg(double thick, double len)
{
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void table(double topWid, double topThick, double legThick, double legLen)
{
	//draw the table - a top and four legs
	//draw the top first
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	tableLeg(legThick, legLen);
	glTranslated(0.0, 0.0, -2 * dist);
	tableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableLeg(legThick, legLen);
	glPopMatrix();
}
void displaySolid(void)
{
	//set properties of the surface material
	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // gray
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//set the light source properties
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat light_position[] = { 2.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	//set the camera
	//glMatrixMode(GL_PROJECTION);
	/*glLoadIdentity();
	double winHt = 1.0; //half-height of window
	glOrtho(-winHt * 64 / 48.0, winHt * 64 / 48.0, -winHt, winHt, 0.1, 100.0);*/
	GLfloat aspect = 640 / 480; // Compute aspect ratio of window
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
	glLoadIdentity(); // Reset
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.25, 1.0, 0.0, 1.0, 0.0);
	//start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





	glPushMatrix();
	glTranslated(3.2, 0.65, 1.5);
	glRotated(30, 0, 1, 0);
	glutSolidTeapot(0.08);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3.0, 0.0, 1.5);
	table(1.2, 0.02, 0.02, 0.6);
	glPopMatrix();



	for (int wz = 0;wz < 3; wz++) {
		for (int wx = 0; wx < 5; wx++) {

			glPushMatrix();
			glTranslated((float)wx, 0, (float)wz);
			wall(0.02);

			glPopMatrix();

		}
	}

	for (int wy = 0;wy < 2; wy++) {
		for (int wx = 0; wx < 5; wx++) {

			glPushMatrix();
			glTranslated((float)wx, (float)wy, 0);
			glRotated(-90, 1, 0, 0);
			wall(0.02);
			glPopMatrix();

		}
	}

	for (int wy = 0;wy < 2; wy++) {
		for (int wx = 0; wx < 5; wx++) {

			glPushMatrix();
			glTranslated((float)wx, (float)wy, 3);
			glRotated(-90, 1, 0, 0);
			wall(0.02);
			glPopMatrix();

		}
	}

	for (int wz = 0;wz <= 2; wz++) {
		for (int wx = 0; wx <= 4; wx++) {

			glPushMatrix();
			glTranslated((float)wx, 2, (float)wz);
			wall(0.02);
			glPopMatrix();

		}
	}

	for (int wz = 0;wz < 3; wz++) {
		for (int wy = 0; wy < 2; wy++) {

			glPushMatrix();
			glTranslated(0, (float)wy, (float)wz);
			glRotated(90, 0.0, 0.0, 1.0);
			wall(0.02);
			glPopMatrix();

		}
	}

	glPushMatrix();
	glTranslated(2.0, 0.0, 1.5);
	chair(0.2, 0.02, 0.01, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.0, 0.0, 2.0);
	chair(0.2, 0.02, 0.01, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5, 0.0, 2.5);
	chair(0.2, 0.02, 0.01, 0.3);
	glPopMatrix();

	glFlush();



}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	displaySolid();
}
void keys(unsigned char key, int x, int y)
{
	if (key == 'q') viewer[0] -= 1.0;
	if (key == 'w') viewer[0] += 1.0;
	if (key == 'a') viewer[1] -= 1.0;
	if (key == 's') viewer[1] += 1.0;
	if (key == 'z') viewer[2] -= 1.0;
	if (key == 'x') viewer[2] += 1.0;

	displaySolid();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("simple shaded scene consisting of a tea pot on a table");
	glutKeyboardFunc(keys);
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//glutMouseFunc(mouse);

	glClearColor(0.1, 0.1, 0.1, 0.0);
	glViewport(0, 0, 640, 480);
	glutMainLoop();
}