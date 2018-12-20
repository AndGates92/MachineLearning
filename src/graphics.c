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
static GLfloat zFar = 1.0e2;

/** @} */ // End of addtogroup GraphicsGroup

// Shared variables 
int no_windows;

void init_gl(int argc, char** argv) {
	glutInit( &argc, argv );

	no_windows = 0;
	initialize_window_list();
	wrapper_dataset_cb();
}

void create_window(int no_img, int width, int height, double * pixels, int * labels, win_type_e window_type) {

	glutInitWindowSize(width, height);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	char * win_name = NULL;
	win_name = (char *) malloc(WIN_NAME_MAX_LENGTH*sizeof(char));
	if (win_name==NULL) {
		LOG_ERROR("Can't allocate memory for window title");
	}
	int win_name_length = 0;
	win_name_length = sprintf(win_name, "Element number 0 (Expected %0d)", (int)*labels);
	ASSERT(win_name_length <= WIN_NAME_MAX_LENGTH);
	ASSERT(win_name_length > 0);
	int win_id = 0;
	win_id = glutCreateWindow(win_name);
	free_memory(win_name);

	window_t * window = NULL;
	window = (window_t *) malloc((size_t) window_size);
	window = add_window(win_id, no_img, width, height, pixels, labels, window_type);
	add_window_struct(window);

	wrapper_dataset_cb();

	no_windows++;
}


void display_dataset_cb() {
	glClear( GL_COLOR_BUFFER_BIT );

	/* 
	* set matrix mode to modelview 
	*/
	glMatrixMode( GL_MODELVIEW );

	int win_id = 0;
	win_id = glutGetWindow();

	window_t * window = NULL;
	window = search_by_win_id(win_id);

	int width = 0;
	width = get_width(window);

	int height = 0;
	height = get_height(window);

	free(window);
 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {

		}
	}


	/* 
	* swap buffers to display the frame 
	*/
 	glutSwapBuffers();
}

void reshape_dataset_cb(int width, int height) {
	/* 
	* set viewport to new width and height 
	*/
	glViewport( 0, 0, width, height );

	/* 
	 * set viewing window using perspective projection
	 */
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); /* init projection matrix */

	/* 
	* perspective parameters: field of view, aspect, near clip, far clip 
	*/
	gluPerspective( zoom, (GLdouble)width/(GLdouble)height, zNear, zFar );
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void keyboard_dataset_cb(unsigned char key, int x, int y) {
	switch (key) {
		default:
			break;
	}

	/* force glut to call the display functin */
	glutPostRedisplay();

}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void specialkeys_dataset_cb(int key, int x, int y) {
	switch (key) {
		default:
			break;
	}

	/* force glut to call the display function */
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

	/* force glut to call the display function */
	glutPostRedisplay();

}

void wrapper_dataset_cb() {
	glutDisplayFunc( display_dataset_cb );
	glutKeyboardFunc( keyboard_dataset_cb );
	glutReshapeFunc( reshape_dataset_cb );
	glutIdleFunc( idle_dataset_cb );
	glutSpecialFunc( specialkeys_dataset_cb );
	glutMouseFunc( mouse_dataset_cb );
}

void show_window() {
	glutMainLoop();
}
