#ifndef PARSE_IDX_H
#define PARSE_IDX_H
/**
 * @copyright
 * @file parse_idx.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Parse IDX file header file
*/

#include <stdbool.h>
#include "data.h"

/**
 * @brief Rename char type as byte for readability reasons
 *
 */
typedef char byte;

/**
 * @brief Maximum number of character in every line of parsed file
 *
 */
#define LINE_MAX_LENGTH 2

/**
 * @brief A byte constains 8 bits
 *
 */
#define BIT_IN_BYTE 8

/** @defgroup ParseIDX Parse IDX Functions
 *  Functions concerning image
 *  @{
 */
/** 
 * @brief Function: void parse_idx (char * test_set, char * train_set, char * test_label, char * train_label)
 *
 * \param test_set: test set filename
 * \param train_set: training set filename
 * \param test_label: test label filename
 * \param train_label: training label filename
 *
 * Top level function parsing IDX files
 */
void parse_idx (char * test_set, char * train_set, char * test_label, char * train_label);

/** 
 * @brief Function: void parse_idx_file (char * filename, data_t ** data)
 *
 * \param filename: filename of IDX file to parse
 * \param data:     data strcuture storing informations extracted from the file parsed 
 *
 * Parse IDX file and store data into structure
 */
void parse_idx_file (char * filename, data_t ** data);

/** 
 * @brief Function: int read_header (FILE * fid)
 *
 * \param fid: file description of the file to parse
 *
 * Read the value of one field of the header and convert little endian to big endian
 */
int read_header(FILE * fid);

/** 
 * @brief Function: void parse_header (FILE * fid, data_t ** data)
 *
 * \param fid:  file description of the file to parse
 * \param data: data strcuture storing informations extracted from the file parsed 
 *
 * Parse the header of the IDX file.
 * Extract the following informations:
 *   -# Number of data type
 *   -# Number of dimensions
 *   -# Dimensions
 */
void parse_header(FILE * fid, data_t ** data);

/** 
 * @brief Function: bool read_body (FILE * fid, elementdatatype_t* value)
 *
 * \param fid:            file description of the file to parse
 * \param value:          value read from file
 *
 * Read the value of one field of the body of a IDX file and convert little endian to big endian
 */
bool read_body(FILE * fid, elementdatatype_t* value);

/** 
 * @brief Function: void parse_body (FILE * fid, data_t ** data)
 *
 * \param fid:  file description of the file to parse
 * \param data: data strcuture storing informations extracted from the file parsed 
 *
 * Parse the body the IDX file.
 * Extract the informations:
 *   -# Labels
 *   -# Samples
 */
void parse_body(FILE * fid, data_t ** data);

/** 
 * @brief Function: data_type_e IDX_data_type_to_enum (byte data_type)
 *
 * \param data_type:  data type code as defined by IDX standard
 * \return return the enumerated data type
 *
 * Convert data type as defined in IDX standard to enumerated type
 */
data_type_e IDX_data_type_to_enum (byte data_type);

/** @} */ // End of ParseIDX group
#endif // PARSE_IDX_H
