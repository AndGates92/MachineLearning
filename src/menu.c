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
#include <time.h>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"
#include "menu.h"

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

