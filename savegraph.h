/*! \file savegraph.h
 *  \brief Routines for saving the output to image files
 *
 *  These routines will save the image to any desired format
 *  using the ImageMagick routines.
 */

#ifndef _SAVEGRAPH_H
#define _SAVEGRAPH_H

/*! Saves cuurent screen to TGA file
 *
 * Used so then saveGraph() can convert to desired format
 * \param image Contents image via of glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, image)
 * \param width Width of image
 * \param height Height of image
 * \param fh File to save to
 * \return 0 if succesful
 * 
 */
int TGAShot(unsigned char *image, int width, int height, FILE *fh);

/*! Takes a screenshot and calls TGAShot()
 *
 * \param fn File name to wrte to.
 * \return 0 if successful -1 if not.
 */
int takeScreenshot(char *fn);

/*! Saves current screen to a file
 *
 * The output format is detected from the filename extension
 * \param fn Filename to save to
 * \return 0 if sucessful -1 if not
 */
int saveGraph(char *fn);


#endif /* savegraph.h */
