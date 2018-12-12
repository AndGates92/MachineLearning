/**
 * @copyright
 * @file data.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body handling data
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "data.h"
#include "utility.h"

data_t * add_data (int* dimensions, int no_dims) {
	data_t * data = NULL;

	data = (data_t *) malloc(sizeof(data_t));
	if (data==NULL) {
		LOG_ERROR("Can't allocate memory for a new data strcuture data_t");
	}
	// ===========================================================================
	// Number of dimensions
	// ===========================================================================
	// Do not support 0 dimension data:
	ASSERT(no_dims >= 1);
	// Do not support more than 3 dimensions:
	// 1 -> Number of elements
	// 2 -> Number of rows
	// 3 -> Number of columns
	ASSERT(no_dims <= 3);
	data->no_dims = no_dims;
	LOG_INFO(MEDIUM,"[New data structure] Set number of dimensions to %0d",  no_dims);

	// ===========================================================================
	// Dimensions
	// ===========================================================================
	data->dimensions = (int *) malloc(no_dims*sizeof(int));

	if (data->dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions of data struct data_t data");
	}
	memcpy(data->dimensions, dimensions, (no_dims*sizeof(int)));
	for (int dim = 0; dim < data->no_dims; dim++) {
		LOG_INFO(MEDIUM,"[New data structure] Set dimension %0d to %0d",  dim, dimensions[dim]);
	}

	// ===========================================================================
	// Elements
	// ===========================================================================
	// Total number of units to allocate
	int total_elements = 0;
	total_elements = compute_total_no_elements(data);
	data->min_element = 0;
	data->max_element = 0;
	data->elements = NULL;
	data->elements = (elementdatatype_t *) malloc(total_elements*sizeof(elementdatatype_t));
	if (data->elements==NULL) {
		LOG_ERROR("Can't allocate memory for elements of data struct data_t");
	}

	// ===========================================================================
	// Data type
	// ===========================================================================
	data->data_type = UNKNOWN;
	data->no_bytes = 0;

	return data;
}

void delete_data (data_t * data) {
	if (data != NULL) {
		free_memory(data->elements);
		LOG_INFO(DEBUG,"Free data elements -> COMPLETED");
		free_memory(data->dimensions);
		LOG_INFO(DEBUG,"Free data dimensions -> COMPLETED");
	}

	free_memory(data);
	LOG_INFO(DEBUG,"Free data structure -> COMPLETED");
}

void set_no_dims (data_t ** data, int no_dims) {
	ASSERT(data != NULL);
	(*data)->no_dims = no_dims;
	LOG_INFO(DEBUG,"Set number of dimensions to %0d",  no_dims);
	LOG_INFO(DEBUG,"Number of dimensions: expected %0d actual %0d",  no_dims, (*data)->no_dims);
}

void set_data_type (data_t ** data, data_type_e data_type) {
	ASSERT((*data) != NULL);
	(*data)->data_type = data_type;
	(*data)->no_bytes = data_type_bytes(data_type);
	char * data_type_str = NULL;
	data_type_str = data_type_to_str(data_type);
	// Assert that each element is large enough to store a value from the IDX file
	LOG_INFO(DEBUG,"Set data type to %s (%0hi bytes)", data_type_str, (*data)->no_bytes);
	free_memory(data_type_str);
	ASSERT (((*data)->no_bytes) >= 1);
	ASSERT ((size_t)((*data)->no_bytes) <= sizeof(elementdatatype_t));
}

void set_dimensions (data_t ** data, int * dimensions) {
	ASSERT((*data) != NULL);
	ASSERT((*data)->dimensions != NULL);
	memcpy((*data)->dimensions, dimensions, (get_no_dims(*data)*sizeof(int)));
	for (int dim = 0; dim < (*data)->no_dims; dim++) {
		LOG_INFO(DEBUG,"Set dimension %0d to %0d",  dim, dimensions[dim]);
		LOG_INFO(DEBUG,"Dimension %0d: expected %0d actual %0d",  dim, dimensions[dim], (*data)->dimensions[dim]);
	}
}

void set_element (data_t ** data, elementdatatype_t element, int* coordinates) {
	int total_offset = 0;

	ASSERT((*data) != NULL);
	ASSERT((*data)->elements != NULL);

	total_offset = compute_element_offset(*data, coordinates);

	(*data)->elements[total_offset] = element;

	elementdatatype_t min_el = 0;
	min_el = get_min_element(*data);
	if (element < min_el) {
		set_min_element(data, element);
	}
	elementdatatype_t max_el = 0;
	max_el = get_max_element(*data);
	if (element > max_el) {
		set_max_element(data, element);
	}

	LOG_INFO(DEBUG,"Set element %0d of data structure data_t : %0lf",  total_offset, (double)element);
	LOG_INFO(DEBUG,"Element(%0d) of data structure data_t : expected %0lf actual %0lf",  total_offset, (double)element, (double)((*data)->elements[total_offset]));
}

void set_data_elements (data_t ** data, elementdatatype_t * elements) {
	int total_elements = 0;

	ASSERT((*data) != NULL);
	ASSERT((*data)->elements != NULL);

	// Compute total dimension of the array of elements
	total_elements = compute_total_no_elements(*data);

	memcpy((*data)->elements, elements, (total_elements*sizeof(elementdatatype_t)));


	for (int idx=0; idx<total_elements; idx++) {
		elementdatatype_t element = 0;
		element = (*(elements+idx));
		LOG_INFO(DEBUG,"Set element(%0d) of data structure data_t : %0lf",  idx, (double)(element));
		LOG_INFO(DEBUG,"Element(%0d) of data structure data_t : expected %0lf actual %0lf",  idx, (double)(element), (double)((*data)->elements[idx]));
		elementdatatype_t min_el = 0;
		min_el = get_min_element(*data);
		if (element < min_el) {
			set_min_element(data, element);
		}
		elementdatatype_t max_el = 0;
		max_el = get_max_element(*data);
		if (element > max_el) {
			set_max_element(data, element);
		}
	}
}

void set_min_element (data_t ** data, elementdatatype_t min_el_value) {
	ASSERT(data != NULL);
	(*data)->min_element = min_el_value;
	LOG_INFO(DEBUG,"Set lowest element in array elements to %0d",  min_el_value);
	LOG_INFO(DEBUG,"Lowest element in array elements: expected %0d actual %0d",  min_el_value, (*data)->min_element);
}

void set_max_element (data_t ** data, elementdatatype_t max_el_value) {
	ASSERT(data != NULL);
	(*data)->max_element = max_el_value;
	LOG_INFO(DEBUG,"Set maximum element in array elements to %0d",  max_el_value);
	LOG_INFO(DEBUG,"Highest element in array elements: expected %0d actual %0d",  max_el_value, (*data)->max_element);
}

int * get_dimensions (data_t * data) {
	ASSERT(data != NULL);
	int no_dims = 0;
	no_dims = get_no_dims(data);

	LOG_INFO(DEBUG,"Number dimensions: %0d",  no_dims);

	int * dimensions = NULL;
	dimensions = (int *) malloc(no_dims*sizeof(int));
	if (dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions");
	}

	memcpy(dimensions, data->dimensions, (no_dims*sizeof(int)));

	for (int dim = 0; dim < data->no_dims; dim++) {
		LOG_INFO(DEBUG,"Dimensions %0d of data structure datat_t is: %0d",  dim, dimensions[dim]);
	}

	return dimensions;
}

int get_dimension (data_t * data, int idx) {
	ASSERT(data != NULL);
	int no_dims = 0;
	no_dims = get_no_dims(data);
	ASSERT(idx < no_dims);

	int dimension = 0;
	dimension = data->dimensions[idx];

	return dimension;
}

int get_no_dims (data_t * data) {
	ASSERT(data != NULL);
	LOG_INFO(DEBUG,"Number of dimensions of data structure data_t: %0d",  data->no_dims);
	return data->no_dims;
}

data_type_e get_data_type (data_t * data) {
	ASSERT(data != NULL);
	data_type_e data_type = UNKNOWN;
	data_type = data->data_type;
	char * data_type_str = NULL;
	data_type_str = data_type_to_str(data_type);
	LOG_INFO(DEBUG,"Data type of elements in data structure data_t: %s",  data_type_str);
	free_memory(data_type_str);
	return data_type;
}

short get_no_bytes (data_t * data) {
	data_type_e data_type = UNKNOWN;
	data_type = get_data_type(data);
	char * data_type_str = NULL;
	data_type_str = data_type_to_str(data_type);
	short no_bytes = 0;
	no_bytes = data->no_bytes;
	LOG_INFO(DEBUG,"Number of bytes of data type %s of data structure data_t: %0hi", data_type_str, no_bytes);
	free_memory(data_type_str);
	return no_bytes;
}

elementdatatype_t get_element (data_t * data, int * coordinates) {
	int total_offset = 0;
	total_offset = compute_element_offset(data, coordinates);

	elementdatatype_t element = data->elements[total_offset];
	LOG_INFO(DEBUG,"Get element(%0d) of data structure data_t : %0lf",  total_offset, (double)(element));
	return element;
}

elementdatatype_t * get_data_elements (data_t * data) {
	elementdatatype_t * elements = NULL;
	int total_elements = 0;

	// Compute total dimension of the array of elements
	total_elements = compute_total_no_elements(data);

	elements = (elementdatatype_t *) malloc(total_elements*sizeof(elementdatatype_t));
	if (elements==NULL) {
		LOG_ERROR("Can't allocate memory for elements array");
	}
	memcpy(elements, data->elements, (total_elements*sizeof(elementdatatype_t)));

	for (int idx=0; idx<total_elements; idx++) {
		LOG_INFO(DEBUG,"Get element%0d) of data structure data_t : %0lf",  idx, (double)(*(elements+idx)));
	}

	return elements;
}

elementdatatype_t get_min_element(data_t * data) {
	ASSERT(data != NULL);
	LOG_INFO(DEBUG,"Lowest element in array elements: %0d",  data->min_element);
	return data->min_element;
}

elementdatatype_t get_max_element(data_t * data) {
	ASSERT(data != NULL);
	LOG_INFO(DEBUG,"Highest element in array elements: %0d",  data->max_element);
	return data->max_element;
}

void get_data_fields(data_t * data, int * no_dims, int ** dimensions, data_type_e * data_type, short * no_bytes, elementdatatype_t ** elements) {

	*no_dims = get_no_dims(data);
	*dimensions = get_dimensions(data);
	*data_type = get_data_type(data);
	*no_bytes = get_no_bytes(data);
	*elements = get_data_elements(data);
}

int compute_element_offset (data_t * data, int * coordinates) {
	int data_offset=0;
	int unit_offset=0;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	dimensions = get_dimensions(data);

	// Initialize to 1 as it will multiply the last coordinate requested
	// It represent the coversion rate betweem=n the current dimension and the last dimension
	unit_offset = 1;

	for (int dim = (no_dims - 1); dim >= 0; dim--) {
		ASSERT(coordinates[dim] < dimensions[dim]);
		// data_offset multiplies the input coordinates by the unit_offset to convert it in last dimension units
		data_offset += (coordinates[dim] * unit_offset);
		unit_offset *= dimensions[dim];
	}

	free_memory (dimensions);

	LOG_INFO(DEBUG,"Element offset: %0d", data_offset);

	return data_offset;
}

char * data_type_to_str (data_type_e data_type) {
	char * data_type_str = NULL;

	data_type_str = (char *) malloc(MAX_DATA_TYPE_LENGTH*sizeof(char));
	if (data_type_str==NULL) {
		LOG_ERROR("Can't allocate memory for string for data type");
	}

	switch (data_type) {
		case SBYTE:
			strcpy(data_type_str, "SBYTE");
			break;
		case UBYTE:
			strcpy(data_type_str, "UBYTE");
			break;
		case SHORT:
			strcpy(data_type_str, "SHORT");
			break;
		case INTEGER:
			strcpy(data_type_str, "INTEGER");
			break;
		case FLOAT:
			strcpy(data_type_str, "FLOAT");
			break;
		case DOUBLE:
			strcpy(data_type_str, "DOUBLE");
			break;
		default:
			LOG_ERROR("Unknown data type. Can't generate string with data type name");
			break;
	}

	return data_type_str;
}

short data_type_bytes (data_type_e data_type) {
	short data_type_bytes = 0;

	switch (data_type) {
		case SBYTE:
			data_type_bytes = 1;
			break;
		case UBYTE:
			data_type_bytes = 1;
			break;
		case SHORT:
			data_type_bytes = 2;
			break;
		case INTEGER:
			data_type_bytes = 4;
			break;
		case FLOAT:
			data_type_bytes = 4;
			break;
		case DOUBLE:
			data_type_bytes = 8;
			break;
		default:
			LOG_ERROR("Unknown data type. Can't compute number of bytes");
			break;
	}

	return data_type_bytes;
}

int compute_total_no_elements(data_t * data) {
	ASSERT(data != NULL);
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	dimensions = get_dimensions(data);

	int total_elements = 1;
	// Compute total dimension of the array of elements
	for (int dim = 0; dim < no_dims; dim++) {
		total_elements *= dimensions[dim];
	}

	free_memory (dimensions);

	return total_elements;
}

elementdatatype_t * get_elements_subset (data_t * data, int no_elements, int * start_position) {
	ASSERT(data != NULL);
	elementdatatype_t * element_array = NULL;
	element_array = (elementdatatype_t *) malloc(no_elements*sizeof(elementdatatype_t));
	if (element_array==NULL) {
		LOG_ERROR("Can't allocate memory for a new data array.");
	}

	int no_dims = 0;
	no_dims = get_no_dims(data);

	int * element_index = NULL;
	element_index = (int *) malloc(no_dims*sizeof(int));
	if (element_index==NULL) {
		LOG_ERROR("Can't allocate memory for a new element index coordinate array.");
	}
	memcpy(element_index, start_position, (no_dims*sizeof(int)));

	int total_elements = 0;
	total_elements = compute_total_no_elements(data);

	for (int position = 0; position < no_elements; position++) {
		int el_offset = 0;
		el_offset = compute_element_offset(data, element_index);
		ASSERT(el_offset < total_elements);
		(*(element_array + position)) = get_element (data, element_index);
		LOG_INFO(DEBUG, "Element %0d (Index in element array %0d): %0d", position,  el_offset, (*(element_array + position)));
		for (int dim = (no_dims - 1); dim >= 0; dim--) {
			int index = 0;
			index = get_dimension(data, dim);
			LOG_INFO(DEBUG, "Dimension %0d: %0d out of %0d", dim, (*(element_index + dim)), index);
			// -1 is because we have to look at the next value of the index we are extracting the data.
			if ((*(element_index + dim)) < (index - 1)) {
				(*(element_index + dim))++;
				break;
			} else {
				(*(element_index + dim)) = 0;
				if (dim < (no_dims - 2)) {
					(*(element_index + dim + 1))++;
				}
			}
		}
	}

	free_memory(element_index);

	return element_array;
}

int element_size (data_t * data) {
	ASSERT(data != NULL);
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	ASSERT(no_dims > 0);
	dimensions = get_dimensions(data);

	int el_size = 0;

	for (int dim = 0; dim < no_dims; dim++) {
		switch (dim) {
			case 0:
				// Number of sets of data
				el_size = 1;
				break;
			case 1:
				// Elements in each set of data
				el_size *= dimensions[dim];
				break;
			case 2:
				// Elements in each set of data (2nd dimension)
				el_size *= dimensions[dim];
				break;
			default:
				LOG_ERROR("Data structure data_t can't support more than 3 dimensions.");
				break;
		}
	}

	free_memory(dimensions);

	return el_size;
}
