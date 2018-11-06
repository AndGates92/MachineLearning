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
#include <assert.h>
#include "log.h"
#include "data.h"

data_t * add_data (int* dimensions, int no_dims) {
	data_t * data = NULL;

	data = (data_t *) malloc(sizeof(data_t));
	if (data==NULL) {
		LOG_ERROR("Can't allocate memory for a new data strcuture data_t at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	data->no_dims = no_dims;
	log_info("File %s in function %s at line %0d: Set number of dimensions to %0d\n", __FILE__, __func__, __LINE__,  no_dims);
	data->dimensions = (int *) malloc(no_dims*sizeof(int));
	if (data->dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions of data struct data_t data at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	memcpy(data->dimensions, dimensions, (no_dims*sizeof(int)));
	data->dimensions = dimensions;
	for (int dim = 0; dim < data->no_dims; dim++) {
		log_info("File %s in function %s at line %0d: Set dimensions %0d to %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim]);
	}
	// Total number of units to allocate
	int total_units = 1;
	for (int dim = 0; dim < data->no_dims; dim++) {
		total_units *= dimensions[dim];
	}
	data->elements = NULL;
	data->elements = (elementdatatype_t *) malloc(total_units*sizeof(elementdatatype_t));
	if (data->elements==NULL) {
		LOG_ERROR("Can't allocate memory for elements of data struct data_t at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

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
	log_info("File %s in function %s at line %0d: Set data type to %0d\n", __FILE__, __func__, __LINE__,  no_dims);
	#ifdef DEBUG
		log_info("File %s in function %s at line %0d: Data type: expected %0d actual %0d\n", __FILE__, __func__, __LINE__,  no_dims, (*data)->no_dims);
	#endif // DEBUG
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
	log_info("File %s in function %s at line %0d: Set element(%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)element);
	#ifdef DEBUG
		log_info("File %s in function %s at line %0d: Element(%0d) of data structure data_t : expected %0lf actual %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)element, (double)((*data)->elements[total_offset]));
	#endif // DEBUG
}

void set_data_elements (data_t ** data, elementdatatype_t * elements) {
	int total_units = 1;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(*data);
	dimensions = (int *) malloc(no_dims*sizeof(int));

	if (dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	// Compute total dimension of the array of elements
	for (int dim = 0; dim < no_dims; dim++) {
		total_units = dimensions[dim];
	}
	memcpy((*data)->elements, elements, (total_units*sizeof(elementdatatype_t)));
	#ifdef VERBOSE
		for (int idx=0; idx<total_units; idx++) {
			log_info("File %s in function %s at line %0d: Set element(%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(*(element+idx)));
			#ifdef DEBUG
				log_info("File %s in function %s at line %0d: Element(%0d) of data structure data_t : expected %0lf actual %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(*(element+idx)), (double)((*data)->elements[idx]));
			#endif // DEBUG
		}
	#endif // VERBOSE
}

int * get_dimensions (data_t * data) {
	log_info("File %s in function %s at line %0d: Dimensions of data structure data_t: %0d\n", __FILE__, __func__, __LINE__,  data->dimensions);
	return data->dimensions;
}

int get_no_dims (data_t * data) {
	log_info("File %s in function %s at line %0d: Number of dimensions of data structure data_t: %0d\n", __FILE__, __func__, __LINE__,  data->no_dims);
	return data->no_dims;
}

data_type_e get_data_type (data_t * data) {
	log_info("File %s in function %s at line %0d: Data type of elements in data structure data_t: %0d\n", __FILE__, __func__, __LINE__,  data->no_dims);
	return data->data_type;
}

elementdatatype_t get_element (data_t * data, int * coordinates) {
	int total_offset = 0;
	total_offset = compute_element_offset(data, coordinates);

	elementdatatype_t element = data->elements[total_offset];
	log_info("File %s in function %s at line %0d: Get element(%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  total_offset, (double)(element));
	return element;
}

elementdatatype_t * get_data_elements (data_t * data) {
	#ifdef VERBOSE
		int total_units = 1;
		for (int dim = 0; dim < (*data)->no_dims; dim++) {
			total_units = (*data)->dimensions[dim];
		}
	}
		for (int idx=0; idx<total_units; idx++) {
			log_info("File %s in function %s at line %0d: Get element%0d) of data structure data_t : %0lf\n", __FILE__, __func__, __LINE__,  idx, (double)(data->(*(element+idx))));
		}
	#endif // VERBOSE

	return data->elements;
}

int compute_element_offset (data_t * data, int * coordinates) {
	int data_offset=0;
	int unit_offset=0;
	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(data);
	dimensions = (int *) malloc(no_dims*sizeof(int));

	if (dimensions==NULL) {
		LOG_ERROR("Can't allocate memory for array of dimensions at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	dimensions = get_dimensions(data);

	for (int dim = 0; dim < no_dims; dim++) {
		assert(coordinates[dim] < dimensions[dim]);
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
			strcpy(data_type_str, "SHORTE");
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
			LOG_ERROR("Unknowing data type");
			exit(EXIT_FAILURE);
			break;
	}

	return data_type_str;
}
