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

#include "graphics.h"

// Shared variables 
int current_window;
int num_windows;
int * win_id_array;

void init_gl(int argc, char** argv) {
	glutInit( &argc, argv );

	current_window = 0;
	num_window = 0;
	win_id_array = (int *) malloc(MAX_NUM_WINDOW*sizeof(int));

	cb_wrapper ();
};

void add_window (char * title) {

	glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
	glutInitWindowPosition( WIN_POS_X, WIN_POS_Y );

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );

//	char * win_name = NULL;
//	win_name = (char *) malloc(WIN_NAME_MAX_LENGTH*sizeof(char));
//	win_name_length = sprintf(win_name, "Element number %0d (Expected %0d)", element_no, label);
	int win_id = 0;
	win_id = glutCreateWindow( title );

	*(win_id_array + num_window) = win_id;
	num_window++;
	ASSERT(num_window <= MAX_NUM_WINDOW);
};


void display_cb () {
	glClear( GL_COLOR_BUFFER_BIT );

	/* 
	* swap buffers to display the frame 
	*/
 	glutSwapBuffers();
}

void reshape_cb (int width, int height) {
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
	gluPerspective( 50.0*zoom, (GLdouble)width/(GLdouble)height, zNear, zFar );
}

void keyboard_cb (unsigned char key, int x, int y) {
	switch (key) {
		default:
			break;
	}

	/* force glut to call the display functin */
	glutPostRedisplay();

}

void specialkeys_cb (int key, int x, int y) {
	switch (key) {
		default:
			break;
	}

	/* force glut to call the display functin */
	glutPostRedisplay();
}

void mouse_cb (int button, int state, int x, int y) {
    switch( button )
    {
        case GLUT_LEFT_BUTTON:
            if ( state != GLUT_DOWN )
                return;
            mouse_test( x, y );
            break;
    }
}

void idle_cb () {

	/* force glut to call the display function */
	glutPostRedisplay();

}

void wrapper_cb () {
	glutDisplayFunc( display_cb );
	glutKeyboardFunc( keyboard_cb );
	glutReshapeFunc( reshape_cb );
	glutIdleFunc( idle_cb );
	glutSpecialFunc( specialkeys_cb );
	glutMouseFunc( mouse_cb );

	glutMainLoop();
}
