/**
 * @copyright
 * @file test_parse_idx.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>
#include "test_parse_idx.h"
#include "neural_network.h"
#include "log.h"

/** \addtogroup ParseIDX Parse IDX Functions
 *  @{
 */

/**
 * @brief Test name
 *
 */
const char* testname = "test_parse_idx";

/** @} */ // End of addtogroup ParseIDX

void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	LOG_INFO(LOW,"Start test: %s\n", testname);

	data_t * test_set_struct_t = NULL;
	data_t * test_label_struct_t = NULL;
	data_t * train_set_struct_t = NULL;
	data_t * train_label_struct_t = NULL;

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set_struct_t, &test_label_struct_t, &train_set_struct_t, &train_label_struct_t);

	LOG_INFO(DEBUG,"Freeing memory allocated for data strcture data_t.\n");
	free(test_set_struct_t);
	free(test_label_struct_t);
	free(train_set_struct_t);
	free(train_label_struct_t);

	LOG_INFO(LOW,"End test: %s\n", testname);

}
