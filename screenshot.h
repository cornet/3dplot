/*! \file screenshot.h
 *  \brief Built in funtions for creating screenshots
 *
 *  Now mostly redundant due to using ImageMagicK libs
 */

#ifndef _SCREENSHOT_H
#define _SCREENSHOT_H

/*! Defines the built in types of screenshot avaliable
 */
typedef enum {
	SCREENSHOT_PPM,   /*!< PPM - http://netghost.narod.ru/gff/vendspec/pbm/ppm.txt    */
	SCREENSHOT_TGA,   /*!< TGA - http://netghost.narod.ru/gff/vendspec/tga/tga.txt    */
	SCREENSHOT_BMP,   /*!< BMP - http://netghost.narod.ru/gff/vendspec/micbmp/bmp.txt */
	SCREENSHOT_RAW    /*!< RAW glReadPixel dump */
} SCREENSHOT_FORMAT;

/*! Takes the screenshot using one of the built in functions
 *
 * \param fn File name to save to
 * \param format Format to save to
 * \return 0 if successful -1 of not
 */
int takeScreenshot(char *fn, SCREENSHOT_FORMAT format);

/*! Writes BMP screenshot
 * \param image Image to save - dump of glReadPixels
 * \param width Width of image
 * \param height Height of image
 * \param fh File to save to
 * \return 0 if successful
 */
int BMPShot(unsigned char *image, int width, int height, FILE *fh);

/*! Writes TGA screenshot
 * \param image Image to save - dump of glReadPixels
 * \param width Width of image
 * \param height Height of image
 * \param fh File to save to
 * \return 0 if successful
 */
int TGAShot(unsigned char *image, int width, int height, FILE *fh);

/*! Writes PPM screenshot
 * \param image Image to save - dump of glReadPixels
 * \param width Width of image
 * \param height Height of image
 * \param fh File to save to
 * \return 0 if successful
 */
int PPMShot(unsigned char *image, int width, int height, FILE *fh);

/*! Writes RAW screenshot
 * \param image Image to save - dump of glReadPixels
 * \param width Width of image
 * \param height Height of image
 * \param fh File to save to
 * \return 0 if successful
 */
int RAWShot(unsigned char *image, int width, int height, FILE *fh);
#endif /* screenshot.h */
