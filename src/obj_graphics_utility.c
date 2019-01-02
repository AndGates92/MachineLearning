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

#include "log.h"
#include "graphics.h"
#include "window.h"
#include "window_list.h"
#include "obj_graphics_utility.h"

unsigned char * reshape_img(int width_orig, int height_orig, double win_width, double win_height, unsigned char * img_orig) {

	double win_img_width_ratio = 0.0;
	win_img_width_ratio = win_width/(double)width_orig;

	double win_img_height_ratio = 0.0;
	win_img_height_ratio = win_height/(double)height_orig;

	unsigned char * img = NULL;
	img = (unsigned char *) malloc(win_width*win_height*NO_COLOURS*sizeof(unsigned char));

	bool width_reduced = false;
	int win_img_width_ratio_int = 0;
	if (win_img_width_ratio < 1.0) {
		win_img_width_ratio_int = (int)(1.0/win_img_width_ratio);
		width_reduced = true;
	} else {
		win_img_width_ratio_int = (int)(win_img_width_ratio);
		width_reduced = false;
	}

	bool height_reduced = false;
	int win_img_height_ratio_int = 0;
	if (win_img_height_ratio < 1.0) {
		win_img_height_ratio_int = (int)(1.0/win_img_height_ratio);
		height_reduced = true;
	} else {
		win_img_height_ratio_int = (int)(win_img_height_ratio);
		height_reduced = false;
	}

	int img_width_idx = 0;

	for (int width_idx = 0; width_idx < win_width; width_idx++) {
		if (width_reduced == false) {
			if ((width_idx % win_img_width_ratio_int) == (win_img_width_ratio_int - 1)) {
				img_width_idx++;
			}
		} else {
			
		}

		int img_height_idx = 0;

		for (int height_idx = 0; height_idx < win_height; height_idx++) {
			for (int colour_idx = 0; colour_idx < NO_COLOURS; colour_idx++) {
				*(img + NO_COLOURS*(height_idx*(int)win_width + width_idx) + colour_idx) = *(img_orig + NO_COLOURS*(img_height_idx*width_orig + img_width_idx) + colour_idx);
			}

			if (height_reduced == false) {
				if ((height_idx % win_img_height_ratio_int) == (win_img_height_ratio_int - 1)) {
					img_height_idx++;
				}
			} else {
			
			}

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

	int menu_id = 0;
	menu_id = glutGetMenu();

	int curr_menu_id = 0;
	curr_menu_id = get_menu_id(window);
	ASSERT((menu_id == curr_menu_id) || (menu_id == 0));

	glutDestroyMenu(menu_id);
}

void remove_window() {
	destroy_menu();
	destroy_window();
}
