/**
 * @copyright
 * @file parse_idx.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Parse IDX file header file
*/

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
 * @brief Function: void parse_idx_file (char * filename)
 *
 * \param filename: filename of IDX file to parse
 *
 * Parse IDX file and store data into structure
 */
void parse_idx_file (char * filename);

/** 
 * @brief Function: int read_header (FILE * fid)
 *
 * \param fid: file description of the file to parse
 *
 * Read the value of one field of the header and convert little endian to big endian
 */
int read_header(FILE * fid);

/** 
 * @brief Function: void parse_header (FILE * fid)
 *
 * \param fid: file description of the file to parse
 *
 * Parse the header of the IDX file.
 * Extract the following informations:
 *   -# Number of data type
 *   -# Number of dimensions
 *   -# Dimensions
 */
void parse_header(FILE * fid);



/** @} */ // End of ParseIDX group
