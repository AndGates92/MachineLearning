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

window_t * add_window (int id, int width, int height, GLfloat * pixels) {
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
	ASSERT(pixels!=NULL);
	window->pixels = pixels;

	return window;
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

GLfloat get_pixels (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get window pixels] Pixels of window data structure window_t");
	ASSERT((window->pixels) != NULL);
	return window->pixels;
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

void set_pixels (window_t ** window, GLfloat * pixels) {
	ASSERT((*window) != NULL);
	(*window)->pixels = pixels;
	LOG_INFO(DEBUG,"[Set window pixels] Set pixels of window data structure window_t");
}

void delete_window (window_t * window) {
	free_memory(window);
	LOG_INFO(DEBUG,"[Delete window] Free window data structure -> COMPLETED");
}

