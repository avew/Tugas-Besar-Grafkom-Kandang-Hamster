/*
 * main.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: kodehijau
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "imageloader.h"
#include "vec3f.h"

static GLfloat spin = 0.0;
float angle = 0;
GLuint texture[2];

float lastx, lasty;
GLint stencilBits;
static int viewx = 50;
static int viewy = 24;
static int viewz = 80;

float rot = 0;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

}

float _angle = 60.0f;

const GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat light_ambient2[] = { 0.3f, 0.3f, 0.3f, 0.0f };
const GLfloat light_diffuse2[] = { 0.3f, 0.3f, 0.3f, 0.0f };

const GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void cylinder(float alas, float atas, float tinggi) {
	float i;
	glPushMatrix();
	glTranslatef(1.0, 0.0, -alas / 8);
	glutSolidCone(alas, 0, 32, 4);
	for (i = 0; i <= tinggi; i += alas / 24) {
		glTranslatef(0.0, 0.0, alas / 24);
		glutSolidTorus(alas / 4, alas - ((i * (alas - atas)) / tinggi), 16, 16);
	}
	glTranslatef(0.0, 0.0, alas / 4);
	glutSolidCone(atas, 0, 20, 1);
	glPopMatrix();
}

void patokan(int panjang) {
	int x;
	glPushMatrix();
	for (x = 0; x < panjang; x++) {
		glutSolidCube(10);
		glTranslated(10.0, 0.0, 0.0);
	}
	glPopMatrix();

	glPushMatrix();
	for (x = 0; x < panjang; x++) {
		glTranslated(-10.0, 0.0, 0.0);
		glutSolidCube(10);
	}
	glPopMatrix();
}

void bawahKandang(int lebar) {
	int zplus;
	int zmin;
	patokan(10);
	glPushMatrix();
	for (zplus = 0; zplus < lebar; ++zplus) {
		glTranslated(0.0, 0.0, 10.0);
		patokan(10);
	}
	glPopMatrix();
	glPushMatrix();
	for (zmin = 0; zmin < lebar; ++zmin) {
		glTranslated(0.0, 0.0, -10.0);
		patokan(10);
	}
	glPopMatrix();
}

void pohon() {
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(15.0, 15.0, 15, 10);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(-1.0, 0.0, -20.0);
	cylinder(8.0, 8.0, 20.0);
	glPopMatrix();
}

void segitiga() {
	glBegin(GL_QUADS);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, -2, -2);
	glVertex3f(-2, 2, -2);
	glVertex3f(-2, 2, 2);
	glEnd();

	//Sisi-sisi Prisma
	glBegin(GL_TRIANGLES);
	glColor3d(1.0f, 1.0f, 1.0f);
	//Segitiga Warna Merah
	glVertex3f(-2, -2, 2);
	glVertex3f(8, 0, 0);
	glVertex3f(-2, 2, 2);
	//Segitiga Warna Hijau
	glVertex3f(-2, 2, 2);
	glVertex3f(8, 0, 0);
	glVertex3f(-2, 2, -2);
	//Segitiga Warna Biru
	glVertex3f(-2, 2, -2);
	glVertex3f(8, 0, 0);
	glVertex3f(-2, -2, -2);
	//Segitiga Warna Putih
	glVertex3f(-2, -2, -2);
	glVertex3f(8, 0, 0);
	glVertex3f(-2, -2, 2);
	glEnd();
}

void muterMuteran() {
	glPushMatrix();
	glTranslated(00.0, 20.0, -1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glRotated(30.0, 1.0, 0.0, 0.0);
	cylinder(3.0, 3.0, 20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(00.0, 20.0, 1.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glRotated(-30.0, 1.0, 0.0, 0.0);
	cylinder(3.0, 3.0, 20.0);
	glPopMatrix();

	glPushMatrix();
	glutSolidCube(10);
	glTranslated(0.0, 0.0, 10.0);
	glutSolidCube(10);
	glTranslated(0.0, 0.0, -20.0);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 40.0, 0.0);
	glRotated(-90, 0.0, 1.0, 0.0);
	cylinder(20.0, 20.0, 5.0);
	glPopMatrix();
}

void display(void) {
	glClearStencil(0); //clear the stencil buffer
	glClearDepth(1.0f);
	glClearColor(0.0, 0.6, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers
	glLoadIdentity();
	gluLookAt(viewx, viewy, viewz, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);

	//Tambahin Objek dibawah ini
	glPushMatrix();
	glTranslated(-90.0, 5.0, 70.0);
	muterMuteran();
	glPopMatrix();

	//atap
	glPushMatrix();
	glTranslated(5.0, 5.0, 0.0);
	glRotated(90.0, 0.0, 0.0, 1.0);
	glScaled(5.0, 10.0, 10.0);
	segitiga();
	glPopMatrix();
	//bawah
	glPushMatrix();
	glTranslated(10,10,10);//cube
	glScaled(3.0,3.0,3.0);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 95.0, 5.0);
	cylinder(6.0, 6.0, 15.0);
	for (int x = 0; x < 4; x++) {
		glTranslated(0.0, -15.0, 0.0);
		cylinder(6.0, 6.0, 15.0);
	}
	glPopMatrix();

	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, -10.0, 5.0);
	cylinder(6.0, 6.0, 15.0);
	for (int x = 0; x < 6; x++) {
		glTranslated(-15.0, 0.0, 0.0);
		cylinder(6.0, 6.0, 15.0);
	}
	glPopMatrix();

	//Hiasan Pohon Dipojok
	glPushMatrix();
	glTranslated(-90.0, 25.0, -90.0);
	pohon();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-85.0, 25.0, -70.0);
	pohon();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-70.0, 20.0, -90.0);
	pohon();
	glPopMatrix();

	//Tempat Minum
	glPushMatrix();
	glTranslated(-60.0, 10.0, -60.0);
	glRotated(-270.0, 1.0, 0.0, 0.0);
	cylinder(15.0, 10.0, 3.0);
	glPopMatrix();
//
//////	//tiang 1
////	glPushMatrix();
////	glRotated(-90, 1.0, 0.0, 0.0);
////	glTranslated(90.0, 100.0, 0.0);
////	cylinder(3.0, 3.0, 150);
////	glPopMatrix();
//////
////////	//tiang 2
////	glPushMatrix();
////	glRotated(-90, 1.0, 0.0, 0.0);
////	glTranslated(90.0, -100.0, 0.0);
////	cylinder(3.0, 3.0, 150);
////	glPopMatrix();
////
//////	//tiang 3
////	glPushMatrix();
////	glRotated(-90, 1.0, 0.0, 0.0);
////	glTranslated(-100.0, 100.0, 0.0);
////	cylinder(3.0, 3.0, 150);
////	glPopMatrix();
////
//////	//tiang 4
////	glPushMatrix();
////	glRotated(-90, 1.0, 0.0, 0.0);
////	glTranslated(-100.0, -100.0, 0.0);
////	cylinder(3.0, 3.0, 150);
////	glPopMatrix();

//	//Bawah
	glPushMatrix();
	bawahKandang(10);
	glPopMatrix();

//	//atas
//	glPushMatrix();
//	glTranslated(0.0, 150.0, 0.0);
//	bawahKandang(10);
//	glPopMatrix();

	glutSwapBuffers();
	glFlush();
	rot++;
	angle++;
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
}

static void kibor(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_HOME:
		viewy++;
		break;
	case GLUT_KEY_END:
		viewy--;
		break;
	case GLUT_KEY_UP:
		viewz--;
		break;
	case GLUT_KEY_DOWN:
		viewz++;
		break;

	case GLUT_KEY_RIGHT:
		viewx++;
		break;
	case GLUT_KEY_LEFT:
		viewx--;
		break;

	case GLUT_KEY_F1: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	case GLUT_KEY_F2: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'd') {

		spin = spin - 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'a') {
		spin = spin + 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'q') {
		viewz++;
	}
	if (key == 'e') {
		viewz--;
	}
	if (key == 's') {
		viewy--;
	}
	if (key == 'w') {
		viewy++;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH); //add a stencil buffer to the window
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Katanya Kandang Hamster 0(@@)0");
	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(kibor);

	glutKeyboardFunc(keyboard);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glutMainLoop();
	return 0;
}

