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
 * @brief Length of menu entry string
 *
 */
#define MAX_MENU_ENTRY_LENGTH 10

/**
 * @brief menu entry data type enumeration menu_entry_e
 *
 */
typedef enum menu_entry {
	PREV_OBJ,
	NEXT_OBJ,
	QUIT
} menu_entry_e;

/**
 * @brief Function: int add_menu()
 *
 * \return menu ID
 *
 * This function adds a menu
 */
int add_menu();

/**
 * @brief Function: void menu_entries(int entry)
 *
 * \param entry: entry of the menu
 *
 * This function selects actions based on selected entry
 */
void menu_entries(int entry);

/**
 * @brief Function: char * menu_entry_to_str(menu_entry_e menu_entry)
 *
 * \param menu_entry: menu entry
 * \return a string with the name of the menu entry
 * 
 * Convert the window type to a string that can be printed.
 */
char * menu_entry_to_str(menu_entry_e menu_entry);

/** @} */ // End of MenuGroup
#endif // MENU_H
