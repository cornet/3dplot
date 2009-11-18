/* plot.h
* Different types of plots and their properties
*/
#ifndef _PLOT_H
#define _PLOT_H

#include <stdio.h>
#include <stdlib.h>



typedef struct {
    const char *keyword;	/* Keyword used in datafile */
    plot_type type; 		/* Type ident used for reference in program */
} strtoplot;

/* The default plot used in case of no definition line in datafile */
#define DEFAULT_PLOT FUNC;

#endif /* plot.h */
