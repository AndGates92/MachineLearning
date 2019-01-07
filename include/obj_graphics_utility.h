#ifndef OBJ_GRAPHICS_UTILITY_H
#define OBJ_GRAPHICS_UTILITY_H
/**
 * @copyright
 * @file obj_graphics_utility.h
 * @author Andrea Gianarda
 * @date 02nd of January 2019
 * @brief Object graphics utility functions header file
 */

/** @defgroup UtilityObjGraphicsGroup Object Graphics Doxygen Group
 *  Functions and defines concerning graphics of objects
 *  @{
 */

/**
 * @brief Number of base colours
 *
 */
#define NO_COLOURS 3

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
 * @brief Function: void change_img_ptr(int step)
 *
 * \param step: value to add to the image pointer
 *
 * Get current window ID and increment the image pointer by the value of step input
 */
void change_img_ptr(int step);

/**
 * @brief Function: void destroy_window()
 *
 * This function destroys a window
 */
void destroy_window();

/**
 * @brief Function: void destroy_menu()
 *
 * This function destroys a menu
 */
void destroy_menu();

/**
 * @brief Function: void remove_window()
 *
 * This function destroys a window and its menu
 */
void remove_window();

/**
 * @brief Function: int orig_idx_mgmt (bool reduced, int orig, int reshaped_idx, int orig_idx, int * corr, double ratio, int ratio_int, double ratio_dec, bool * add_extra)
 *
 * \param reduced: dimension is reduced with respect to original dimensions
 * \param orig: original dinension
 * \param reshaped_idx: index of reshaped dimension
 * \param orig_idx: index of original dimension
 * \param corr: correction for idx increase logic.
 * \param ratio: ratio between new and original dimension.
 * \param ratio_int: integer part of ratio between new and original dimension.
 * \param ratio_dec: decimal part of ratio between new and original dimension.
 * \param add_extra: need to add extra line or column flag.
 * \return index of original image
 *
 * Computes the inex of a given dimensione in the original image
 */
int orig_idx_mgmt (bool reduced, int orig, int reshaped_idx, int orig_idx, int * corr, double ratio, int ratio_int, double ratio_dec, bool * add_extra);
/** @} */ // End of UtilityObjGraphicsGroup
#endif // OBJ_GRAPHICS_UTILITY_H
