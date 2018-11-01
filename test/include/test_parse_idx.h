#include <stdlib.h>
#include <stdio.h>

/**
 * @copyright
 * @file test_parse_idx.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Test parse IDX file header file
*/

/** @defgroup TestParseIDX Test parse IDX Functions
 *  Functions concerning image
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
/** @} */ // End of ImageFunc group
