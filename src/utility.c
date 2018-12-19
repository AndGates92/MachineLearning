/**
 * @copyright
 * @file utility.c
 * @author Andrea Gianarda
 * @date 22nd of October 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "log.h"
#include "utility.h"

void free_memory (void * ptr) {
	if (ptr != NULL) {
		free (ptr);
	}
}

double * cast_array_to_double (elementdatatype_t * element_set, int dimension) {

	// Pointer to the elements after casting
	double * element_set_double = NULL;

	element_set_double = (double *) malloc(dimension*sizeof(double));
	if (element_set_double==NULL) {
		LOG_ERROR("Can't allocate memory for element_set_double array");
	}

	if (sizeof(elementdatatype_t) == sizeof(double)) {
		memcpy(element_set_double, element_set, (dimension*sizeof(double)));
	} else {
		for (int idx=0; idx < dimension; idx++) {
			(*(element_set_double + idx)) = (double)(*(element_set + idx));
		}
	}

	return element_set_double;
}

double * normalize_elements (double * element_set, elementdatatype_t max_element, int dimension) {

	// Pointer to the elements after casting
	double * element_set_norm = NULL;

	element_set_norm = (double *) malloc(dimension*sizeof(double));
	if (element_set_norm==NULL) {
		LOG_ERROR("Can't allocate memory for element_set_norm array");
	}

	double * max_element_double = NULL;
	max_element_double = cast_array_to_double(&max_element, 1);

	for (int idx=0; idx < dimension; idx++) {
		(*(element_set_norm + idx)) = (*(element_set + idx))/(*max_element_double);
		LOG_INFO(HIGH,"[Normalize Element] Normalized element %0f (Original value %0f Maximum value %0f)", (*(element_set_norm + idx)), (*(element_set + idx)), *max_element_double);
	}

	free_memory(max_element_double);

	return element_set_norm;
}

int * cast_array_to_int (elementdatatype_t * element_set, int dimension) {

	// Pointer to the elements after casting
	int * element_set_int = NULL;

	element_set_int = (int *) malloc(dimension*sizeof(int));
	if (element_set_int==NULL) {
		LOG_ERROR("Can't allocate memory for element_set_int array");
	}

	if (sizeof(elementdatatype_t) == sizeof(int)) {
		memcpy(element_set_int, element_set, (dimension*sizeof(int)));
	} else {
		for (int idx=0; idx < dimension; idx++) {
			(*(element_set_int + idx)) = (int)(*(element_set + idx));
		}
	}

	return element_set_int;
}
