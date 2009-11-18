
#include <stdio.h>
#include <stdlib.h>
#include <magick/api.h>

#if defined(__APPLE__) && (__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "main.h"

int TGAShot(unsigned char *image, int width, int height, FILE *fh)	
{
	struct TGAheader {
		unsigned char idfield_len;
		unsigned char cmap_type;
		unsigned char image_type;
		unsigned char cmap_spec[5];
		unsigned char x_orig[2];
		unsigned char y_orig[2];
		unsigned char width[2];
		unsigned char height[2];
		unsigned char pixel_size;
		unsigned char image_desc;
	} __attribute__((packed)) header;

	int i;

	/* Write Header */
	header.idfield_len = 0;
	header.cmap_type = 0;
	header.image_type = 2;
	for (i = 0; i < 5; i++) {
		header.cmap_spec[i] = 0;
	}
	for (i = 0; i < 2; i++) {
		header.x_orig[i] = 0;
		header.y_orig[i] = 0;
	}
	/* Lo bits */
	header.width[0] = width & 0xFF;
	/* Hi bits */
	header.width[1] = (width >> 8) & 0xFF;
	header.height[0] = height & 0xFF;
	header.height[1] = (height >> 8) & 0xFF;
	header.pixel_size = 24;
	header.image_desc = 0;

	fwrite(&header, sizeof(header), 1, fh);
	fwrite(image, sizeof(unsigned char), width*height*3, fh);

	return 0;
}

int takeScreenshot(char *fn)
{
	unsigned char *image = NULL;
	int retval;
	int width, height;
	int x, y;
	int viewport[4]; /* x, y, width, height */
	FILE *fh;

	
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = viewport[0];
	y = viewport[1];
	width = viewport[2];
	height = viewport[3];
	
	image = (unsigned char*)malloc(sizeof(unsigned char)*width*height*3);
	if (!image) {
		printf("Failed to allocate memory for image\n");
		return -1;
	}

	fh = fopen(fn, "wb");
	if (fh == NULL) {
		printf("Can't open file to take screenshot\n");
		return NULL;
	} 
	/* Makes sure we are getting right buffer (the front one) */
	glReadBuffer(GL_FRONT);
	glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, image);
	retval = TGAShot(image, width, height, fh);
	fclose(fh);
	/* Free up memory */
	free(image);

	return retval;
}


int saveGraph(char *fn)
{
	MagickWand *image;

	takeScreenshot("/tmp/tmp.tga");

	image = NewMagickWand();
	MagickReadImage(image, "/tmp/tmp.tga");
	MagickWriteImage(image, fn);

	DestroyMagickWand(image);

	return 0;
}


