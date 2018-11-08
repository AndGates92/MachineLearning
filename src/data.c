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

data_t * add_data (int* dimensions, int no_dims) {
	data_t * data = NULL;

	data = (data_t *) malloc(sizeof(data_t));
	if (data==NULL) {
		LOG_ERROR("Can't allocate memory for a new data strcuture data_t at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
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
	log_info("File %s in function %s at line %0d: Set number of dimensions to %0d\n", __FILE__, __func__, __LINE__,  no_dims);

	// ===========================================================================
	// Dimensions
	// ===========================================================================
	data->dimensions = (int *) malloc(no_dims*sizeof(int));
	if (data->dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions of data struct data_t data at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	memcpy(data->dimensions, dimensions, (no_dims*sizeof(int)));
	for (int dim = 0; dim < data->no_dims; dim++) {
		log_info("File %s in function %s at line %0d: Set dimension %0d to %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim]);
	}

	// ===========================================================================
	// Elements
	// ===========================================================================
	// Total number of units to allocate
	int total_elements = 1;
	for (int dim = 0; dim < data->no_dims; dim++) {
		total_elements *= dimensions[dim];
	}
	data->elements = NULL;
	data->elements = (elementdatatype_t *) malloc(total_elements*sizeof(elementdatatype_t));
	if (data->elements==NULL) {
		LOG_ERROR("Can't allocate memory for elements of data struct data_t at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	// ===========================================================================
	// Data type
	// ===========================================================================
	data->data_type = UNKNOWN;
	data->no_bytes = 0;

	return data;
}

void delete_data (data_t * data) {
	free(data->elements);
	log_info("Free data elements -> COMPLETED\n");
	free(data->dimensions);
	log_info("Free data dimensions -> COMPLETED\n");
	free(data);
	log_info("Free data structure -> COMPLETED\n");
}

void set_no_dims (data_t ** data, int no_dims) {
	(*data)->no_dims = no_dims;
	log_info("File %s in function %s at line %0d: Set number of dimensions to %0d\n", __FILE__, __func__, __LINE__,  no_dims);
	#ifdef DEBUG
		log_info("File %s in function %s at line %0d: Number of dimensions: expected %0d actual %0d\n", __FILE__, __func__, __LINE__,  no_dims, (*data)->no_dims);
	#endif // DEBUG
}

void set_data_type (data_t ** data, data_type_e data_type) {
	(*data)->data_type = data_type;
	(*data)->no_bytes = data_type_bytes(data_type);
	// Assert that each element is large enough to store a value from the IDX file
	log_info("File %s in function %s at line %0d: Set data type to %s (%0hi bytes)\n", __FILE__, __func__, __LINE__,  data_type_to_str(data_type), (*data)->no_bytes);
	ASSERT ((size_t)((*data)->no_bytes) <= sizeof(elementdatatype_t));
}

void set_dimensions (data_t ** data, int * dimensions) {
	memcpy((*data)->dimensions, dimensions, (get_no_dims(*data)*sizeof(int)));
	for (int dim = 0; dim < (*data)->no_dims; dim++) {
		log_info("File %s in function %s at line %0d: Set dimension %0d to %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim]);
		#ifdef DEBUG
			log_info("File %s in function %s at line %0d: Dimension %0d: expected %0d actual %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim], (*data)->dimensions[dim]);
		#endif // DEBUG
	}
}

void set_element (data_t ** data, elementdatatype_t element, int* coordinates) {
	int total_offset = 0;
	total_offset = compute_element_offset(*data, coordinates);

	(*data)->elements[total_offset] = element;
	log_info("File %s in function %s at line %0d: Set element %0d of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)element);
	#ifdef DEBUG
		log_info("File %s in function %s at line %0d: Element(%0d) of data structure data_t : expected %0lf actual %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)element, (double)((*data)->elements[total_offset]));
	#endif // DEBUG
}

void set_data_elements (data_t ** data, elementdatatype_t * elements) {
	int total_elements = 1;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(*data);
	dimensions = get_dimensions(*data);

	// Compute total dimension of the array of elements
	for (int dim = 0; dim < no_dims; dim++) {
		total_elements = dimensions[dim];
	}
	memcpy((*data)->elements, elements, (total_elements*sizeof(elementdatatype_t)));

	free (dimensions);

	#ifdef VERBOSE
		for (int idx=0; idx<total_elements; idx++) {
			log_info("File %s in function %s at line %0d: Set element(%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(*(element+idx)));
			#ifdef DEBUG
				log_info("File %s in function %s at line %0d: Element(%0d) of data structure data_t : expected %0lf actual %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(*(element+idx)), (double)((*data)->elements[idx]));
			#endif // DEBUG
		}
	#endif // VERBOSE
}

int * get_dimensions (data_t * data) {
	int no_dims = 0;
	no_dims = get_no_dims(data);

	int * dimensions = NULL;
	dimensions = (int *) malloc(no_dims*sizeof(int));

	if (dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	memcpy(dimensions, data->dimensions, (no_dims*sizeof(int)));

	for (int dim = 0; dim < data->no_dims; dim++) {
		log_info("File %s in function %s at line %0d: Dimensions %0d of data structure datat_t is: %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim]);
	}

	return dimensions;
}

int get_dimension (data_t * data, int idx) {
	int no_dims = 0;
	no_dims = get_no_dims(data);
	ASSERT(idx < no_dims);

	int dimension = 0;

	dimension = data->dimensions[idx];

	return dimension;
}

int get_no_dims (data_t * data) {
	log_info("File %s in function %s at line %0d: Number of dimensions of data structure data_t: %0d\n", __FILE__, __func__, __LINE__,  data->no_dims);
	return data->no_dims;
}

data_type_e get_data_type (data_t * data) {
	log_info("File %s in function %s at line %0d: Data type of elements in data structure data_t: %s\n", __FILE__, __func__, __LINE__,  data_type_to_str(data->data_type));
	return data->data_type;
}

short get_no_bytes (data_t * data) {
	log_info("File %s in function %s at line %0d: Number of bytes of data type %s of data structure data_t: %0hi\n", __FILE__, __func__, __LINE__, data_type_to_str(get_data_type(data)), data->no_bytes);
	return data->no_bytes;
}

elementdatatype_t get_element (data_t * data, int * coordinates) {
	int total_offset = 0;
	total_offset = compute_element_offset(data, coordinates);

	elementdatatype_t element = data->elements[total_offset];
	log_info("File %s in function %s at line %0d: Get element(%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)(element));
	return element;
}

elementdatatype_t * get_data_elements (data_t * data) {
	elementdatatype_t * elements = NULL;
	int total_elements = 1;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	dimensions = get_dimensions(data);

	// Compute total dimension of the array of elements
	for (int dim = 0; dim < no_dims; dim++) {
		total_elements *= dimensions[dim];
	}
	elements = (elementdatatype_t *) malloc(total_elements*sizeof(elementdatatype_t));
	memcpy(elements, data->elements, (total_elements*sizeof(elementdatatype_t)));

	#ifdef VERBOSE
		int total_elements = 1;
		for (int dim = 0; dim < (*data)->no_dims; dim++) {
			total_elements = (*data)->dimensions[dim];
		}
	}
		for (int idx=0; idx<total_elements; idx++) {
			log_info("File %s in function %s at line %0d: Get element%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(*(elements+idx)));
		}
	#endif // VERBOSE

	free(dimensions);

	return elements;
}

int compute_element_offset (data_t * data, int * coordinates) {
	int data_offset=0;
	int unit_offset=0;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	dimensions = get_dimensions(data);

	for (int dim = 0; dim < no_dims; dim++) {
		ASSERT(coordinates[dim] < dimensions[dim]);
		switch (dim) {
			case 0:
				data_offset = coordinates[dim];
				break;
			case 1:
				data_offset *= dimensions[dim];
				unit_offset = coordinates[dim];
				break;
			case 2:
				data_offset *= dimensions[dim];
				unit_offset *= dimensions[dim];
				unit_offset += coordinates[dim];
				break;
			default:
				LOG_ERROR("Not supported more than 3 dimensions.\n Failure at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
				break;
		}
	}

	int total_offset;
	total_offset = data_offset + unit_offset;

	free (dimensions);

	return total_offset;
}

char * data_type_to_str (data_type_e data_type) {
	char * data_type_str = NULL;

	data_type_str = (char *) malloc(MAX_DATA_TYPE_LENGTH*sizeof(char));

	if (data_type_str==NULL) {
		LOG_ERROR("Can't allocate memory for string for data type at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
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
			LOG_ERROR("Unknown data type. Can't generate string with data type name at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
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
			LOG_ERROR("Unknown data type. Can't compute number of bytes at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
			break;
	}

	return data_type_bytes;
}
