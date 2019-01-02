#ifndef OBJ_GRAPHICS_H
#define OBJ_GRAPHICS_H
/**
 * @copyright
 * @file obj_graphics.h
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Object graphics header file
 */

#include "window.h"

/** @defgroup ObjGraphicsGroup Object Graphics Doxygen Group
 *  Functions and defines concerning graphics of objects
 *  @{
 */
/**
 * @brief Maximum length of the window title
 *
 */
#define WIN_NAME_MAX_LENGTH (MAX_WIN_NAME_PREFIX + 50)

/**
 * @brief Function: void wrapper_dataset_cb()
 *
 * Callback datset wrapper
 */
void wrapper_dataset_cb();

/**
 * @brief Function: void display_dataset_cb()
 *
 * This function is called by the GLUT to display the graphics
 */
void display_dataset_cb();

/**
 * @brief Function: void reshape_dataset_cb(int width, int height)
 *
 * \param width: width of the reshaped window
 * \param height: height of the reshaped window
 *
 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
 */
void reshape_dataset_cb(int width, int height);

/**
 * @brief Function: void idle_dataset_cb()
 *
 * This function call idle of the program
 */
void idle_dataset_cb();

/**
 * @brief Function: void mouse_dataset_cb(int button, int state, int x, int y);
 *
 * \param button: mouse button pressed
 * \param state: state of mouse button pressed
 * \param x: x coordinate of the mouse button pressed
 * \param y: y coordinate of the mouse button pressed
 *
 * This function sets mouse button function
 */
void mouse_dataset_cb(int button, int state, int x, int y);

/**
 * @brief Function: void specialkey_dataset_cb(int key, int x, int y);
 *
 * \param key: key pressed
 * \param x: x coordinate of the key pressed
 * \param y: y coordinate of the key pressed
 *
 * This function sets mouse button function
 */
void specialkey_dataset_cb(int key, int x, int y);

/**
 * @brief Function: void keyboard_dataset_cb(unsigned char key, int x, int y);
 *
 * \param key: key pressed
 * \param x: x coordinate of the key pressed
 * \param y: y coordinate of the key pressed
 *
 * This function assigns a function to some keys of the keyboard
 */
void keyboard_dataset_cb(unsigned char key, int x, int y);

/** @} */ // End of ObjGraphicsGroup
#endif // OBJ_GRAPHICS_H
