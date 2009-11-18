/*! \file lights.h
 *  \brief Routines for dealing with lights
 *  
 */

#ifndef _LIGHTS_H
#define _LIGHTS_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* To hold information for Lights */

/*! Holds Light infomation */
struct light {
    GLenum lightid;	/*!< Set to LIGHT[0|1|...] !FIXME: needs to be implemented */
    float *position; /*!< position of light                                     */
    float *diffuse;  /*!< Diffusion of light used by GL_DIFFUSE                 */
    float *specular; /*!< Specular of light used by GL_SPECULAR                 */
};


/*! Adds a light
 * 
 * \param x x coordinate of light
 * \param y y coordinate of light
 * \param z z coordinate of light
 * \return lightid of light FIXME: needs to be implemented
 */
int addLight(float x, float y, float z);

/*! Frees up memory for unused light
 * 
 * \param lightID OpenGL light ID
 */
void destroyLight(int lightID);

/*! Delets a light
 *
 * \param lightID OpenGL light ID
 */
void delLight(int lightID);

/*! Moves a light relative to its current position
 *
 * \param lightid ID of light to move TODO: Not supported yet
 * \param x New relative x position
 * \param y New relative y position
 * \param z New relative z position
 * \param w New relative w position - if 0 then light is positional.
 */
void moveLight(int lightid, float x, float y, float z, float w);

#endif /* lights.h */

