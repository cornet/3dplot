/*
 * lights.c
 * Routines to handle light placement
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lights.h"
#include "control.h"

struct light *Lights;


int addLight(float x, float y, float z)
{
    float *t; /* temp var */
    float lmodelambient[] = {1.0, 1.0, 1.0, 1.0};
    
    Lights = malloc(sizeof(struct light));
    
    Lights->lightid = GL_LIGHT0;
    Lights->position = NULL;
    Lights->diffuse = NULL;
    Lights->specular = NULL;

    
    t = realloc(Lights->position, 4 * sizeof(double));
    if (t == NULL) {
        destroyLight(0);
        printf("addLight: failed while reallocating data\n");
        return NULL;
    }
    Lights->position = t;
    t = realloc(Lights->diffuse, 4 * sizeof(double));
    if (t == NULL) {
        destroyLight(0);
        printf("addLight: failed while reallocating data\n");
        return NULL;
    }
    Lights->diffuse = t;
    t = realloc(Lights->specular, 4 * sizeof(double));
    if (t == NULL) {
        destroyLight(0);
        printf("addLight: failed while reallocating data\n");
        return NULL;
    }
    Lights->specular = t;
    
    Lights->position[0] = x;
    Lights->position[1] = y;
    Lights->position[2] = z;
    Lights->position[3] = 1.0;
    Lights->diffuse[0] = 1.0;
    Lights->diffuse[1] = 1.0;
    Lights->diffuse[2] = 1.0;
    Lights->diffuse[3] = 1.0;
    Lights->specular[0] = 10.0;
    Lights->specular[1] = 10.0;
    Lights->specular[2] = 10.0;
    Lights->specular[3] = 1.0;
    
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
    glLightfv(Lights->lightid, GL_POSITION, Lights->position);
    glLightfv(Lights->lightid, GL_DIFFUSE, Lights->diffuse);
    glLightfv(Lights->lightid, GL_SPECULAR, Lights->specular); 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelambient);
    
    glEnable(GL_LIGHTING);
    glEnable(Lights->lightid);
    glEnable(GL_DEPTH_TEST);
	 /* Force update of camera (or get blank screen) */
	 updateCamera();
    return 1;
}

void destroyLight(int lightID)
{
    
}

void delLight(int lightID)
{
    
}

void moveLight(int lightID, float x, float y, float z, float w)
{
    float lightposition[4];
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
    Lights->position[0] += x;
    Lights->position[1] += y;
    Lights->position[2] += z;
    Lights->position[3] += w;
        
    glLightfv(GL_LIGHT0, GL_POSITION, Lights->position);
    
    glutPostRedisplay();
}
