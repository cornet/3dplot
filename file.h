/*! \file file.h
 * \brief Routines for dealing with data files
 * 
*/
#ifndef _FILE_H
#define _FILE_H

#include "main.h"

/* Function definitions */

/*! Gets the number of X values in the dataset
 * 
 * \param ds Pointer to dataset
 * \return Number of values.
 */
long getxNum (struct dataset *ds);

/*! Gets the number of Y values in the dataset
 * 
 * \param ds Pointer to dataset
 * \return Number of values.
 */
long getyNum (struct dataset *ds);

/*! Gets the number of Z values in the dataset
 * 
 * \param ds Pointer to dataset
 * \return Number of values.
 */
long getzNum (struct dataset *ds);

/*! Frees up memory used by unused dataset
 *
 * \param ds Dataset to free up
 */
void destroyDataSet(struct dataset *ds);

/*! Reads the data file into a data set
 *
 * \param fh Pointer to data file
 * \return Dataset containing data from file.
 */
struct dataset* readDataFile(FILE *fh);

#endif /* file.h */
