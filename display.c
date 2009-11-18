/*
 * display.c
 */

#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "main.h"
#include "control.h"
#include "graph.h"
#include "display.h"
#include "savegraph.h"
#include "lights.h"


void initDisplay(void)
{	
	extern float Camera[3];
	extern float Centre[3];
	extern float UpVector[3];
	
	extern int FLAT_SHADING;
	extern int WINDOW_SIZE;
	extern int Width;
	extern int Height;
	
	/* Initialise Window */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	if (WINDOW_SIZE ==1) {
		glutInitWindowSize(Width, Height);
	} else {
		glutInitWindowSize(DEF_WIN_WIDTH, DEF_WIN_HEIGHT);
	}
	glutInitWindowPosition(DEF_WIN_X_POS, DEF_WIN_Y_POS);
	glutCreateWindow("3dPlot");

	/* Clear Background */
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	
	gluLookAt(Camera[0], Camera[1], Camera[2],
			Centre[0], Centre[1], Centre[2],
			UpVector[0], UpVector[1], UpVector[2]);

	glLoadIdentity();

	if (FLAT_SHADING == 1) {
		glShadeModel(GL_FLAT);
	} else {
		glShadeModel(GL_SMOOTH);
	}
}

void setCameraDefaults(void)
{	
	extern float Camera[3];
	extern float Centre[3];
	extern float UpVector[3];

	extern int SET_CAMERA_PLACEMENT;
	extern float CameraPlacement[6];
	int i;

	/* Init gluLookAt */
	if (SET_CAMERA_PLACEMENT == 1) {
		Camera[0] = CameraPlacement[0];
		Camera[1] = CameraPlacement[1];
		Camera[2] = CameraPlacement[2];
		Centre[0] = CameraPlacement[3];
		Centre[1] = CameraPlacement[4];
		Centre[2] = CameraPlacement[5];
		UpVector[0] = CameraPlacement[6]; 
		UpVector[1] = CameraPlacement[7];
		UpVector[2] = CameraPlacement[8];
	} else {
		Camera[0] = CAMX;
		Camera[1] = CAMY;
		Camera[2] = CAMZ;
		Centre[0] = CENTREX;
		Centre[1] = CENTREY;
		Centre[2] = CENTREZ;
		UpVector[0] = UPVECTORX; 
		UpVector[1] = UPVECTORY;
		UpVector[2] = UPVECTORZ;
	}

	/* Set initial Coords */
	updateSphericalCoords();
	
}

void drawAxis(void)
{
	extern int AXIS_DEFINED;
	extern float Axis[6];

	/* Set axis colour */
	glColor3d(1.0, 1.0, 1.0);
	if (AXIS_DEFINED == 1) {		

		glBegin(GL_LINES);    
		/* x-axis */
		glVertex3d(Axis[0], 0.0, 0.0);
		glVertex3d(Axis[1], 0.0, 0.0);

		/* y-axis */
		glVertex3d(0.0, Axis[2], 0.0);
		glVertex3d(0.0, Axis[3], 0.0);

		/* z-axis */
		glVertex3d(0.0, 0.0, Axis[4]);
		glVertex3d(0.0, 0.0, Axis[5]);
		glEnd(); /* GL_LINES */

	} else {
		glBegin(GL_LINES);    
		/* x-axis */
		glVertex3d(-1.25, 0.0, 0.0);
		glVertex3d(1.25, 0.0, 0.0);

		/* y-axis */
		glVertex3d(0.0, -1.25, 0.0);
		glVertex3d(0.0, 1.25, 0.0);

		/* z-axis */
		glVertex3d(0.0, 0.0, -1.25);
		glVertex3d(0.0, 0.0, 1.25);
		glEnd(); /* GL_LINES */
	}

	glFlush();
}

void drawGraph(struct dataset *ds)
{
	extern GLuint *ThePlot;

	ThePlot = malloc(sizeof(GLuint));

	ThePlot[0] = glGenLists(1);
	glNewList(ThePlot[0], GL_COMPILE);
	plotGraph(ds);
	glEndList();

}

void reshape(int w, int h )
{
	extern float Camera[3];
	extern float Centre[3];
	extern float UpVector[3];

	/* Prevent divide by zero error if window too small */
	if(h == 0) {
		h = 1;
	};

	/* Set Viewport to be entire window */
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	/* Reset the coordinate system before modifying */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Set the correct perspective */
	gluPerspective(45, w/h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Camera[0], Camera[1], Camera[2],
			Centre[0], Centre[1], Centre[2],
			UpVector[0], UpVector[1], UpVector[2]);
}

void renderGraph(void)
{
	extern GLuint *ThePlot;
	extern int OUTPUT;
	extern char *OutputFile;

	extern int PLACE_LIGHT;
	extern float LightDetails[3];

	glClear(GL_COLOR_BUFFER_BIT);
	/*| GL_DEPTH_BUFFER_BIT); */

	if (PLACE_LIGHT == 1) {
		addLight(LightDetails[0], LightDetails[1], LightDetails[2]);
		printf("Light: %f, %f, %f\n", LightDetails[0], LightDetails[1], LightDetails[2]);
		/* Prevent it trying to place same light again! */
		PLACE_LIGHT=0;
	}

	drawAxis();

	glCallList(ThePlot[0]);
	glutSwapBuffers();
	glFlush();


	if (OUTPUT ==1) {
		printf("Saving Graph\n");
		saveGraph(OutputFile);
		exit(0);
	}
}
