/*
 *  main.c
 *  3dplot
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "display.h"
#include "control.h"
#include "file.h"
#include "graph.h"

/*#include "screenshot.h" */
#include "config.h"
#include "movie.h"


/*
 * Global Vairables
 * This is the ONLY place global variables should be declared
 */


/*
 * Hold argv and argc stuff,
 * Needs to be passed to gl init function
 */
int Argc;
char **Argv;

/* 
 * Coordinates Used By glLookAt()
 * Camera[3] : x,y,z coodinates of camera
 * Centre[3] : global coodinates of centre of viewport
 * UpVector[3] : Defines the upward direction of the camera
 */
float Camera[3];
float Centre[3];
float UpVector[3];

/*
 * Spherical Coordinates used for movement
 * Radius
 * Theta - Longitudinal Angle
 * Phi - Lateral Angle
 */
float Radius; 
float Theta;  /* Longitudinal Angle */
float Phi;    /* Lateral Angle      */

/*
 * Scale factors...
 * Hold Max and Min vals of data
 * Gained from first frame, need to kept same for 
 * rest of frames
 */
int FIRST_FRAME=1;
float MaxVal;
float MinVal;

/*
 * Flags and Variables passed from command line
 */
FILE *ConfigFile;

int COLOUR=0;
float Colour[3];

int USE_GRADIENT_FILL=0;
float GradientDetails[6];

int WINDOW_SIZE=0;
int Width;
int Height;

int FLAT_SHADING=0;

int WIREFRAME=0;

int OUTPUT=0;
char *OutputFile;

int SAVE_MOVIE=0;
char *MovieBaseDir;

int MOVIE=0;
char *MovieBaseDir;
char *FrameList;
int NumOfFrames;			/* Holds the number of frames in the plot */

int PLACE_LIGHT=0;
float LightDetails[3];

int AXIS_DEFINED=0;
float Axis[6];

int SET_CAMERA_PLACEMENT=0;
float CameraPlacement[9];

int VERBOSE=0;

GLuint *ThePlot;        /* Holds the Display list for the plot    */

int expandFloatOption(float *values, char *string)
{
	int length;
	int i,j,k;
	char buf[6];

	length = strlen(string);

	for (j=0; j<6; j++) {
		buf[j] = '\0';
	}

	i=0; j=0; k=0;
	while(i<length) {
		if(string[i] == ',') {
			i++;
			values[k] = atof(buf);
			for (j=0; j<6; j++) {
				buf[j] = '\0';
			}
			j=0;
			k++;
		} else {
			buf[j] = string[i];
			i++; j++;
		}
		printf("i = %d \n",i); 
	}

	/* Get final one */
	values[k] = atoi(buf);
	return 0;
}		

int expandIntOption(int *values, char *string)
{
	int length;
	int i,j,k;
	char buf[6];

	length = strlen(string);

	for (j=0; j<6; j++) {
		buf[j] = '\0';
	}

	i=0; j=0; k=0;
	while(i<length) {
		if(string[i] == ',') {
			i++;
			values[k] = atoi(buf);
			for (j=0; j<6; j++) {
				buf[j] = '\0';
			}
			j=0;
			k++;
		} else {
			buf[j] = string[i];
			i++; j++;
		}
		printf("i = %d \n",i); 
	}

	/* Get final one */
	values[k] = atoi(buf);
	return 0;
}

int main(int argc, char **argv)
{
	FILE *fh; 
	struct dataset *ds;
	struct frame *frames;
	int argch;
	int i;

	/* Command line vars */
	int size[2];


	Argc = argc;
	Argv = argv;
	
	/* Read command Line Args */
	while ((argch = getopt(argc, argv, "c:C:g:s:fwo:O:m:hl:t:a:vV")) != -1) {
		switch (argch) {
			case 'c': /* Read Config File */
				ConfigFile = fopen(optarg, "r");
				readConfigFile(ConfigFile);
				fclose(ConfigFile);
				break;
				
			case 'C': /* Set Graph Colour */
				COLOUR=1;
				expandFloatOption(Colour, optarg);
				/* Scale to between 0 and 1 */
				for (i=0; i<3; i++) {
					Colour[i] = Colour[i]/255;
				}
				break;
				
			case 's': /* Set window Geometry */
				WINDOW_SIZE =1;
				expandIntOption(size, optarg);
				Width = size[0];	
				Height = size[1];
				break;
				
			case 'g': /* Do Gradient\heightmap Render */
				USE_GRADIENT_FILL=1;
				expandFloatOption(GradientDetails, optarg); 
				/* Scale */
				for (i=0; i<6; i++) {
					GradientDetails[i] = GradientDetails[i]/255;
				}
				break;

			case 'f': /* Use Flat shading */
				FLAT_SHADING=1;
				break;

			case 'w': /* Render Wireframe Model */
				WIREFRAME=1;
				break;
			
			case 'o': /* Output to file */
				OUTPUT=1;
				OutputFile = malloc(sizeof(optarg));
				strcpy(OutputFile, optarg);
				break;
			
			case 'O': /* Set Movie output dir */
				SAVE_MOVIE=1;
				MovieBaseDir = malloc(sizeof(optarg));
				strcpy(MovieBaseDir, optarg);
				break;
				
			case 'm': /* Render Movie */
				MOVIE=1;
				FrameList = malloc(sizeof(optarg)+sizeof(char));
				strcpy(FrameList, optarg);
				printf("FrameList is %s\n", FrameList);
				break;
			
			case 'l': /* Place a light */
				PLACE_LIGHT=1;
				expandFloatOption(LightDetails, optarg);
				break;
			
			case 'a': /* Set up axis */
				AXIS_DEFINED=1;
				expandFloatOption(Axis, optarg);
				break;
				
			case 't': /* Set Camera Placement */
				SET_CAMERA_PLACEMENT=1;
				expandFloatOption(CameraPlacement, optarg);
				break;

			case 'v': /* Verbose Mode */
				VERBOSE = 1;
				break;
				
			case 'h': /* Show Help */
				break;
				
			case 'V': /* Show Version */
				printf("3dplot v0.1\n");
				return 0;
				break;

			default:
				break;
		}
	}

	if (MOVIE==1) {
		printf("Rendering the movie from list %s\n", FrameList);
		frames = readFrames(FrameList);

		renderFrames(frames);
		glutDisplayFunc(saveMovie);
		glutReshapeFunc(reshape);
		glutMainLoop();
		return 0;
	}

	/* Parse any other args, i.e. the files */
	if (optind < argc) {
		printf("File is %s \n", argv[optind]);
		fh = fopen(argv[optind], "r");
		ds = readDataFile(fh);
	} else {
			printf("No file specified\n");
			return 0;
	}		


	glutInit(&argc, argv);
	initDisplay();
	setCameraDefaults();

	glutDisplayFunc(renderGraph);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	drawGraph(ds);
	
	glutMainLoop();

	return 0;
}
