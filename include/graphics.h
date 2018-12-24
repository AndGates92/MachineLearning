#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Graphics header file
*/

#include "window.h"

/** @defgroup GraphicsGroup Graphics Doxygen Group
 *  Functions and defines concerning graphics
 *  @{
 */
/**
 * @brief Maximum length of the window title
 *
 */
#define WIN_NAME_MAX_LENGTH 50

/**
 * @brief Window position on the x coordinate
 *
 */
#define WIN_POS_X 50

/**
 * @brief Window position on the y coordinate
 *
 */
#define WIN_POS_Y 50

/**
 * @brief Function: void init_gl(int argc, char ** argv)
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 *
 * Initialize GLUT library and shared variable values
 */
void init_gl(int argc, char** argv);

/**
 * @brief Function: void create_window(int no_img, int width, int height, float * pixels, int * labels, win_type_e window_type)
 *
 * \param no_img: number of images in pixels array
 * \param width: width of the window.
 * \param height: height of the window.
 * \param pixels: pixels to be displayed (it can involve multiple sets of pixels).
 * \param labels: labels (it contains all labels for the pixels displayed).
 * \param window_type: window label (it specify the content of the window).
 *
 * Add window to display elements
 */
void create_window(int no_img, int width, int height, float * pixels, int * labels, win_type_e window_type);

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
 * @brief Function: void change_img_ptr(int step)
 *
 * \param step: value to add to the image pointer 
 *
 * Get current window ID and increment the image pointer by the value of step input
 */
void change_img_ptr();

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

/**
 * @brief Function: void show_window()
 *
 * This function starts displaying windows
 */
void show_window();

/** @} */ // End of GraphicsGroup
#endif // GRAPHICS_H
