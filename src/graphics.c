/**
 * @copyright
 * @file graphics.c
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Functions related to the display of elements
*/

// include standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

// math library
#include <math.h>

#include "log.h"
#include "graphics.h"
#include "window_list.h"

/** @addtogroup GraphicsGroup
 *  @{
 */
/**
 * @brief FIeld of view
 *
 */
static GLfloat zoom = 50.0;

/**
 * @brief Near clip
 *
 */
static GLfloat zNear = 1.0;

/**
 * @brief Far clip
 *
 */
static GLfloat zFar = 1.0;

/** @} */ // End of addtogroup GraphicsGroup

// Shared variables 
int no_windows;

void init_gl(int argc, char** argv) {
	glutInit( &argc, argv );

	no_windows = 0;
	initialize_window_list();
}

void create_window(int no_img, int width, int height, unsigned char * pixels, int * labels, win_type_e window_type, char * win_name_prefix) {

	glutInitWindowSize(width, height);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	char * win_name = NULL;
	win_name = (char *) malloc(WIN_NAME_MAX_LENGTH*sizeof(char));
	if (win_name==NULL) {
		LOG_ERROR("Can't allocate memory for window title");
	}
	int win_name_length = 0;
	win_name_length = sprintf(win_name, "[%s] Element number 0 (Expected %0d)", win_name_prefix, (int)*labels);
	ASSERT(win_name_length <= WIN_NAME_MAX_LENGTH);
	ASSERT(win_name_length > 0);
	int win_id = 0;
	win_id = glutCreateWindow(win_name);
	free_memory(win_name);

	window_t * window = NULL;
	window = (window_t *) malloc((size_t) window_size);
	window = add_window(win_id, no_img, width, height, pixels, labels, window_type, win_name_prefix);
	add_window_struct(window);

	wrapper_dataset_cb();

	no_windows++;
}

void display_dataset_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	// set matrix mode to modelview 
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	LOG_INFO(DEBUG,"[Display cb] Display cb");

	window_t * window = NULL;
	window = search_by_win_id(win_id);

	int width = 0;
	width = get_width(window);

	int height = 0;
	height = get_height(window);

	int curr_img_ptr = 0;
	curr_img_ptr = get_img_ptr(window);

	int label = 0;
	label = get_label(window, curr_img_ptr);

	char * win_name_prefix = NULL;
	win_name_prefix = get_prefix(window);

	char * win_name = NULL;
	win_name = (char *) malloc(WIN_NAME_MAX_LENGTH*sizeof(char));
	if (win_name==NULL) {
		LOG_ERROR("Can't allocate memory for window title");
	}
	int win_name_length = 0;
	win_name_length = sprintf(win_name, "[%s] Element number %0d (Expected %0d)", win_name_prefix, curr_img_ptr, label);
	ASSERT(win_name_length <= WIN_NAME_MAX_LENGTH);
	ASSERT(win_name_length > 0);
	glutSetWindowTitle(win_name);
	free_memory(win_name_prefix);
	free_memory(win_name);

	unsigned char * img_pixels = NULL;
	img_pixels = get_img(window, curr_img_ptr);

	unsigned char * img_rgb = NULL;
	img_rgb = (unsigned char *) malloc(width*height*NO_COLOURS*sizeof(unsigned char));

	for (int width_idx=0; width_idx < width; width_idx++) {
		for (int height_idx=0; height_idx < height; height_idx++) {
			for (int colour_idx = 0; colour_idx < NO_COLOURS; colour_idx++) {
				unsigned char colour = 0;

				switch (colour_idx) {
					case 0:
						colour = *(img_pixels + height_idx*width + width_idx);
						break;
					default :
						colour = 0;
						break;
				}

				*(img_rgb + NO_COLOURS*(height_idx*width + width_idx) + colour_idx) = colour;
			}
		}
	}

	double win_width = 0;
	win_width = glutGet(GLUT_WINDOW_WIDTH);

	double win_height = 0;
	win_height = glutGet(GLUT_WINDOW_HEIGHT);

	unsigned char * img_reshaped = NULL;
	img_reshaped = reshape_img(width, height, win_width, win_height, img_rgb);

	unsigned char * img_flipped = NULL;
	img_flipped = flip_img((int)win_width, (int)win_height, img_reshaped);

	//glDrawPixels((int)win_width, (int)win_height, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, img_flipped);
	glDrawPixels((int)win_width, (int)win_height, GL_RGB, GL_UNSIGNED_BYTE, img_flipped);

	free_memory(img_pixels);
	free_memory(img_rgb);
	free_memory(img_reshaped);
	free_memory(img_flipped);

	// swap buffers to display the frame
	glutSwapBuffers();
}

void reshape_dataset_cb(int width, int height) {
	// set viewport to new width and height 
	glViewport( 0, 0, width, height );

	// set viewing window using perspective projection
	glMatrixMode( GL_PROJECTION ); 
	// init projection matrix
	glLoadIdentity();

	// perspective parameters: field of view, aspect, near clip, far clip 
	gluPerspective( zoom, (GLdouble)width/(GLdouble)height, zNear, zFar );

//	glClear(GL_COLOR_BUFFER_BIT);
}

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void keyboard_dataset_cb(unsigned char key, int x, int y) {
	switch (key) {
		case 'n':
			LOG_INFO(ZERO,"[Keyboard callbak] Increase image pointer because of pressing key %c", key);
			change_img_ptr(+1);
			break;
		case 'p':
			LOG_INFO(ZERO,"[Keyboard callbak] Decrease image pointer because of pressing key %c", key);
			change_img_ptr(-1);
			break;
		case 'q':
			LOG_INFO(ZERO,"[Keyboard callbak] Exit program because of pressing key %c", key);
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
	}

	// force glut to call the display function
	glutPostRedisplay();

}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void specialkey_dataset_cb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			LOG_INFO(ZERO,"[Keyboard callbak] Increase image pointer because of pressing key Arrow Up");
			change_img_ptr(+1);
			break;
		case GLUT_KEY_DOWN:
			LOG_INFO(ZERO,"[Keyboard callbak] Decrease image pointer because of pressing key Arrow Down");
			change_img_ptr(-1);
			break;
		default:
			break;
	}

	// force glut to call the display function
	glutPostRedisplay();
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void mouse_dataset_cb(int button, int state, int x, int y) {
	switch (button) {
		default:
			break;
	}
}
#pragma GCC diagnostic pop

void idle_dataset_cb() {

	// force glut to call the display function
	glutPostRedisplay();

}

void wrapper_dataset_cb() {
	glutDisplayFunc( display_dataset_cb );
	glutKeyboardFunc( keyboard_dataset_cb );
	glutReshapeFunc( reshape_dataset_cb );
	glutIdleFunc( idle_dataset_cb );
	glutSpecialFunc( specialkey_dataset_cb );
	glutMouseFunc( mouse_dataset_cb );
}

void show_window() {
	glutMainLoop();
}
