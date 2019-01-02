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

#include "menu.h"

int menu_id;

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

void add_menu() {

	menu_id = glutCreateMenu(menu_items);
	glutAddMenuEntry("Quit", QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
