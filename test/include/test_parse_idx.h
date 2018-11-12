#ifndef TEST_PARSE_IDX_H
#define TEST_PARSE_IDX_H
/**
 * @copyright
 * @file test_parse_idx.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Test parse IDX file header file
*/

#include "data.h"

/** @defgroup TestParseIDXGroup Test parse IDX Doxygen Group
 *  Functions and defines concerning image
 *  @{
 */
/** 
 * @brief Function: void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label)
 *
 * \param test_set: test set filename
 * \param train_set: training set filename
 * \param test_label: test label filename
 * \param train_label: training label filename
 *
 * Parse IDX file and ensure data is correctly stored in structure
 */
void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label);

/** 
 * @brief Function: void compare(data_t * data1, data_t * data2)
 *
 * \param data1: first data structure to compare
 * \param data2: second data structure to compare
 *
 * Compare two data structures
 */
void compare(data_t * data1, data_t * data2);
/** @} */ // End of TestParseIDXGroup group
#endif // TEST_PARSE_IDX_H
