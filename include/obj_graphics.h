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
 * @brief Function: unsigned char * reshape_img(int width_orig, int height_orig, double win_width, double win_height, unsigned char * img_orig)
 *
 * \param img_orig: image pixels as stored in window array
 * \param win_width: width of the window.
 * \param win_height: height of the window.
 * \param width: width of the image stored in window array.
 * \param height: height of the image stored in window array.
 * \return reshaped image
 *
 * Reshape image array
 */
unsigned char * reshape_img(int width_orig, int height_orig, double win_width, double win_height, unsigned char * img_orig);

/**
 * @brief Function: float * normalize_img(int win_width, int win_height, unsigned char * img_in)
 *
 * \param img_in: image pixels as stored in window array
 * \param win_width: width of the window.
 * \param win_height: height of the window.
 * \return normalized image
 *
 * Normalize image
 */
float * normalize_img(int win_width, int win_height, unsigned char * img_in);

/**
 * @brief Function: unsigned char * flip_img(int win_width, int win_height, unsigned char * img_in)
 *
 * \param img_in: image pixels as stored in window array
 * \param win_width: width of the window.
 * \param win_height: height of the window.
 * \return flipped image
 *
 * Flip image as OpenGL puts coordinates in the lower left corner of the image
 */
unsigned char * flip_img(int win_width, int win_height, unsigned char * img_in);

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
void change_img_ptr(int step);

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
 * @brief Function: void destroy_window()
 *
 * This function destroys a window
 */
void destroy_window();

/** @} */ // End of ObjGraphicsGroup
#endif // OBJ_GRAPHICS_H
