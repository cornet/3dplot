/*! \file graph.h
 *  \brief Routines for plotting the graph itself
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include "main.h"

/* Function definitions */

/*! Defines the material used on the graph
 */
void defineMaterial(void);

/*! Computers the Red value for a height on the graph
 * 
 * This function assumes the height to be between -1 and 1
 * \param height Height of point.
 * \return Red colour value as used by OpenGL (i.e. between 0.0 and 1.0)
 */
float redMap(float height);

/*! Computers the Green value for a height on the graph
 * 
 * This function assumes the height to be between -1 and 1
 * \param height Height of point.
 * \return Green colour value as used by OpenGL (i.e. between 0.0 and 1.0)
 */
float greenMap(float height);

/*! Computers the Blue value for a height on the graph
 *
 * This function assumes the height to be between -1 and 1
 * \param height Height of point.
 * \return Blue colour value as used by OpenGL (i.e. between 0.0 and 1.0)
 */
float blueMap(float height);

/*! Plots the graph itself
 *
 * This parses the dataset and plots the point.
 * It assumes that the dataset is scaled so that all points lie between -1 and 1
 *
 * \param ds dataset to plot
 */
void plotGraph(struct dataset *ds);

#endif /* graph.h */
