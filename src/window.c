/**
 * @copyright
 * @file window.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body handling window
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "window.h"

/** @addtogroup WindowGroup
 *  @{
 */
/**
 * @brief window data strcture window
 *
 */
struct window {
	int id; /**< Window ID */
	int width; /**< width of the window */
	int height; /**< height of the window */
	int no_img; /**< Number of images in pixels array */
	double * pixels; /**< Pixel color */
	int * labels; /**< Label */
	win_type_e window_type; /**< Window type */
};
/** @} */ // End of addtogroup WindowGroup

window_t * add_window (int id, int no_img, int width, int height, double * pixels, int * labels, win_type_e window_type) {
	window_t * window = NULL;

	window = (window_t *) malloc(sizeof(window_t));
	if (window==NULL) {
		LOG_ERROR("Can't allocate memory for a new window data strcuture window_t");
	}
	// ===========================================================================
	// ID handler
	// ===========================================================================
	window->id = id;
	LOG_INFO(MEDIUM,"[New window structure] Set ID handler of window data struct to %0d",  id);

	// ===========================================================================
	// Dimensions
	// ===========================================================================
	ASSERT (width>0);
	window->width = width;
	LOG_INFO(MEDIUM,"[New window structure] Set window width of window data struct to %0d",  width);

	ASSERT (height>0);
	window->height = height;
	LOG_INFO(MEDIUM,"[New window structure] Set window height of window data struct to %0d",  height);

	// ===========================================================================
	// Pixels
	// ===========================================================================
	// Total number of units to allocate
	ASSERT (no_img>0);
	window->no_img = no_img;
	LOG_INFO(MEDIUM,"[New window structure] Set number of images in pixels of window data struct to %0d",  no_img);

	ASSERT(pixels!=NULL);
	window->pixels = pixels;

	window->window_type = window_type;

	// ===========================================================================
	// Labels
	// ===========================================================================
	// If labels is NULL, it will be ignored
	if (labels == NULL) {
		LOG_INFO(ZERO,"[New window structure] Array of labels is NULL. It will be ignored.");
	}
	window->labels = labels;
	LOG_INFO(ZERO,"[New window structure] Created window data structure: ID ->  %0d Window dimensions -> (width %0d, height %0d) number of images -> %0d ", id, width, height, no_img);

	return window;
}

win_type_e get_window_type (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window type] Type of content shown in window: %s",  win_type_to_str(window->window_type));
	return window->window_type;
}

int get_no_img (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get number of images] Number of images in pixels array of window data structure window_t: %0d",  window->no_img);
	return window->no_img;
}

int get_id (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get ID handler] ID handler of dimensions of window data structure window_t: %0d",  window->id);
	return window->id;
}

int get_width (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window width] Width of window data structure window_t: %0d",  window->width);
	return window->width;
}

int get_height (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window height] Height of window data structure window_t: %0d",  window->height);
	return window->height;
}

double * get_pixels (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window pixels] Pixels of window data structure window_t");
	ASSERT((window->pixels) != NULL);
	return window->pixels;
}

int * get_labels (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window labels] Labels of window data structure window_t");
	ASSERT((window->labels) != NULL);
	return window->labels;
}

void set_window_type (window_t ** window, win_type_e window_type) {
	ASSERT((*window) != NULL);
	(*window)->window_type = window_type;
	LOG_INFO(DEBUG,"[Set window type] Set window type: %s",  win_type_to_str((*window)->window_type));
}

void set_no_img (window_t ** window, int no_img) {
	ASSERT((*window) != NULL);
	(*window)->no_img = no_img;
	LOG_INFO(DEBUG,"[Set number of images] Set number of images in pixels array of window data structure window_t: %0d",  (*window)->no_img);
}

void set_id (window_t ** window, int id) {
	ASSERT((*window) != NULL);
	(*window)->id = id;
	LOG_INFO(DEBUG,"[Set ID handler] Set ID handler of dimensions of window data structure window_t: %0d",  (*window)->id);
}

void set_width (window_t ** window, int width) {
	ASSERT((*window) != NULL);
	(*window)->width = width;
	LOG_INFO(DEBUG,"[Set window width] Set width of window data structure window_t: %0d",  (*window)->width);
}

void set_height (window_t ** window, int height) {
	ASSERT((*window) != NULL);
	(*window)->height = height;
	LOG_INFO(DEBUG,"[Set window height] Set height of window data structure window_t: %0d",  (*window)->height);
}

void set_pixels (window_t ** window, double * pixels) {
	ASSERT((*window) != NULL);
	(*window)->pixels = pixels;
	LOG_INFO(DEBUG,"[Set window pixels] Set pixels of window data structure window_t");
}

void set_labels (window_t ** window, int * labels) {
	ASSERT((*window) != NULL);
	(*window)->labels = labels;
	LOG_INFO(DEBUG,"[Set window labels] Set labels of window data structure window_t");
}

void delete_window (window_t * window) {
	if (window != NULL) {
		free_memory(window->pixels);
		LOG_INFO(DEBUG,"[Delete window] Free window pixels -> COMPLETED");
		free_memory(window->labels);
		LOG_INFO(DEBUG,"[Delete data] Free labels -> COMPLETED");
	}

	free_memory(window);
	LOG_INFO(DEBUG,"[Delete window] Free window data structure -> COMPLETED");
}

char * win_type_to_str (win_type_e window_type) {
	char * window_type_str = NULL;

	window_type_str = (char *) malloc(MAX_WINDOW_TYPE_LENGTH*sizeof(char));
	if (window_type_str==NULL) {
		LOG_ERROR("Can't allocate memory for string for data type");
	}

	switch (window_type) {
		case DATASET:
			strcpy(window_type_str, "DATASET");
			break;
		default:
			LOG_ERROR("Unknown window type. Can't generate string with window type name");
			break;
	}

	return window_type_str;
}

size_t window_size() {
	return (sizeof(window_t));
}
