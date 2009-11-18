/*! \file control.h
 *  \brief Routines for processing key presses.
 *
 * 
 * Handles all key presses as well as any camera movement related functions.
 * Also defined are the funtions used by OpenGL as the key handling functions.
*/

#ifndef _CONTROL_H
#define _CONTROL_H

/*! Updates Spherical Coordinates of the Camera
 */
void updateSphericalCoords(void);

/*! Updates Cartesian Corrdinates of the Camera
 */
void updateCartesianCoords(void);

/*! Moves the Camera to its new position
 */
void updateCamera(void);

/*! Function used by glutKeyboardFunc()
 * 
 * Handles all alphanumeric key presses and mouse movement
 * \param key Key pressed
 * \param x Mouse X coordinate
 * \param y Mouse Y coordinate
 */
void processNormalKeys(unsigned char key, int x, int y);

/*! Function used by glutSpecialFunc()
 * 
 * Handles non-alphanumeric key presses and mouse movement
 * \param key Key pressed
 * \param x Mouse X coordinate
 * \param y Mouse Y coordinate
 */
void processSpecialKeys(int key, int x, int y);

#endif /* control.h */

