#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Graphics header file
*/

/** @defgroup FileGroup File Doxygen Group
 *  Functions and defines concerning file manipulation
 *  @{
 */
/**
 * @brief Maximum number of windows allowed
 *
 */
#define MAX_NUM_WINDOW 1

/**
 * @brief Window width
 *
 */
#define WIN_WIDTH 680

/**
 * @brief Window height
 *
 */
#define WIN_HEIGHT 680

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
 * @brief void init_gl (int argc, char ** argv)
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 *
 * Initialize GLUT library and shared variable values
 */
void init_gl (int argc, char** argv);

/**
 * @brief void add_window (char * title)
 *
 * \param element_no: element number displayed in the window.
 * \param label: label of the element displayed on the window.
 *
 * Add window to display elements
 */
void add_window (int element_no, int label);

/**
 * @brief void wrapper_cb ()
 *
 * Callback wrapper
 */
void cb_wrapper ();

/**
 * @brief void display_cb (void)
 *
 * This function is called by the GLUT to display the graphics
 */
void display_cb ();

/**
 * @brief void reshape_cb (int width, int height)
 *
 * \param width: width of the reshaped window
 * \param height: height of the reshaped window
 *
 * This function is called whenever the user (or OS) reshapes the OpenGL window. The GLUT sends the new window dimensions (x,y)
 */
void reshape_cb (int width, int height);

/**
 * @brief void idle_cb (void)
 *
 * This function call idle of the program
 */
void idle_cb ();

/**
 * @brief void mouse_cb(int button, int state, int x, int y);
 *
 * \param button: mouse button pressed
 * \param state: state of mouse button pressed
 * \param x: x coordinate of the mouse button pressed
 * \param y: y coordinate of the mouse button pressed
 *
 * This function sets mouse button function
 */
void mouse_cb (int button, int state, int x, int y);

/**
 * @brief void specialkey_cb(int key, int x, int y);
 *
 * \param key: key pressed
 * \param x: x coordinate of the key pressed
 * \param y: y coordinate of the key pressed
 *
 * This function sets mouse button function
 */
void specialkey_cb (int key, int x, int y);

/**
 * @brief void keyboard_cb(int key, int x, int y);
 *
 * \param key: key pressed
 * \param x: x coordinate of the key pressed
 * \param y: y coordinate of the key pressed
 *
 * This function assigns a function to some keys of the keyboard
 */
void keyboard_cb (int key, int x, int y);

#endif // GRAPHICS_H
