/**
 * @copyright
 * @file graphics.c
 * @author Andrea Gianarda
 * @date 31st of December 2018
 * @brief Functions related to OpenGL graphics
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

#include "log.h"
#include "menu.h"
#include "graphics.h"
#include "obj_graphics.h"
#include "window_list.h"

// Shared variables 
int no_windows;

void init_gl(int argc, char** argv) {
	glutInit( &argc, argv );

	no_windows = 0;
	initialize_window_list();
}

void create_window(int no_img, int width, int height, unsigned char * pixels, int * labels, win_type_e window_type, char * win_name_prefix) {

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
	win_id = init_window(width, height, WIN_POS_X, WIN_POS_Y, win_name);

	free_memory(win_name);

	window_t * window = NULL;
	window = (window_t *) malloc((size_t) window_size);
	window = add_window(win_id, no_img, width, height, pixels, labels, window_type, win_name_prefix);
	add_window_struct(window);

	wrapper_dataset_cb();

	no_windows++;
}

int init_window (int width, int height, int pos_x, int pos_y, char * win_name) {

	LOG_INFO(DEBUG,"[Init window] Create window at %0d, %0d. Dimensions: width %0d height %0d", pos_x, pos_y, width, height);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(pos_x, pos_y);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	int win_id = 0;
	win_id = glutCreateWindow(win_name);

	return win_id;

}

void create_menu () {

	add_menu();

}

void show_window() {
	glutMainLoop();
}

void change_no_windows(int step) {
	no_windows += step;
}

int get_no_windows() {
	return no_windows;
}
