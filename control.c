
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lights.h"
#include "main.h"

#include "control.h"
#include "screenshot.h"

/*
	Declare external variables
 */
extern float Camera[3];
extern float Centre[3];
extern float UpVector[3];
extern float Radius;
extern float Theta;
extern float Phi;

/*
 * Declar external flag variables
 */
extern int OUTPUT;

void updateSphericalCoords(void) 
{
	Radius = sqrt(Camera[0]*Camera[0] + Camera[1]*Camera[1] + Camera[2]*Camera[2]);

	if(Camera[1] == 0.0) {
		if(Camera[0] > 0) { 
			Phi = 0.0;
		}
	} else {
		Phi = atan(Camera[0] / Camera[1]);
	}

	if(Radius == 0.0) {
		Theta = 0.0;
	} else {
		Theta = acos(Camera[2] / Radius);
	}
}

void updateCartesianCoords(void)
{
	Camera[0] = Radius * sin(Phi) * sin(Theta);
	Camera[2] = Radius * cos(Theta);    
	Camera[1] = Radius * cos(Phi) * sin(Theta);

	printf("Currnet Speherical Coords: %f %f %f\n", Radius, Theta, Phi);
	printf("Updating Cartesian Coords: %f, %f, %f\n", Camera[0], Camera[1], Camera[2]);
}

void updateCamera(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Camera[0], Camera[1], Camera[2],
			Centre[0], Centre[1], Centre[2],
			UpVector[0], UpVector[1], UpVector[2]);
	glutSwapBuffers();
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	extern FILE *Outputfh;
	switch (key) {
		case 'q' :
			exit(0);
			break;
		case 'l':
			addLight(2.0, 2.0, 2.0);
			break;
		case 'a' :
			moveLight(0, 1.0, 0.0, 0.0, 0.0);
			break;
		case 'd' :
			moveLight(0, -1.0, 0.0, 0.0, 0.0);
			break; 
		case 'w' :
			moveLight(0, 0.0, 1.0, 0.0, 0.0);
			break;
		case 's' :
			moveLight(0, 0.0, -1.0, 0.0, 0.0);
			break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT :
			Phi += 0.1;
			updateCartesianCoords();
			updateCamera();
			break;
		case GLUT_KEY_RIGHT :
			Phi -= 0.1;
			updateCartesianCoords();
			updateCamera();
			break;
		case GLUT_KEY_UP :
			Theta -= 0.1;
			if (Theta > M_PI)
				Theta = M_PI;
			if (Theta < 0)
				Theta = 0;
			updateCartesianCoords();
			updateCamera();
			break;
		case GLUT_KEY_DOWN :
			Theta += 0.1;
			if (Theta > M_PI)
				Theta = M_PI;
			if (Theta < 0)
				Theta = 0;
			updateCartesianCoords();
			updateCamera();
			break;
	}
}
