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
#include "log.h"
#include "data.h"
#include "file.h"
#include "parse_idx.h"

void parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	data_t * test_set_struct_t;
	data_t * test_label_struct_t;
	data_t * train_set_struct_t;
	data_t * train_label_struct_t;

	parse_idx_file(test_set, &test_set_struct_t);
	parse_idx_file(test_label, &test_label_struct_t);
	parse_idx_file(train_set, &train_set_struct_t);
	parse_idx_file(train_label, &train_label_struct_t);

	log_info("File %s in function %s at line %0d: Freeing memory allocated for data strcture data_t.\n", __FILE__, __func__, __LINE__);
	free(test_set_struct_t);
	free(test_label_struct_t);
	free(train_set_struct_t);
	free(train_label_struct_t);

}

void parse_idx_file (char * filename, data_t ** data) {
	FILE * fid = NULL;

	// Check is string is empty
	if (strcmp(filename, "")) {
		fid    = file_open(filename, "r");
	}

	if (fid!=NULL) {
		log_info("================================================================\n", filename);
		log_info("Parsing file %s\n", __FILE__, __func__, __LINE__,  filename);
		log_info("================================================================\n", filename);
		log_info("File %s in function %s at line %0d: Parse header of file %s\n", __FILE__, __func__, __LINE__,  filename);
		parse_header(fid, data);
		log_info("File %s in function %s at line %0d: Parse body of file %s\n", __FILE__, __func__, __LINE__,  filename);
		parse_body(fid, data);
		log_info("File %s in function %s at line %0d: Parsing complete.\n", __FILE__, __func__, __LINE__);
		log_info("File %s in function %s at line %0d: Closing file %s\n", __FILE__, __func__, __LINE__,  filename);

	}


	file_close(fid);
}

// Header stores informations in 32-bit integer variables
int read_header(FILE * fid) {
	int value_le = 0;
	fread(&value_le, sizeof(value_le), 1, fid);

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
		LOG_ERROR("Can't allocate memory for magic number at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	magic_number = read_header(fid);
	memcpy(magic_number_bytes, &magic_number, sizeof(int));

	byte no_dims;
	// Number of dimensions is always the LSB of the magic number (i.e. byte0)
	no_dims = magic_number_bytes[0];

	byte data_type;
	// Number of dimensions is always the LSB of the magic number (i.e. byte0)
	data_type = magic_number_bytes[1];

	log_info("File %s in function %s at line %0d: Magic number %0d\n", __FILE__, __func__, __LINE__,  magic_number);
	log_info("File %s in function %s at line %0d:     -> number of dimensions %0d\n", __FILE__, __func__, __LINE__,  no_dims);
	log_info("File %s in function %s at line %0d:     -> data type %0d\n", __FILE__, __func__, __LINE__,  data_type);

	int * dimensions = NULL;
	dimensions = (int *) malloc(no_dims*sizeof(int));
	if (dimensions == NULL) {
		LOG_ERROR("Can't allocate memory for dimensions of data at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	// Loop through dimensions
	for (int dim = 0; dim < no_dims; dim++) {
		dimensions[dim] = read_header(fid);
		log_info("File %s in function %s at line %0d: Dimension %0d: %0d\n", __FILE__, __func__, __LINE__,  dim, dimensions[dim]);
	}

	log_info("File %s in function %s at line %0d: Creating data structure\n", __FILE__, __func__, __LINE__);
	*data = add_data(dimensions, no_dims);

	free (dimensions);
	free (magic_number_bytes);
}

void parse_body(FILE * fid, data_t ** data) {

}
