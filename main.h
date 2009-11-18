/*! \file main.h
 *
 *  main.h
 *  3dplot
 *
 *  Created by Nathan on Thu Oct 23 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MAIN_H
#define _MAIN_H

/*! Structure to hold the current data being worked on
 */
struct dataset
{
    long X;    /*!< Number of x values in dataset */
    long Y;    /*!< Number of y values in dataset */
    double *x; /*!< x values */
    double *y; /*!< y values */
    double *z; /*!< z values */
};

int expandFloatOption(float *values, char *string);
int expandIntOption(int *values, char *string);
#endif /* main.h */
