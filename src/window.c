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
	char * prefix; /**< Name prefix */
	int win_id; /**< Window ID */
	int menu_id; /**< Menu ID */
	int img_ptr; /**< Image pointer */
	int width; /**< width of the window */
	int height; /**< height of the window */
	int no_img; /**< Number of images in pixels array */
	unsigned char * pixels; /**< Pixel color */
	int * labels; /**< Label */
	win_type_e window_type; /**< Window type */
};
/** @} */ // End of addtogroup WindowGroup

window_t * add_window (int win_id, int menu_id, int no_img, int width, int height, unsigned char * pixels, int * labels, win_type_e window_type, char * prefix) {
	window_t * window = NULL;

	window = (window_t *) malloc(sizeof(window_t));
	if (window==NULL) {
		LOG_ERROR("Can't allocate memory for a new window data structure window_t");
	}
	// ===========================================================================
	// ID handler
	// ===========================================================================
	window->win_id = win_id;
	LOG_INFO(MEDIUM,"[New window structure] Set window ID handler of window data struct to %0d",  win_id);

	window->menu_id = menu_id;
	LOG_INFO(MEDIUM,"[New window structure] Set menu ID handler of window data struct to %0d",  menu_id);

	// ===========================================================================
	// Prefix
	// ===========================================================================
	window->prefix = (char *) malloc(MAX_WIN_NAME_PREFIX*sizeof(char));
	if (window->prefix==NULL) {
		LOG_ERROR("Can't allocate memory for the window name prefix of window data structure window_t");
	}
	int prefix_len = 0;
	prefix_len = sprintf(window->prefix, "%s", prefix);
	ASSERT(prefix_len < MAX_WIN_NAME_PREFIX);

	// ===========================================================================
	// Image pointer
	// ===========================================================================
	window->img_ptr = 0;
	LOG_INFO(MEDIUM,"[New window structure] Set image pointer to 0");

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
	int no_pixels = 0;
	no_pixels = no_img * width * height;
	window->pixels = (unsigned char *) malloc(no_pixels*sizeof(unsigned char));
	if (window->pixels==NULL) {
		LOG_ERROR("Can't allocate memory for a new set of pixels in window data structure window_t");
	}
	memcpy(window->pixels, pixels, no_pixels*sizeof(unsigned char));

	window->window_type = window_type;

	// ===========================================================================
	// Labels
	// ===========================================================================
	// If labels is NULL, it will be ignored
	window->labels = NULL;
	if (labels == NULL) {
		LOG_INFO(ZERO,"[New window structure] Array of labels is NULL. It will be ignored.");
	} else {
		window->labels = (int *) malloc(no_img*sizeof(int));
		memcpy(window->labels, labels, no_img*sizeof(int));
	}
	LOG_INFO(ZERO,"[New window structure] Created window data structure: ID -> window %0d menu %0d Window dimensions -> (width %0d, height %0d) number of images -> %0d", win_id, menu_id, width, height, no_img);

	return window;
}

char * get_prefix (window_t * window) {
	char * prefix = NULL;
	prefix = (char *) malloc(MAX_WIN_NAME_PREFIX*sizeof(char));
	if (prefix==NULL) {
		LOG_ERROR("Can't allocate memory for the window name prefix");
	}
	sprintf(prefix, "%s", window->prefix);
	return prefix;
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

int get_menu_id (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get menu ID handler] ID handler of window data structure window_t: %0d",  window->menu_id);
	return window->menu_id;
}

int get_win_id (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get menu ID handler] ID handler of window data structure window_t: %0d",  window->win_id);
	return window->win_id;
}

int get_img_ptr (window_t * window) {
	ASSERT(window != NULL);
	LOG_INFO(DEBUG,"[Get image pointer] Image pointer of window data structure window_t: %0d",  window->img_ptr);
	return window->img_ptr;
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

unsigned char * get_pixels (window_t * window) {
	ASSERT(window != NULL);
	ASSERT((window->pixels) != NULL);

	int no_pixels = 0;
	no_pixels = compute_no_pixels(window);

	unsigned char * pixels = NULL;
	pixels = (unsigned char *) malloc(no_pixels*sizeof(unsigned char));
	if (pixels==NULL) {
		LOG_ERROR("Can't allocate memory for pixels array");
	}
	memcpy(pixels, window->pixels, (no_pixels*sizeof(unsigned char)));

	LOG_INFO(DEBUG,"[Get window pixels] Pixels of window data structure window_t");

	return pixels;
}

unsigned char * get_img (window_t * window, int img_no) {
	ASSERT(window != NULL);
	ASSERT((window->pixels) != NULL);

	int no_pixels_in_img = 0;
	no_pixels_in_img = compute_no_pixels_in_img(window);

	unsigned char * img_pixels = NULL;
	img_pixels = (unsigned char *) malloc(no_pixels_in_img*sizeof(unsigned char));
	if (img_pixels==NULL) {
		LOG_ERROR("Can't allocate memory for image pixels array");
	}
	memcpy(img_pixels, (window->pixels + (img_no*no_pixels_in_img)), (no_pixels_in_img*sizeof(unsigned char)));

	LOG_INFO(DEBUG,"[Get image pixels] Pixels of window data structure window_t");

	return img_pixels;
}

int get_label (window_t * window, int idx) {
	int * labels = NULL;
	labels = get_labels(window);

	int label  =0;
	label = *(labels + idx);

	free_memory(labels);

	LOG_INFO(DEBUG,"[Get window label] Label %0d of window data structure window_t: %0d", idx, label);

	return label;
}

int * get_labels (window_t * window) {
	ASSERT(window != NULL);
	ASSERT((window->labels) != NULL);

	int no_img = 0;
	no_img = get_no_img(window);

	int * labels = NULL;
	labels = (int *) malloc(no_img*sizeof(int));
	if (labels==NULL) {
		LOG_ERROR("Can't allocate memory for labels array");
	}
	memcpy(labels, window->labels, (no_img*sizeof(int)));

	LOG_INFO(DEBUG,"[Get window labels] Labels of window data structure window_t");

	return labels;
}

void set_prefix (window_t ** window, char * prefix) {
	ASSERT((*window) != NULL);

	int prefix_len = 0;
	prefix_len = sprintf((*window)->prefix, "%s", prefix);
	ASSERT(prefix_len < MAX_WIN_NAME_PREFIX);
	ASSERT(prefix_len > 0);

	LOG_INFO(DEBUG,"[Set window name prefix] Set window name prefix of window data structure window_t: %s",  prefix);
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

void set_menu_id (window_t ** window, int menu_id) {
	ASSERT((*window) != NULL);
	(*window)->menu_id = menu_id;
	LOG_INFO(DEBUG,"[Set menu ID handler] Set menu ID handler of window data structure window_t: %0d",  (*window)->menu_id);
}

void set_win_id (window_t ** window, int win_id) {
	ASSERT((*window) != NULL);
	(*window)->win_id = win_id;
	LOG_INFO(DEBUG,"[Set window ID handler] Set window ID handler of window data structure window_t: %0d",  (*window)->win_id);
}

void set_img_ptr (window_t ** window, int img_ptr) {
	ASSERT((*window) != NULL);
	(*window)->img_ptr = img_ptr;
	LOG_INFO(DEBUG,"[Set image pointer] Set image pointer of window data structure window_t: %0d",  (*window)->img_ptr);
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

void set_pixels (window_t ** window, unsigned char * pixels) {
	ASSERT((*window) != NULL);
	int no_img = 0;
	no_img = get_no_img(*window);

	int width = 0;
	width = get_width(*window);

	int height = 0;
	height = get_height(*window);

	int no_pixels = 0;
	no_pixels = no_img * width * height;

	memcpy((*window)->pixels, pixels, no_pixels*sizeof(unsigned char));

	LOG_INFO(DEBUG,"[Set window pixels] Set pixels of window data structure window_t");
}

void set_labels (window_t ** window, int * labels) {
	ASSERT((*window) != NULL);
	int no_img = 0;
	no_img = get_no_img(*window);

	memcpy((*window)->labels, labels, no_img*sizeof(unsigned char));

	LOG_INFO(DEBUG,"[Set window labels] Set labels of window data structure window_t");
}

void delete_window (window_t * window) {
	if (window != NULL) {
		free_memory(window->prefix);
		LOG_INFO(DEBUG,"[Delete window] Free window name prefix -> COMPLETED");
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

int compute_no_pixels_in_img(window_t * window) {
	ASSERT(window != NULL);

	int width = 0;
	width = get_width(window);

	int height = 0;
	height = get_height(window);

	int no_pixels_in_img = 0;
	no_pixels_in_img = width*height;
	LOG_INFO(DEBUG, "[Compute number pixels in image] Total number of pixels in window_t array: %0d", no_pixels_in_img);

	return no_pixels_in_img;
}

int compute_no_pixels(window_t * window) {
	ASSERT(window != NULL);

	int no_img = 0;
	no_img = get_no_img(window);

	int no_pixels_in_img = 0;
	no_pixels_in_img = compute_no_pixels_in_img(window);

	int no_pixels = 0;
	no_pixels = no_img*no_pixels_in_img;
	LOG_INFO(DEBUG, "[Compute number pixels] Total number of pixels in window_t array: %0d", no_pixels);

	return no_pixels;
}

size_t window_size() {
	return (sizeof(window_t));
}
