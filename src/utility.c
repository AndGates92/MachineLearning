/**
 * @copyright
 * @file utility.c
 * @author Andrea Gianarda
 * @date 22nd of October 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>

void free_memory (void * ptr) {
	if (ptr != NULL) {
		free (ptr);
	}
}
