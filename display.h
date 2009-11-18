/*! \file display.h
 *  \brief Routines for handling OpenGL Display functions
 */

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "main.h"

/*! Defines window defaults */
enum window_defaults {
	DEF_WIN_WIDTH = 200,  /*!< Window width in pixels                */
	DEF_WIN_HEIGHT = 200, /*!< Window height in pixels               */
	DEF_WIN_X_POS = 100,  /*!< Window x position from left in pixels */
	DEF_WIN_Y_POS = 100   /*!< Window y position from top in pixels  */
};

/*! Define camera defaults
 *  
 *  Used by gluLookAt.
 */
enum camera_defaults {
	CAMX = 5,      /*!< x position coordinate  */
	CAMY = 0,     /*!< y position coordinate  */
	CAMZ = 0,      /*!< z position coordinate  */
	CENTREX = 0,   /*!< x centre point coordinate */
	CENTREY = 0,   /*!< y centre point coordinate */
	CENTREZ = 0,   /*!< z centre point coordinate */
	UPVECTORX = 0, /*!< x up vector value */
	UPVECTORY = 0, /*!< y up vector value */
	UPVECTORZ = 1  /*!< z up vector value */
};

/*! Initialise the display
 * 
 * - Initalise Window
 * - Clear Background
 * - Set up camera
 */
void initDisplay(void);

/*! Sets the camera defaults
 */
void setCameraDefaults(void);

/*! Function to be called when window is resized
 *
 * \param w New width of window
 * \param h New height of window
 */
void reshape(int w, int h);

/*! Draw the graph axes
 *
 * Each axis from -1 to 1, all data will be scaled.
 */
void drawAxis(void);

/*! The glutDisplayFunc() display function.
 *
 * 
 * - Call the drawAxis() function
 * - Plot the graph (held as a GL List)
 */
void renderGraph(void);

/*! Function to do the initial drawing of the graph */
void drawGraph(struct dataset *ds);

#endif /* display.h */
