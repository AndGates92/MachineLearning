/**
 * @copyright
 * @file obj_graphics_utility.c
 * @author Andrea Gianarda
 * @date 02nd of January 2019
 * @brief Utility functions related to the display of elements
*/

// include standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

// math library
#include <math.h>

#include "log.h"
#include "graphics.h"
#include "window.h"
#include "window_list.h"
#include "obj_graphics_utility.h"

unsigned char * reshape_img(int width_orig, int height_orig, double win_width, double win_height, unsigned char * img_orig) {

	double win_img_width_ratio = 0.0;
	bool width_reduced = false;
	if (win_width < width_orig) {
		win_img_width_ratio = ((double)width_orig/win_width);
		width_reduced = true;
	} else {
		win_img_width_ratio = (win_width/(double)width_orig);
		width_reduced = false;
	}

	int win_img_width_ratio_int = 0;
	win_img_width_ratio_int = (int)(floor(win_img_width_ratio));

	double win_img_width_ratio_dec = 0.0;
	if (win_img_width_ratio == (double)(win_img_width_ratio_int)) {
		win_img_width_ratio_dec = 1.0;
	} else {
		win_img_width_ratio_dec = ceil(1.0/(win_img_width_ratio - (double)(win_img_width_ratio_int)));
	}

	double win_img_height_ratio = 0.0;
	bool height_reduced = false;
	if (win_height < height_orig) {
		win_img_height_ratio = ((double)height_orig/win_height);
		height_reduced = true;
	} else {
		win_img_height_ratio = (win_height/(double)height_orig);
		height_reduced = false;
	}

	int win_img_height_ratio_int = 0;
	win_img_height_ratio_int = (int)(win_img_height_ratio);

	double win_img_height_ratio_dec = 0.0;
	if (win_img_height_ratio == (double)(win_img_height_ratio_int)) {
		win_img_height_ratio_dec = 1.0;
	} else {
		win_img_height_ratio_dec = ceil(1.0/(win_img_height_ratio - (double)(win_img_height_ratio_int)));
	}

	unsigned char * img = NULL;
	img = (unsigned char *) malloc(win_width*win_height*NO_COLOURS*sizeof(unsigned char));

	int img_width_idx = 0;
	int width_corr = 0;
	bool add_extra_col = false;

	LOG_INFO(DEBUG,"[Reshape image] original image width %0d height %0d \n", width_orig,height_orig);
	LOG_INFO(DEBUG,"[Reshape image] reshape image width %0lf height %0lf \n", win_width,win_height);
	LOG_INFO(DEBUG,"[Reshape image] ratio width %0lf height %0lf \n", win_img_width_ratio,win_img_height_ratio);
	LOG_INFO(DEBUG,"[Reshape image] Integer part of ratio width %0d height %0d \n", win_img_width_ratio_int,win_img_height_ratio_int);
	LOG_INFO(DEBUG,"[Reshape image] Inverse of decimal part of ratio width %0lf height %0lf \n", win_img_width_ratio_dec,win_img_height_ratio_dec);

	for (int width_idx = 0; width_idx < (int)win_width; width_idx++) {

		ASSERT(img_width_idx < width_orig);

		int img_height_idx = 0;
		int height_corr = 0;
		bool add_extra_line = false;

		for (int height_idx = 0; height_idx < (int)win_height; height_idx++) {

			ASSERT(img_height_idx < height_orig);
			LOG_INFO(DEBUG, "[Reshape image] orig (%0d, %0d) ---> reshaped (%0d, %0d): %0d \n", width_idx, height_idx, img_width_idx,img_height_idx,*(img_orig + NO_COLOURS*(img_height_idx*width_orig + img_width_idx)));

			for (int colour_idx = 0; colour_idx < NO_COLOURS; colour_idx++) {
				*(img + NO_COLOURS*(height_idx*(int)win_width + width_idx) + colour_idx) = *(img_orig + NO_COLOURS*(img_height_idx*width_orig + img_width_idx) + colour_idx);
			}

			if (height_reduced == false) {
				int height_idx_corr = 0;
				height_idx_corr = (height_idx - height_corr);
				if ((height_idx_corr % win_img_height_ratio_int) == (win_img_height_ratio_int - 1)) {
					// Increase height only if no need to add extra line, extra line was not added the previous time around or ratio has no decimal part
					if (((height_idx_corr % ((int) win_img_height_ratio_dec)) < (((int) win_img_height_ratio_dec) - 1)) || (add_extra_line == true) || (win_img_height_ratio == (double)(win_img_height_ratio_int))) {
						if (img_height_idx < (height_orig - 1)) {
							img_height_idx++;
						}
						add_extra_line = false;
					} else {
						height_corr++;
						add_extra_line = true;
					}
				}
			} else {
			
			}
		}

		if (width_reduced == false) {
			int width_idx_corr = 0;
			width_idx_corr = (width_idx - width_corr);
			if ((width_idx_corr % win_img_width_ratio_int) == (win_img_width_ratio_int - 1)) {
				// Increase width only if no need to add extra column, extra line was not added the previous time around or ratio has no decimal part
				if (((width_idx_corr % ((int) win_img_width_ratio_dec)) < (((int) win_img_width_ratio_dec) - 1)) || (add_extra_col == true) || (win_img_width_ratio == (double)(win_img_width_ratio_int))) {
					if (img_width_idx < (width_orig - 1)) {
						img_width_idx++;
					}
					add_extra_col = false;
				} else {
					width_corr++;
					add_extra_col = true;
				}
			}
		} else {
			
		}
	}

	return img;
}

unsigned char * flip_img(int win_width, int win_height, unsigned char * img_in) {

	unsigned char * img = NULL;
	img = (unsigned char *) malloc(win_width*win_height*NO_COLOURS*sizeof(unsigned char));

	for (int width_idx = 0; width_idx < win_width; width_idx++) {
		for (int height_idx = 0; height_idx < win_height; height_idx++) {
			for (int colour_idx = 0; colour_idx < NO_COLOURS; colour_idx++) {
				*(img + NO_COLOURS*((win_height - 1 - height_idx)*win_width + width_idx) + colour_idx) = *(img_in + NO_COLOURS*(height_idx*win_width + width_idx) + colour_idx);
			}
		}
	}

	return img;
}

float * normalize_img(int win_width, int win_height, unsigned char * img_in) {

	float * img = NULL;
	img = (float *) malloc(win_width*win_height*NO_COLOURS*sizeof(float));

	int max_pixel_val = 0;
	// Choose first element of img_pixels to extract datatype width
	max_pixel_val = (2^(BIT_IN_BYTE*sizeof(*img_in)))-1;

	for (int width_idx = 0; width_idx < win_width; width_idx++) {
		for (int height_idx = 0; height_idx < win_height; height_idx++) {
			int idx = 0;
			idx = NO_COLOURS*((win_height - 1 - height_idx)*win_width + width_idx);
			for (int colour_idx = 0; colour_idx < NO_COLOURS; colour_idx++) {
				*(img + idx + colour_idx) = ((float)(*(img_in + idx + colour_idx)))/((float)max_pixel_val);
			}
		}
	}

	return img;
}

void change_img_ptr(int step) {
	int win_id = 0;
	win_id = glutGetWindow();

	window_t * window = NULL;
	window = search_by_win_id(win_id);

	int curr_img_ptr = 0;
	curr_img_ptr = get_img_ptr(window);

	int no_img = 0;
	no_img = get_no_img(window);

	if ((step < 0) && (curr_img_ptr < abs(step))) {
		curr_img_ptr += (no_img + step);
	} else if ((step > 0) && (curr_img_ptr >= (no_img - abs(step)))) {
		curr_img_ptr -= (no_img - step);
	} else {
		curr_img_ptr += step;
	}

	set_img_ptr(&window, curr_img_ptr);
}

void destroy_window() {
	int win_id = 0;
	win_id = glutGetWindow();

	remove_window_struct(win_id);

	glutDestroyWindow(win_id);
	change_no_windows(-1);

	window_list_t * window_head_list = NULL;
	window_head_list = get_window_list_head();

	int no_windows = 0;
	no_windows = get_no_windows();

	if (window_head_list == NULL) {
		ASSERT(no_windows == 0);
		// Exit only if no windows are left
		exit(EXIT_SUCCESS);
	} else {
		ASSERT(no_windows > 0);
	}
}

void destroy_menu() {
	int win_id = 0;
	win_id = glutGetWindow();

	window_t * window = NULL;
	window = search_by_win_id(win_id);

	int curr_menu_id = 0;
	curr_menu_id = get_menu_id(window);

	glutDestroyMenu(curr_menu_id);
}

void remove_window() {
	destroy_menu();
	destroy_window();
}
