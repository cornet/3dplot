/* convert.c
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "file.h"
#include "convert.h"

struct dataset *funcToPara(struct dataset *ds)
{
	double *t; /* Used to expand arrays */
	int i,j;
	
	t = malloc(sizeof(double) * ds->X * ds->Y);
	/* x(s,t) - Repeat all the current x values T times */
	for (i=0; i < ds->Y; i++) {
		for (j=0; j < ds->X; j++) {
			t[ds->Y * i + j] = ds->x[j];
		}
	}
	ds->x = t;
	
	/* y(s,t) - Repeat each y value S times */
	for (i=0; i < ds->Y; i++) {
		for(j=0; j < ds->X; j++) {
			t[ds->X * i + j] = ds->y[i];
		}
	}
	ds->y = t;
	
	return ds;
}

struct dataset *kurvToPara(struct dataset *ds)
{
	double *tx, *ty, *tz; /* Used to expand arrays */
	int i;
	float width; /* Width of strip used */
	/* Angle of rotation from line connecting adjcent
		points to horizontal - anticlockwise */
	double alpha;
		
	width = STRIPWIDTH;
	
	tx = malloc(sizeof(double) * ds->X * 2);
	ty = malloc(sizeof(double) * ds->X * 2);
	tz = malloc(sizeof(double) * ds->X * 2);
	
	/* x(s,t) points of one side of strip */
	for (i=0; i < ds->X - 1; i++) {
		alpha = atan( (ds->y[i + 1] - ds->y[i]) /
					  (ds->x[i + 1] - ds->y[i]) );
		tx[i] = ds->x[i] - (width/2) * sin(alpha);
		tx[i + ds->X] = ds->x[i] + (width/2) * sin(alpha);
		ty[i] = ds->y[i] + (width/2) * cos(alpha);
		ty[i + ds->X] = ds->y[i] + (width/2) * cos(alpha);
		tz[i] = ds->z[i];
		tz[i + ds->X] = ds->z[i + 1];
		
		/* If on penultmate point then need to calculate final points */
		if ( i == ds->X - 2 ) {
			tx[i + 1] = ds->x[i + 1] - (width/2) * sin(alpha);
			tx[i + ds->X + 1] = ds->x[i + 1] + (width/2) * sin(alpha);
			ty[i + 1] = ds->y[i + 1] + (width/2) * cos(alpha);
			ty[i + ds->X + 1] = ds->y[i + 1] + (width/2) * cos(alpha);
			tz[i + 1 ] = ds->z[i + 1];
			tz[i + ds->X + 1] = ds->z[i + 1];
		}
	}
	
	ds->x = tx;
	ds->y = ty;
	ds->z = tz;
	ds->Y = 2;
	
	return ds;
}

struct dataset *convertToPara(char type[5], struct dataset *ds)
{
	if (strncmp(type, "", 4)) {
		ds = funcToPara(ds);
		printf("No type, assumed func\n");
	}
	if (strncmp(type, "func", 4)) {
		ds = funcToPara(ds);
		printf("funcToPara\n");
	}
	if (strncmp(type, "kurv", 4)) {
		ds = kurvToPara(ds);
		printf("kurvToPara\n");
	}
	
	return ds;
}

