/*
 * screenshot.c
 * Saves screenshot to BMP, TGA or PPM
 */

#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__) && (__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "screenshot.h"

int BMPShot(unsigned char *image, int width, int height, FILE *fh)
{
	struct BMPheader {
		unsigned short type;
		unsigned int size;
		unsigned short res1;
		unsigned short res2;
		unsigned int offset;
	} __attribute__((packed)) header;

	struct BMPInfo {
		unsigned int size;
		unsigned int width;
		unsigned int height;
		unsigned short planes;
		unsigned short bit_count;
		unsigned int comp;
		unsigned int sizeimage;
		unsigned int x_pels_per_meter;
		unsigned int y_pels_per_meter;
		unsigned int clr_used;
		unsigned int clr_important;
	} __attribute__((packed)) info;

	/* Write Header */
	header.type = 'B' | 'M' << 8;
	header.size = sizeof(header) + sizeof(info) + width * height * 3;
	header.res1 = header.res2 = 0;
	header.offset = sizeof(header) + sizeof(info);
	info.size = sizeof(info);
	info.width = width;
	info.height = height;
	info.planes = 1;
	info.bit_count = 24;
	info.comp = 0;
	info.sizeimage = width * height * 3;
	info.x_pels_per_meter = info.y_pels_per_meter = 0;
	info.clr_used = 0;
	info.clr_important = 0;

	fwrite(&header, sizeof(header), 1, fh);
	fwrite(&info, sizeof(info), 1, fh);

	fwrite(image, sizeof(unsigned char), height*width*3, fh);

	return 0;

}

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

int PPMShot(unsigned char *image, int width, int height, FILE *fh)
{
	unsigned char *row;
	int i;

	/* Wirte Header */
	fprintf(fh, "P6\n#GL Screenshot file.ppm\n%d %d\n%d\n", width, height, 255);

	/* GL returns the data upside down */
	for (i = height - 1; i >= 0; i--) {
		row = (unsigned char*)image + width * i * 3;
		fwrite(row, sizeof(unsigned char), width*3, fh);
	}

	return 0;
}

int RAWShot(unsigned char *image, int width, int height, FILE *fh)
{
	fprintf(fh, "%d\n%d\n", width, height);
	fwrite(image, sizeof(unsigned char), height*width*3, fh);

	return 0;
}	


int takeScreenshot_(char *fn, SCREENSHOT_FORMAT format)
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

	switch(format) {
		case SCREENSHOT_BMP:
			fh = fopen(fn, "wb");
			if (fh == NULL) {
				printf("Can't open file to take screenshot\n");
				return NULL;
			}
			glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, image);
			retval = BMPShot(image, width, height, fh);
			fclose(fh);
			break;
		case SCREENSHOT_TGA:
			fh = fopen(fn, "wb");
			if (fh == NULL) {
				printf("Can't open file to take screenshot\n");
				return NULL;
			}
			glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, image);
			retval = TGAShot(image, width, height, fh);
			fclose(fh);
			break;
		case SCREENSHOT_PPM:
			fh = fopen(fn, "wb");
			if (fh == NULL) {
				printf("Can't open file to take screenshot\n");
				return NULL;
			}
			glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
			retval = PPMShot(image, width, height, fh);
			fclose(fh);
			break;
		case SCREENSHOT_RAW:
			fh = fopen(fn, "wb");
			if (fh == NULL) {
				printf("Can't open file to take screenshot\n");
				return NULL;
			}
			glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
			retval = RAWShot(image, width, height, fh);
			fclose(fh);
			break;
		default:
			printf("Invalid format %d\n", format);
			retval -1;
			break;
	}

	/* Free up memory */
	free(image);

	return retval;
}

