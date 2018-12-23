#ifndef WINDOW_H
#define WINDOW_H
/**
 * @copyright
 * @file window.h
 * @author Andrea Gianarda
 * @date 18th of December 2018
 * @brief Graphics header file
*/

/** @defgroup WindowGroup Window Doxygen Group
 *  Functions and defines concerning window data strcture window_t
 *  @{
 */
/**
 * @brief Length of window type string
 *
 */
#define MAX_WINDOW_TYPE_LENGTH 10

/**
 * @brief Window labels
 *
 */
typedef enum win_type_list {
	DATASET
} win_type_e;

/**
 * @brief window data strcture type window_t
 *
 */
typedef struct window window_t;

/**
 * @brief Function: window_t * add_window(int id, int no_img, int width, int height, double * pixels, int * labels, win_type_e window_type)
 *
 * \param id: window id handler
 * \param no_img: number of images stored in pixels array
 * \param width: width of the window
 * \param height: height of the window
 * \param pixels: pixels of the window
 * \param labels: labels matching the pixels (it is ignored if set to NULL)
 * \param window_type: type of content displayed in the window)
 * \return a pointer to an window strcture window_t
 *
 * Create and allocate memory for a new window data strcture window_t
 */
window_t * add_window(int id, int no_img, int width, int height, double * pixels, int * labels, win_type_e window_type);

/**
 * @brief Function: void set_no_img(window_t ** window, win_type_e window_type)
 *
 * \param window: input window data structure window_t
 * \param window_type: type of content displayed in the window)
 *
 * Set type of content displayed on the window
 */
void set_window_type(window_t ** window, win_type_e window_type);

/**
 * @brief Function: void set_no_img(window_t ** window, int no_img)
 *
 * \param window: input window data structure window_t
 * \param no_img: number of images in pixels array
 *
 * Set number of images in pixels array
 */
void set_no_img(window_t ** window, int no_img);

/**
 * @brief Function: void set_id(window_t ** window, int id)
 *
 * \param window: input window data structure window_t
 * \param id: window id handler
 *
 * Set window handler ID
 */
void set_id(window_t ** window, int id);

/**
 * @brief Function: void set_img_ptr(window_t ** window, int img_ptr)
 *
 * \param window: input window data structure window_t
 * \param img_ptr: image pointer
 *
 * Set image pointer
 */
void set_img_ptr(window_t ** window, int img_ptr);

/**
 * @brief Function: void set_width(window_t ** window, int width)
 *
 * \param window: input window data structure window_t
 * \param width: width of the window
 *
 * Set window width
 */
void set_width(window_t ** window, int width);

/**
 * @brief Function: void set_height(window_t ** window, int height)
 *
 * \param window: input window data structure window_t
 * \param height: height of the window
 *
 * Set window height
 */
void set_height(window_t ** window, int height);

/**
 * @brief Function: void set_pixels(window_t ** window, double * pixels)
 *
 * \param window: input window data structure window_t
 * \param pixels: pixels of the window
 *
 * Set window pixels
 */
void set_pixels(window_t ** window, double * pixels);

/**
 * @brief Function: void set_label(window_t ** window, int * pixels)
 *
 * \param window: input window data structure window_t
 * \param labels: labels matching the pixels
 *
 * Set window pixels
 */
void set_label(window_t ** window, int * labels);

/**
 * @brief Function: win_type_e get_window_type(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the type of content displayed on the window
 *
 * Get the type of content displayed on the window
 */
win_type_e get_window_type(window_t * window);

/**
 * @brief Function: int get_no_img(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the number of images in pixel array
 *
 * Get number of images in pixels array
 */
int get_no_img(window_t * window);

/**
 * @brief Function: int get_id(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the window handler ID
 *
 * Get window handler ID
 */
int get_id(window_t * window);

/**
 * @brief Function: int get_img_ptr(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the image pointer
 *
 * Get image pointer
 */
int get_img_ptr(window_t * window);

/**
 * @brief Function: int get_width(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the window width
 *
 * Get window width
 */
int get_width(window_t * window);

/**
 * @brief Function: int get_height(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the window height
 *
 * Get window height
 */
int get_height(window_t * window);

/**
 * @brief Function: double * get_pixels(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the window pixels
 *
 * Get window pixels
 */
double * get_pixels(window_t * window);

/**
 * @brief Function: double * get_img(window_t * window, int img_no)
 *
 * \param window: input window data structure window_t
 * \param img_no: image number to be extracted
 * \return the pixels of the image requested
 *
 * Get pixels of image requested
 */
double * get_img(window_t * window, int img_no);

/**
 * @brief Function: int * get_labels(window_t * window)
 *
 * \param window: input window data structure window_t
 * \return the window pixels
 *
 * Get window pixels
 */
int * get_labels(window_t * window);

/**
 * @brief Function: void delete_window(window_t * window)
 *
 * \param window: window data strcture window_t to delete
 * 
 * Delete an window data strcture window_t. Frees up memory as well.
 */
void delete_window(window_t * window);

/**
 * @brief Function: char * win_type_to_str(window_type_e window_type)
 *
 * \param window_type:    window type of window data strcture window_t
 * \return a string with the name of the window type
 * 
 * Convert the window type to a string that can be printed.
 */
char * win_type_to_str(win_type_e window_type);

 /**
 * @brief Function: int compute_no_pixels(window_t * window)
 *
 * \param window:    window data structure
 * \return the number of pixels in the array of pixels
 *
 * Compute the number of pixels in the array of pixels.
 */
int compute_no_pixels(window_t * window);

 /**
 * @brief Function: int compute_img_dim(window_t * window)
 *
 * \param window:    window data structure
 * \return the number of pixels in an image
 *
 * Compute the number of pixels in an image.
 */
int compute_no_pixels_in_img(window_t * window);

/**
 * @brief Function: size_t window_size()
 *
 * \return the size of window data structure window_t
 * 
 * Get the size of window data structure window_t.
 */
size_t window_size();

/** @} */ // End of WindowGroup group
#endif // WINDOW_H
