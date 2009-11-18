/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "savegraph.h"
#include "display.h"
#include "graph.h"
#include "movie.h"
#include "file.h"
#include "main.h"
#include "lights.h"

void destroyFrames(struct frame *frames)
{
	if (frames == NULL)
		return;
	if (frames->framepath != NULL)
		free(frames->framepath);

	free(frames);
}

void destroyList(GLuint *list)
{
	if (list == NULL)
		return;
	else
		free(list);
}

struct frame *readFrames(char *fn)
{
	char buf[BUFSIZE]; /* Buffer to hold single line */
	char path[BUFSIZE];
	struct frame *frames;    /* Holds names of frame file */
	char (*t)[BUFSIZE];
	int i, j, k;
	int EOL; /* End of Line flag */
	extern int NumOfFrames;
	FILE *fh;

	/* Read file into array, expanding as required */
	fh = fopen(fn,"r");
	i=0;

	frames = malloc(sizeof(struct frame));
	frames->framepath = NULL;
	frames->num = 0;

	while (fgets(buf, sizeof(buf), fh) != NULL) {
		EOL=0;
		j=0; k=0;
		while(j < sizeof(buf) && EOL != 1) {
			switch (buf[j]) {
				case '\n':
					EOL=1;
					path[k] = '\0';
					break;
				case '\0':
					EOL=1;
					path[k] = '\0';
					break;
				default:
					path[k] = buf[j];
					j++; k++;
					break;
			}
		}

		/* Allocates memory to save current path name */
		t = realloc(frames->framepath, sizeof(buf) * (i+1));
		if (t == NULL) {
			destroyFrames(frames);
			printf("readFrames: failed while reallocating data\n");
			return NULL;
		}

		frames->framepath = t;

		strcpy(frames->framepath[i], path);
		i++;
		frames->num++;

	}

	NumOfFrames = frames->num;

	return frames;
}

void renderFrames(struct frame *frames)
{
	FILE *fh;
	int ERROR=0;
	int i;
	struct dataset *ds;
	extern int Argc;
	extern char **Argv;
	extern GLuint *ThePlot;
	GLuint *t;
	
	
	/* Open frame - Fail if can't */
	i=0;

	glutInit(&Argc, Argv);
	initDisplay();
	setCameraDefaults();


	ThePlot = malloc(sizeof(GLuint));
	
	while (i<frames->num && ERROR !=1) {
		
		fh = fopen(frames->framepath[i], "r");
		if (fh == NULL) {
			printf("ERROR: Can't open frame %s\n", frames->framepath[i]);
			ERROR = 1;
		
		} else {
		
			ds = readDataFile(fh);
			
			if (ds == NULL) {
				
				printf("Error reading data from file %s\n", frames->framepath[i]);
			
			} else {
				
				fclose(fh);
				t = realloc(ThePlot, sizeof(GLuint) * (i+1));
				
				if (t == NULL) {
					printf("Error reallocating memory for display list\n");
					free(ThePlot);
					return;
				}

				ThePlot = t;
				
				ThePlot[i] = glGenLists(1);
				glNewList(ThePlot[i], GL_COMPILE);
				plotGraph(ds);
				glEndList();
			}
			/* Next Frame */
			i++;

		}
	}
}

void displayMovie(void)
{
	int i;
	extern GLuint *ThePlot;
	extern int NumOfFrames;

	for (i=0; i<NumOfFrames; i++) {
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		drawAxis();
		glCallList(ThePlot[i]);
		printf("Rendered Frame %d\n", i);
		glPopMatrix();
		glutSwapBuffers();
	}
}

void saveMovie(void)
{
	int i;
	extern GLuint *ThePlot;
	extern int NumOfFrames;
	char fn[BUFSIZE];
	char framenum[BUFSIZE];
	extern char *MovieBaseDir;
	extern int PLACE_LIGHT;
	extern float LightDetails[3];
	extern int SAVE_MOVIE;

	for (i=0; i<NumOfFrames; i++) {
		glClear(GL_COLOR_BUFFER_BIT);
		if (PLACE_LIGHT == 1) {
			addLight(LightDetails[0], LightDetails[1], LightDetails[2]);
		}

		glPushMatrix();
		drawAxis();
		glCallList(ThePlot[i]);
		printf("Rendered Frame %d\n", i);
		glPopMatrix();
		glutSwapBuffers();

		/* Only saved if desired */
		if (SAVE_MOVIE==1) {
			strcpy(fn, MovieBaseDir);
			strcat(fn, "/frame"); /* FIXME: This breaks Windows */
			sprintf(framenum,"%i", i);
			strcat(fn, framenum);
			strcat(fn, ".png");
		}

		/* Use our built in routines for this */
		saveGraph(fn); 
		//takeScreenshot(fn, SCREENSHOT_PPM);
	}
	if (SAVE_MOVIE==1) {
		exit(0);
	}
}

