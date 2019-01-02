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
#include "window_list.h"
#include "window.h"

void menu_items(int item) {
	switch (item) {
		case QUIT:
			exit(EXIT_SUCCESS);
			break;
		default:
			glutPostRedisplay();
			break;
	}

	glutPostRedisplay();
}

int add_menu() {

	int menu_id;
	menu_id = glutCreateMenu(menu_items);
	glutAddMenuEntry("Quit", QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu_id;
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
