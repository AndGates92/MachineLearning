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
#include <time.h>

// include graphical libraries (OPENGL)
#include <GL/glut.h>
#include <GL/gl.h>

#include "log.h"
#include "obj_graphics_utility.h"
#include "menu.h"

void menu_entries(int entry) {
	switch (entry) {
		case PREV_OBJ:
			LOG_INFO(ZERO,"[Keyboard callbak] Decrement image pointer because of pressing entry %s in menu", menu_entry_to_str(entry));
			change_img_ptr(-1);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case NEXT_OBJ:
			LOG_INFO(ZERO,"[Keyboard callbak] Increment image pointer because of pressing entry %s in menu", menu_entry_to_str(entry));
			change_img_ptr(+1);
			// force glut to call the display function
			glutPostRedisplay();
			break;
		case QUIT:
			exit(EXIT_SUCCESS);
			break;
		default:
			glutPostRedisplay();
			break;
	}
}

int add_menu() {

	int menu_id;
	menu_id = glutCreateMenu(menu_entries);
	glutAddMenuEntry("Previous Element", PREV_OBJ);
	glutAddMenuEntry("Next Element", NEXT_OBJ);
	glutAddMenuEntry("Quit", QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu_id;
}

char * menu_entry_to_str(menu_entry_e menu_entry) {
	char * menu_entry_str = NULL;

	menu_entry_str = (char *) malloc(MAX_MENU_ENTRY_LENGTH*sizeof(char));
	if (menu_entry_str==NULL) {
		LOG_ERROR("Can't allocate memory for string for data type");
	}

	switch (menu_entry) {
		case PREV_OBJ:
			strcpy(menu_entry_str, "PREV_OBJ");
			break;
		case NEXT_OBJ:
			strcpy(menu_entry_str, "NEXT_OBJ");
			break;
		case QUIT:
			strcpy(menu_entry_str, "QUIT");
			break;
		default:
			LOG_ERROR("Unknown menu entry. Can't generate string with menu entry name");
			break;
	}

	return menu_entry_str;
}
