/*! \file config.h
 *  \brief Routines for reading and writing the config files.
 *
 *  Config files are used as the main input to 3dplot.
 *  They contain all the variables to recreate the plot, viewport, lights etc
 *  In general the extension .3dp should be used.
 *  Format of config file is as follows:
 *  - One line per variable set
 *  - Comments defined using # and continue to EOL
 *  - Variables are set by \<variable name\> = \<setting\>
 *  - Free formating in terms of whitespaces
 *  - Invalid lines are ignored
 *  
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include "lights.h"


/*! Structure to hold all config variables
 *  
 *  The following information is held in this structure:
 *  - Window Information
 *    -# Window Dimentions
 *    -# Window Position
 *  - Camera Information Used by gluLookAt()
 *  
 */
struct config {
	int WinHeight; /*!< Window Height     */
	int WinWidth;  /*!< Window Width      */
	int WinX;      /*!< Window X Position */
	int WinY;      /*!< Window Y Position */
	
	float Camera[3];   /*!< X,Y,Z Coordinates of Camera                       */
	float Centre[3];   /*!< X,Y,Z Coordinates of Centre Focus Point of Camera */
	float UpVector[3]; /*!< X,Y,Z Values for Up Vector of the Camera          */
	
	/* Lights */
};

/*! Reads configuration file
 * 
 * \param fh file pointer to config file
 * \return 0 if file read ok, -1 otherwise
 */
int readConfigFile(FILE *fh);

#endif /* config.h */
