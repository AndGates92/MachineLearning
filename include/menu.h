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
 * @brief Function: int add_menu()
 *
 * \return menu ID
 *
 * This function adds a menu
 */
int add_menu();

/**
 * @brief Function: void menu_items(int item)
 *
 * \param item: item of the menu
 *
 * This function selects actions based on selected item
 */
void menu_items(int item);

/**
 * @brief Function: void destroy_menu()
 *
 * This function destroys a menu
 */
void destroy_menu();

/** @} */ // End of MenuGroup
#endif // MENU_H
