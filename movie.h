/*! \file movie.h
 *  \brief Routines for production of movies
 */


#ifndef _MOVIE_H_
#define _MOVIE_H_

/*! Defines buffer size */
enum buffer {
	BUFSIZE = 1025
};

/*! Holds frame locations */
struct frame {
	int num;         /*!< Number of frames              */
	char (*framepath)[BUFSIZE]; /*!< Holds full path to frame data */
};

/*! Frees memory from unused frames
 * 
 * \param frames Frames to destroy
 */
void destroyFrames(struct frame *frames);

/*! Loads frame names into an array
 *
 *  \param fh File containing data file names
 *  \return array containing list of files
 */
struct frame* readFrames(char *fn);

/*! Renders the frams to display lists
 *
 * \param frames Frames to render
 * \param path Path to save frames to
 */
void renderFrames(struct frame *frames);

/*! Display function used by glutDisplayFunc
 */
void displayMovie(void);

/*! Function to display and save the movie to a file
 *
 * again used by glutDisplayFunc
 */
void saveMovie(void);


#endif /* movie.h */
