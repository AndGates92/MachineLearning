#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 31st of December 2018
 * @brief Top level graphics header file
 */

#include "window.h"

/** @defgroup GraphicsGroup Object Graphics Doxygen Group
 *  Functions and defines concerning graphics of objects
 *  @{
 */
/**
 * @brief Maximum length of the window title
 *
 */
#define WIN_NAME_MAX_LENGTH (MAX_WIN_NAME_PREFIX + 50)

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
 * @brief Number of base colours
 *
 */
#define NO_COLOURS 3

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
 * @brief Function: void create_window(int no_img, int width, int height, unsigned char * pixels, int * labels, win_type_e window_type, char * win_name_prefix)
 *
 * \param no_img: number of images in pixels array
 * \param win_name_prefix: window name prefix
 * \param width: width of the window.
 * \param height: height of the window.
 * \param pixels: pixels to be displayed (it can involve multiple sets of pixels).
 * \param labels: labels (it contains all labels for the pixels displayed).
 * \param window_type: window label (it specify the content of the window).
 *
 * Add window to display elements
 */
void create_window(int no_img, int width, int height, unsigned char * pixels, int * labels, win_type_e window_type, char * win_name_prefix);

/**
 * @brief Function: void show_window()
 *
 * This function starts displaying windows
 */
void show_window();

/**
 * @brief Function: void change_no_windows(int step)
 *
 * \param step: value to add to the number of windows
 *
 * Increment the number of windows by the values given as input step
 */
void change_no_windows(int step);

/** @} */ // End of GraphicsGroup
#endif // GRAPHICS_H
