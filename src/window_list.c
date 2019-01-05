/**
 * @copyright
 * @file window_list.c
 * @author Andrea Gianarda
 * @date 20th of December 2018
 * @brief Functions related to windows linked list
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "window_list.h"

/** @addtogroup WindowListGroup
 *  @{
 */
/**
 * @brief window list data strcture window_list
 *
 */
struct window_list {
	window_list_t * previous; /**< Previous Window */
	window_t * window; /**< Window */
	window_list_t * next; /**< Next Window */
};
/** @} */ // End of addtogroup WindowListGroup

window_list_t * head_window;

void initialize_window_list() {
	head_window = NULL;
}

void add_window_struct(window_t * window) {

	window_list_t* new_window = NULL;

	new_window = (window_list_t*) malloc(sizeof(window_list_t));
	if(new_window == NULL) {
		LOG_ERROR("Can't allocate memory for new window list data structure window_list_t");
	}

	new_window->window = window;
	new_window->previous = NULL;

	if(head_window != NULL) {
		head_window->previous = new_window;
	}

	new_window->next = head_window;
	head_window = new_window;
}

void remove_window_struct(int win_id) {

	window_list_t * window_list = NULL;
	// Initially point to the head
	window_list = head_window;

	while (window_list != NULL) {
		int curr_win_id = 0;
		curr_win_id = get_win_id(window_list->window);

		LOG_INFO(DEBUG,"[Delete window structure] Window ID: current %0d searched %0d",  curr_win_id, win_id);

		if (curr_win_id == win_id) {

			window_list_t * window_list_found = NULL;
			// Store pointer to searched window list
			window_list_found = window_list;

			if (window_list == head_window) {
				// Move head pointer as window list to delete is the head
				if (window_list->next == NULL) {
					head_window = NULL;
				} else {
					head_window = head_window->next;
					head_window->previous = NULL;
				}
			} else {
				window_list->previous->next = window_list->next;
				if (window_list->next != NULL) {
					window_list->next->previous = window_list->previous;
				}
			}

			delete_window_struct(window_list_found);

		}

		window_list = window_list->next;

	}
}

void delete_window_struct(window_list_t * window_list) {

	delete_window(window_list->window);
	LOG_INFO(DEBUG,"[Delete window list] Free window data structure -> COMPLETED");
	free_memory(window_list);
	LOG_INFO(DEBUG,"[Delete window list] Free window list data structure -> COMPLETED");

}

window_t * search_by_win_id(int win_id) {

	window_list_t * window_list = NULL;
	// Initially point to the head
	window_list = head_window;

	window_t * window_found = NULL;

	while (window_list != NULL) {
		int curr_win_id = 0;
		curr_win_id = get_win_id(window_list->window);

		LOG_INFO(DEBUG,"[New search by windows ID] Window ID: current %0d searched %0d",  curr_win_id, win_id);

		if (curr_win_id == win_id) {
			window_found = window_list->window;
			return window_found;
		}

		window_list = window_list->next;

	}

	LOG_ERROR("Couldn't find window matching window ID %0d", win_id);
	return NULL;
}

size_t window_list_size() {
	return (sizeof(window_list_t));
}

window_list_t * get_window_list_head() {
	return head_window;
}
