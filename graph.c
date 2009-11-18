/*
	graph.c
	Functions to plot static graphs
 */

#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__) && (__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "graph.h"

void defineMaterial(void)
{
    GLfloat specular[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat shininess[] = {50.0};

	 //glColor3f(1.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

float redMap(float height) 
{
	extern float GradientDetails[6];
	/* Scale up so 0 <- height <= 2 */
	height = height + 1;
	return GradientDetails[0] + (height * (GradientDetails[3] - GradientDetails[0])/2);
}

float greenMap(float height) 	
{
	extern float GradientDetails[6];
	height = height + 1;
	return GradientDetails[1] + (height * (GradientDetails[4] - GradientDetails[1])/2);
}

float blueMap(float height) 
{
	extern float GradientDetails[6];
	height = height + 1;
	return GradientDetails[2] + (height * (GradientDetails[5] - GradientDetails[2])/2);
}

void plotGraph(struct dataset *ds)
{
    int is,it; /* Counters for s and t coords */
    double x,y,z;   /* To hold current point to plot */
	 extern int COLOUR;
	 extern int USE_GRADIENT_FILL;
	 extern int WIREFRAME;
	 extern float Colour[3];

    defineMaterial();

	 if (WIREFRAME == 1) {
		 glPolygonMode(GL_FRONT, GL_LINE);
		 glPolygonMode(GL_BACK, GL_LINE);
	 } else {
		 glPolygonMode(GL_FRONT, GL_FILL);
		 glPolygonMode(GL_BACK, GL_FILL);
	 }
					
    
    printf("Begin Plot\n");
    for (it=1; it < ds->Y; it++) {
        glBegin(GL_QUAD_STRIP);
        for (is=0; is < ds->X ; is++) {
            x = ds->x[(is * ds->Y) + it];
            y = ds->y[(is * ds->Y) + it];
            z = ds->z[(is * ds->Y) + it];
				/* Check to see if cmd line args passed */
				if (COLOUR == 1) {
					glColor3f(Colour[0], Colour[1], Colour[2]);
				} else {
					glColor3f(1.0, 1.0, 1.0);
				}
				if (USE_GRADIENT_FILL == 1) {
					glColor3f(redMap(z), greenMap(z), blueMap(z));
					printf("x = %f, y = %f, z = %f\n", redMap(z), greenMap(z), blueMap(z));
				}
            glVertex3d(x, y, z);

            x = ds->x[(is * ds->Y) + it - 1];
            y = ds->y[(is * ds->Y) + it - 1];
            z = ds->z[(is * ds->Y) + it - 1];
				if (USE_GRADIENT_FILL == 1) {
					glColor3f(redMap(z), greenMap(z), blueMap(z));
				}
            glVertex3d(x, y, z);

        }
        glEnd();
    }	
    printf("End Plot\n");
}
