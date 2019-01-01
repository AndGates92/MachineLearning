#ifndef MENU_H
#define MENU_H
/**
 * @copyright
 * @file menu.h
 * @author Andrea Gianarda
 * @date 31st of December 2018
 * @brief Menu graphics header file
 */

/** @defgroup MenuGroup Menu Graphics Doxygen Group
 *  Functions and defines concerning graphics of objects
 *  @{
 */
/**
 * @brief menu list data type enumeration menu_list_e
 *
 */
typedef enum menu_list {
	QUIT
} menu_list_e;

/**
 * @brief Function: void add_menu(int menu_win_id)
 *
 * \param menu_win_id: ID of menu window
 *
 * This function adds a menu
 */
void add_menu(int menu_win_id);

/**
 * @brief Function: void menu_items(int item)
 *
 * \param item: item of the menu
 *
 * This function selects actions based on selected item
 */
void menu_items(int item);

/** @} */ // End of MenuGroup
#endif // MENU_H
