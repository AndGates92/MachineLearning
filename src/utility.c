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

unsigned char * cast_array_to_unsigned_byte (elementdatatype_t * element_set, int dimension) {

	// Pointer to the elements after casting
	unsigned char * element_set_unsigned_byte = NULL;

	element_set_unsigned_byte = (unsigned char *) malloc(dimension*sizeof(unsigned char));
	if (element_set_unsigned_byte==NULL) {
		LOG_ERROR("Can't allocate memory for element_set_unsigned_byte array");
	}

	if (sizeof(elementdatatype_t) == sizeof(unsigned char)) {
		memcpy(element_set_unsigned_byte, element_set, (dimension*sizeof(unsigned char)));
	} else {
		for (int idx=0; idx < dimension; idx++) {
			(*(element_set_unsigned_byte + idx)) = (unsigned char)(*(element_set + idx));
		}
	}

	return element_set_unsigned_byte;
}

float * cast_array_to_float (elementdatatype_t * element_set, int dimension) {

	// Pointer to the elements after casting
	float * element_set_float = NULL;

	element_set_float = (float *) malloc(dimension*sizeof(float));
	if (element_set_float==NULL) {
		LOG_ERROR("Can't allocate memory for element_set_float array");
	}

	if (sizeof(elementdatatype_t) == sizeof(float)) {
		memcpy(element_set_float, element_set, (dimension*sizeof(float)));
	} else {
		for (int idx=0; idx < dimension; idx++) {
			(*(element_set_float + idx)) = (float)(*(element_set + idx));
		}
	}

	return element_set_float;
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

void statusbar(char * str, int idx, int max_val) {

	ASSERT(idx <= max_val);

	double ratio = 0;
	ratio = ((double) idx)/((double) max_val);
	double percentage = 0;
	percentage = 100.0*ratio;
	int no_of_symbols_in_progress_bar = 0;
	no_of_symbols_in_progress_bar = (int)((((double) (PROGRESS_BAR_LENGTH))*((double) idx))/((double) max_val));

	printf("[%s %.3lf%%] ", str, percentage);
	for (int no_sym = 0; no_sym < no_of_symbols_in_progress_bar; no_sym++) {
		printf("%s", STRINGIFY_EXPR(PROGRESS_BAR_SYMBOL));
	}
	if (idx == max_val) {
		printf("\n");
	} else {
		printf("\r");
		fflush(stdout);
	}
}
