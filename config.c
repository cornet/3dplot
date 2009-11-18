/*
 * config.c
 * Nathan Howard
 * Routines to read and write to config files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

#define MAX_LINE_LENGTH 1024

int readConfigFile(FILE *fh)
{
	char buf[1025];
	char line[1025];
	int i,j,k;
	int EOL=0; /* End of Line flag */
	char option[512]; /* The option we are changing */
	char setting[512]; /* The setting its set to */
	struct config conf; /* Holds config */
	
	while (fgets(buf, sizeof(buf), fh) != NULL ) {
	/* Ditch Comments and leading any whitspaces */
		EOL=0;
		j = 0; i = 0;

		/* If 1st char of line is a # then set EOF
		 * This should stop reading od most unnecessary lines */
		if ( buf[0] == '#' ) {
			EOL = 1;
		}

		while(i < sizeof(buf) && EOL != 1) {
			switch (buf[i]) {
				case '#':
					EOL = 1;
					/*printf("EOL\n");*/
					line[j] = '\0';
				break;
				case '\n':
					EOL = 1;
					line[j] = '\0';
					break;
				case ' ':
					i++;
				break;
				default:
				line[j] = buf[i];
				i++; j++;
				break;
			}
		}

		/*printf("Buffer: %s, Line: %s\n", buf, line);*/

		/* Read option */
		/* Note: j is length of line */
		i=0;
		while (line[i] != '=' && i < j) {
			option[i] = line[i];
			i++;
		}

		option[i] = '\0';	
		i++; /* Skip over '=' */
		
		/* Read setting */
		k=i; /* Current position in line */
		i=0;
		while (k < j) {
			setting[i] = line[k];
			i++; k++;
		}
		setting[i] = '\0';
		
		printf("%s = %s\n", option, setting);

		/* Clear out buffer */
		for(i=0; i<sizeof(line); i++) {
			line[i] = '\0';
		}
		for(i=0; i<sizeof(buf); i++) {
			buf[i] = '\0';
		}

		/* Compare and assign variables */
		if ( strcmp(option,"WinHeight") == 0 ) {
			conf.WinHeight = strtod(setting, NULL);
			printf("WinHeight = %d\n", conf.WinHeight);
		}
		if ( strcmp(option,"WinWidth") == 0 ) {
			conf.WinWidth = strtod(setting, NULL);
			printf("WinWidth = %d\n", conf.WinWidth);
		}
		if ( strcmp(option,"WinX") == 0 ) {
			conf.WinX = strtod(setting, NULL);
			printf("WinX = %d\n", conf.WinX);
		}
		if ( strcmp(option,"WinY") == 0 ) {
			conf.WinY = strtod(setting, NULL);
			printf("WinY = %d\n,", conf.WinY);
		}
		if ( strcmp(option,"CameraX") == 0 ) {
			conf.Camera[0] = strtod(setting, NULL);
			printf("CameraX = %f\n", conf.Camera[0]);
		}
		if ( strcmp(option,"CameraY") == 0 ) {
			conf.Camera[1] = strtod(setting, NULL);
			printf("CameraY = %f\n", conf.Camera[1]);
		}
		if ( strcmp(option,"CameraZ") == 0 ) {
			conf.Camera[2] = strtod(setting, NULL);
			printf("CameraZ = %f\n", conf.Camera[2]);
		}
		if ( strcmp(option,"CentreX") == 0 ) {
			conf.Centre[0] = strtod(setting, NULL);
			printf("CentreX = %f\n", conf.Centre[0]);
		}
		if ( strcmp(option,"CentreY") == 0 ) {
			conf.Centre[1] = strtod(setting, NULL);
			printf("CantreY = %f\n", conf.Camera[1]);
		}
		if ( strcmp(option,"CentreZ") == 0 ) {
			conf.Centre[2] = strtod(setting, NULL);
			printf("CantreZ = %f\n", conf.Centre[2]);
		}
		if ( strcmp(option,"UpVectorX") == 0 ) {
			conf.UpVector[0] = strtod(setting, NULL);
			printf("UpVectorX = %f\n", conf.UpVector[0]);
		}
		if ( strcmp(option,"UpVectorY") == 0 ) {
			conf.UpVector[1] = strtod(setting, NULL);
			printf("UpVectorY = %f\n", conf.UpVector[1]);
		}
		if ( strcmp(option,"UpVectorZ") == 0 ) {
			conf.UpVector[2] = strtod(setting, NULL);
			printf("UpVectorZ = %f\n", conf.UpVector[2]);
		}

	}

	return 0;
}
