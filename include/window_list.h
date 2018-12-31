#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 20th of December 2018
 * @brief Window List header file
*/

#include "window.h"

/** @defgroup WindowListGroup WindowList Doxygen Group
 *  Functions and defines concerning window linked list
 *  @{
 */
/**
 * @brief window list data strcture type
 *
 */
typedef struct window_list window_list_t;

/**
 * @brief Function: void initialize_window_list()
 *
 * This function initialize global variables
 */
void initialize_window_list();

/**
 * @brief Function: void add_window_struct(window_t * window)
 *
 * \param window: window data struct to be added
 *
 * This function adds a window data struct to the window linked list
 */
void add_window_struct(window_t * window);

/**
 * @brief Function: void remove_window_struct(int win_id)
 *
 * \param win_id: window ID to be searched
 *
 * This function remove a window structure from window linked list data structure window_list_t
 */
void remove_window_struct(int win_id);

/**
 * @brief Function: void delete_window_struct(window_list_t * window_list)
 *
 * \param window_list: window list whose memory has to be freed up
 *
 * This function frees up memory allocated for an element of window linked list data structure window_list_t
 */
void delete_window_struct(window_list_t * window_list);

/**
 * @brief Function: window_t * search_by_win_id(int win_id)
 *
 * \param win_id: window ID to be searched
 *
 * This function searched the window structure matching the window ID given as argument
 */
window_t * search_by_win_id(int win_id);

/**
 * @brief Function: size_t window_list_size()
 *
 * \return the size of window linked list data structure window_list_t
 * 
 * Get the size of window linked list data structure window_list_t.
 */
size_t window_list_size();

/**
 * @brief Function: window_list_t * get_window_list_head()
 *
 * \return the head pointer of the window list data structure window_list_t
 * 
 * Get the head pointer of window linked list data structure window_list_t.
 */
window_list_t * get_window_list_head();

/** @} */ // End of WindowListGroup
#endif // WINDOW_LIST_H
