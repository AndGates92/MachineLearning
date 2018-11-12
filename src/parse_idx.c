/**
 * @copyright
 * @file parse_idx.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body parsing IDX file
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "file.h"
#include "parse_idx.h"


void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t) {

	LOG_INFO(LOW,"Start parsing all IDX files\n");

	parse_idx(test_set, test_set_struct_t);
	parse_idx(test_label, test_label_struct_t);
	parse_idx(train_set, train_set_struct_t);
	parse_idx(train_label, train_label_struct_t);

	LOG_INFO(LOW,"End parsing all IDX files\n");

}

void parse_idx (char * filename, data_t ** data) {
	FILE * fid = NULL;

	// Check is string is empty
	if (strcmp(filename, "")) {
		fid    = file_open(filename, "r");
	}

	if (fid!=NULL) {
		log_info(ZERO, "================================================================\n", filename);
		log_info(ZERO, "Parsing file %s\n", filename);
		log_info(ZERO, "================================================================\n", filename);
		LOG_INFO(MEDIUM,"Parse header of file %s\n",  filename);
		parse_header(fid, data);
		LOG_INFO(MEDIUM,"Parse body of file %s\n",  filename);
		parse_body(fid, data);
		LOG_INFO(ZERO,"Parsing complete.\n");
		LOG_INFO(DEBUG,"Closing file %s\n",  filename);

	}


	file_close(fid);
}

// Header stores informations in 32-bit integer variables
int read_header(FILE * fid) {
	int value_le = 0;
	size_t no_el_read = 0;
	no_el_read = fread(&value_le, sizeof(value_le), 1, fid);

	// Assert that fread successfully read 1 element
	ASSERT(no_el_read == 1);

	// Convert from little endian to big endian
	int value_be=0;
	const int int_bits = BIT_IN_BYTE*sizeof(value_le);
	const int mask = 0xFF;
	for(int byte = 0; byte < (int) sizeof(value_le); byte++) {
		value_be+=(((value_le>>(int_bits-(BIT_IN_BYTE*(byte+1)))) & mask) << (BIT_IN_BYTE*byte));
	}

	return value_be;
}

void parse_header(FILE * fid, data_t ** data) {

	// Variable storing the 32 bits fo the magic number
	int magic_number;
	// Variable storing the 32 bits fo the magic number grouped as bytes (8 bits)
	byte * magic_number_bytes = NULL;
	magic_number_bytes = (byte *) malloc(sizeof(int)*sizeof(byte));
	if (magic_number_bytes == NULL) {
		LOG_ERROR("Can't allocate memory for magic number");
	}

	magic_number = read_header(fid);
	memcpy(magic_number_bytes, &magic_number, sizeof(int));

	byte no_dims;
	// Number of dimensions is always the LSB of the magic number (i.e. byte0)
	no_dims = magic_number_bytes[0];

	byte data_type;
	data_type_e data_type_enum;
	// Number of dimensions is always the LSB of the magic number (i.e. byte0)
	data_type = magic_number_bytes[1];
	data_type_enum = IDX_data_type_to_enum(data_type);

	LOG_INFO(MEDIUM,"Magic number %0d\n",  magic_number);
	LOG_INFO(MEDIUM,"    -> number of dimensions %0d\n",  no_dims);
	LOG_INFO(MEDIUM,"    -> data type %0d (%s)\n",  data_type, data_type_to_str(data_type_enum));

	free(magic_number_bytes);

	int * dimensions = NULL;
	dimensions = (int *) malloc(no_dims*sizeof(int));
	if (dimensions == NULL) {
		LOG_ERROR("Can't allocate memory for dimensions of data");
	}

	// Loop through dimensions
	for (int dim = 0; dim < no_dims; dim++) {
		dimensions[dim] = read_header(fid);
		LOG_INFO(MEDIUM,"Dimension %0d: %0d\n",  dim, dimensions[dim]);
	}

	LOG_INFO(MEDIUM,"Creating data structure data_t\n");
	*data = add_data(dimensions, no_dims);
	set_data_type(data, data_type_enum);

	free(dimensions);


}

// Header stores informations in 32-bit integer variables
bool read_body(FILE * fid, elementdatatype_t* value) {
	elementdatatype_t value_le = 0;
	size_t no_el_read = 0;
        no_el_read = fread(&value_le, sizeof(value_le), 1, fid);

	bool eof = false;
	if (no_el_read == 1) {
		eof = false;
	} else {
		eof = true;
	}

	// Convert from little endian to big endian
	elementdatatype_t value_be=0;
	const int int_bits = BIT_IN_BYTE*sizeof(value_le);
	const int mask = 0xFF;
	for(int byte = 0; byte < (int) sizeof(value_le); byte++) {
		value_be+=(((value_le>>(int_bits-(BIT_IN_BYTE*(byte+1)))) & mask) << (BIT_IN_BYTE*byte));
	}

	*value = value_be;

	return eof;
}

void parse_body(FILE * fid, data_t ** data) {
	bool eof = false;
	short no_bytes = 0;
	int element_cnt=0;

	no_bytes = get_no_bytes(*data);
	ASSERT(no_bytes > 0);

	int datatype_element_ratio = 0;
	datatype_element_ratio = sizeof(elementdatatype_t)/no_bytes;
	ASSERT (datatype_element_ratio > 0);

	// Get total number of elements
	int * dimensions = NULL;
	dimensions = get_dimensions(*data);

	int no_dims = 0;
	no_dims = get_no_dims(*data);

	int total_elements = 1;
	// Compute total dimension of the array of elements
	for (int dim = 0; dim < no_dims; dim++) {
		total_elements *= dimensions[dim];
	}

	do {
		// Variable storing parsed data
		elementdatatype_t data_read = 0;
		eof = read_body(fid, &data_read);

		LOG_INFO(DEBUG,"Data read %0d, End of file %s\n", data_read, bool_to_str(eof));

		// Variable storing the 32 bits fo the magic number grouped as bytes (8 bits)
		byte * element_bytes = NULL;
		element_bytes = (byte *) malloc(sizeof(int)*sizeof(byte));
		if (element_bytes == NULL) {
			LOG_ERROR("Can't allocate memory for an array to split elements in single bytes");
		}

		memcpy(element_bytes, &data_read, sizeof(elementdatatype_t));

		int valid_elements = 0;
		if (eof) {
			ASSERT((total_elements - element_cnt) <= datatype_element_ratio);
			valid_elements = (total_elements - element_cnt);
		} else {
			ASSERT((total_elements - element_cnt) >= datatype_element_ratio);
			valid_elements = datatype_element_ratio;
		}

		for (int el = 0; el < valid_elements; el++) {
			elementdatatype_t element = 0;
			for (int byte = 0; byte < no_bytes; byte++) {
				int idx = 0;
				idx = (el*no_bytes)+byte;
				element += (element_bytes[idx] << (BIT_IN_BYTE*byte));
			}
			LOG_INFO(HIGH,"Element %0d out of %0d: %0d\n", element_cnt, total_elements, element);

			int * coordinates = NULL;
			coordinates = (int *) malloc(no_dims*sizeof(int));
			if (coordinates==NULL) {
				LOG_ERROR("Can't allocate memory for array of dimensions of data struct data_t data");
			}

			int remainder = 0;
			remainder = element_cnt;
			for (int dim = (no_dims-1); dim >= 0; dim--) {
				// Compute coordinate - It is the remainder module the max value of the current coordinate
				coordinates[dim] = remainder % dimensions[dim];
				// Compute remainer for the enxt coordinate
				remainder /= dimensions[dim];
			}

			ASSERT(remainder == 0);

			set_element(data, element, coordinates);

			element_cnt++;
		}

		free (element_bytes);

	} while (eof == false);

	free(dimensions);

	ASSERT(element_cnt == total_elements);

}

data_type_e IDX_data_type_to_enum (byte data_type) {
	data_type_e data_type_enum = UNKNOWN;

	switch (data_type) {
		case 0x8:
			data_type_enum = SBYTE;
			break;
		case 0x9:
			data_type_enum = UBYTE;
			break;
		case 0xB:
			data_type_enum = SHORT;
			break;
		case 0xC:
			data_type_enum = INTEGER;
			break;
		case 0xD:
			data_type_enum = FLOAT;
			break;
		case 0xE:
			data_type_enum = DOUBLE;
			break;
		default:
			LOG_ERROR("Unknown data type ID %0d. Can't generate convert to data_type_e type", data_type);
			break;
	}

	return data_type_enum;
}
