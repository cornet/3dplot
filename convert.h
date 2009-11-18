/*! \file convert.h
 *  \brief Routines for converting plot data
 *
 *  3dplot deals with parametric data (PARA). Other formats are supported by
 *  3dplot but are converted to parametric.
 *  The following data types are supported:
 *  - PARA
 *    Parametric data, this is the default
 *  - FUNC
 *    Function plot data
 *  - KURV 
 *    Kurv plot data
 *  See the FILE_SPEC doc for full details
*/

#ifndef _CONVERT_H
#define _CONVERT_H


/*! Width of line used to plot KURV Plots */
#define STRIPWIDTH 0.1

/* Define Functions */

/*! Converts Function data to Parametric
 *
 * \param ds Pointer to data set to convert
 * \return Pointer to converted dataset
 */
struct dataset *funcToPara(struct dataset *ds);

/*! Converts Kurv (Curve) data to Parametric
 *
 * \param ds Pointer to data set to convert
 * \return Pointer to converted dataset
 */
struct dataset *kurvToPara(struct dataset *ds);

/*! Converting data to parametric
 *
 * This is the function that should be called.
 * It detects what type the data is and then calls one of
 * specific converting functions.
 *
 * \param type Sting containing plot type as defined in the data file 5 chars includs NULL terminator
 * \param ds Pointer to data set to convert
 * \return Pointer to converted dataset
 */
struct dataset *convertToPara(char type[5], struct dataset *ds);
#endif /* convert.h */
