#ifndef WINDOW_H
#define WINDOW_H
/**
 * @copyright
 * @file window.h
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Graphics header file
*/

/**
 * @brief window data strcture window_t
 *
 */
typedef struct window {
	int curr_element_ptr; /**< X dimension */
	int id; /**< Window ID */
	int x_dim; /**< X dimension */
	int y_dim; /**< Y dimension */
	GLfloat * pixels; /**< Pixel color */
}

/**
 * @brief Function: window_t * add_window (int id, int width, int height, GLfloat * pixels)
 *
 * \param id: window id handler
 * \param width: width of the window
 * \param height: height of the window
 * \param pixels: pixels of the window
 * \return a pointer to an window strcture window_t
 *
 * Create and allocate memory for a new window data strcture window_t
 */
window_t * add_window (int id, int width, int height, GLfloat * pixels);

/**
 * @brief Function: void set_id (int id)
 *
 * \param id: window id handler
 *
 * Set window handler ID
 */
void set_id (int id);

/**
 * @brief Function: void set_width (int width)
 *
 * \param width: width of the window
 *
 * Set window width
 */
void set_width (int width);

/**
 * @brief Function: void set_height (int height)
 *
 * \param height: height of the window
 *
 * Set window height
 */
void set_height (int height);

/**
 * @brief Function: void set_pixels (GLfloat pixels)
 *
 * \param pixels: pixels of the window
 *
 * Set window pixels
 */
void set_pixels (GLfloat pixels);

/**
 * @brief Function: int get_id (window_t window)
 *
 * \param window: input window data structure window_t
 * \return the window handler ID
 *
 * Set window handler ID
 */
int get_id (window_t window);

/**
 * @brief Function: int get_width (window_t window)
 *
 * \param window: input window data structure window_t
 * \return the window width
 *
 * Set window width
 */
int get_width (window_t window);

/**
 * @brief Function: int get_height (window_t window)
 *
 * \param window: input window data structure window_t
 * \return the window height
 *
 * Set window height
 */
int get_height (window_t window);

/**
 * @brief Function: GLfloat get_pixels (window_t window)
 *
 * \param window: input window data structure window_t
 * \return the window pixels
 *
 * Set window pixels
 */
GLfloat get_pixels (window_t window);

/**
 * @brief Function: void delete_window (window_t * window)
 *
 * \param window: window data strcture window_t to delete
 * 
 * Delete an window data strcture window_t. Frees up memory as well.
 */
void delete_window (window_t * window);

#endif // WINDOW_H
