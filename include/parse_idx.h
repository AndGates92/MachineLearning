/**
 * @copyright
 * @file parse_idx.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Parse IDX file header file
*/

/**
 * @brief Maximum number of character in every line of parsed file
 *
 */
#define LINE_MAX_LENGTH 20

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

/** @} */ // End of ParseIDX group
