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
#include <unistd.h>
#include <math.h>
#include "log.h"
#include "file.h"
#include "parse_idx.h"
#include "utility.h"

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
		LOG_INFO(MEDIUM,"[Parse IDX File] Parse header of file %s",  filename);
		parse_header(fid, data);
		LOG_INFO(MEDIUM,"[Parse IDX File] Parse body of file %s",  filename);
		parse_body(fid, data);
		LOG_INFO(ZERO,"[Parse IDX File] Parsing complete.");
		LOG_INFO(DEBUG,"[Parse IDX File] Closing file %s",  filename);

	}

	file_close(fid);
}

// Header stores informations in 32-bit integer variables
int read_header(FILE * fid) {
	int value_le = 0;
	size_t no_el_read = 0;
	no_el_read = fread(&value_le, sizeof(value_le), 1, fid);

	// Assert that fread successfully read 1 element
	ASSERT(no_el_read == (size_t)1);

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

	char * data_type_str = NULL;
	data_type_str = data_type_to_str(data_type_enum);

	LOG_INFO(MEDIUM,"[Parse Header] Magic number %0d",  magic_number);
	LOG_INFO(MEDIUM,"[Parse Header]     -> number of dimensions %0d",  no_dims);
	LOG_INFO(MEDIUM,"[Parse Header]     -> data type %0d (%s)",  data_type, data_type_str);

	free_memory(data_type_str);
	free_memory(magic_number_bytes);

	int * dimensions = NULL;
	dimensions = (int *) malloc(no_dims*sizeof(int));
	if (dimensions == NULL) {
		LOG_ERROR("Can't allocate memory for dimensions of data");
	}

	// Loop through dimensions
	for (int dim = 0; dim < no_dims; dim++) {
		dimensions[dim] = read_header(fid);
		LOG_INFO(MEDIUM,"[Parse Header] Dimension %0d: %0d",  dim, dimensions[dim]);
	}

	LOG_INFO(MEDIUM,"[Parse Header] Creating data structure data_t");
	*data = add_data(dimensions, no_dims);
	set_data_type(data, data_type_enum);

	free_memory(dimensions);

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

	data_type_e data_type_enum = UNKNOWN;
	data_type_enum = get_data_type(*data);

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
	total_elements = compute_total_no_elements(*data);

	element_cnt = datatype_element_ratio;

	do {
		// Variable storing parsed data (reading sizeof(elementdatatype_t) bytes)
		elementdatatype_t data_read = 0;
		eof = read_body(fid, &data_read);

		LOG_INFO(DEBUG,"[Parse Body] Data read %0d, End of file %s", data_read, bool_to_str(eof));

		// Variable storing sizeof(elementdatatype_t) bytes of the data grouped as bytes
		byte * element_bytes = NULL;
		element_bytes = (byte *) malloc(sizeof(elementdatatype_t));
		if (element_bytes == NULL) {
			LOG_ERROR("Can't allocate memory for an array to split elements in single bytes");
		}

		memcpy(element_bytes, &data_read, sizeof(elementdatatype_t));

		int valid_elements = 0;
		if (eof) {
			ASSERT((total_elements + datatype_element_ratio - element_cnt) <= datatype_element_ratio);
			ASSERT((total_elements + datatype_element_ratio - element_cnt) >= 0);
			valid_elements = (total_elements + datatype_element_ratio - element_cnt);
		} else {
			ASSERT((total_elements - element_cnt) >= 0);
			valid_elements = datatype_element_ratio;
		}
		for (int el = 0; el < valid_elements; el++) {

			element_cnt--;
			ASSERT(element_cnt >= 0);

			elementdatatype_t element = 0;
			for (int byte = 0; byte < no_bytes; byte++) {
				int idx = 0;
				idx = (el*no_bytes)+byte;
				element += (element_bytes[idx] << (BIT_IN_BYTE*byte));
			}
			LOG_INFO(DEBUG,"[Parse Body] Element %0d out of %0d: %0d", element_cnt, total_elements, element);

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

			if (data_type_enum == UBYTE) {
				elementdatatype_t mask = 0;
				mask = ((elementdatatype_t)pow(2,(BIT_IN_BYTE*no_bytes))) - 1;
				// Tie to 0 MSBs 
				element = (element & mask);
			}

			set_element(data, element, coordinates);

			free_memory(coordinates);

			ASSERT(element_cnt < total_elements);
		}

		element_cnt += (2*datatype_element_ratio);

		free_memory (element_bytes);

	} while (eof == false);

	free_memory(dimensions);

}

data_type_e IDX_data_type_to_enum (byte data_type) {
	data_type_e data_type_enum = UNKNOWN;

	switch (data_type) {
		case 0x8:
			data_type_enum = UBYTE;
			break;
		case 0x9:
			data_type_enum = SBYTE;
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
