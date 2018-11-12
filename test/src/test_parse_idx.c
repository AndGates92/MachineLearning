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

/** \addtogroup TestParseIDXGroup
 *  @{
 */

/**
 * @brief Test name
 *
 */
const char* testname = "test_parse_idx";

/** @} */ // End of addtogroup TestParseIDXGroup

void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	LOG_INFO(LOW,"Start test: %s\n", testname);

	// First set of data structures
	data_t * test_set_struct_t = NULL;
	data_t * test_label_struct_t = NULL;
	data_t * train_set_struct_t = NULL;
	data_t * train_label_struct_t = NULL;

	// Second set of data structures
	data_t * test_set2_struct_t = NULL;
	data_t * test_label2_struct_t = NULL;
	data_t * train_set2_struct_t = NULL;
	data_t * train_label2_struct_t = NULL;

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set_struct_t, &test_label_struct_t, &train_set_struct_t, &train_label_struct_t);

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set2_struct_t, &test_label2_struct_t, &train_set2_struct_t, &train_label2_struct_t);

	LOG_INFO(LOW,"Compare test set data structures.\n");
	compare(test_set_struct_t, test_set2_struct_t);
	LOG_INFO(LOW,"Compare test label data structures.\n");
	compare(test_label_struct_t, test_label2_struct_t);
	LOG_INFO(LOW,"Compare training set data structures.\n");
	compare(train_set_struct_t, train_set2_struct_t);
	LOG_INFO(LOW,"Compare training label data structures.\n");
	compare(train_label_struct_t, train_label2_struct_t);

	LOG_INFO(DEBUG,"Freeing memory allocated for 1st set of data strcture data_t.\n");
	free(test_set_struct_t);
	free(test_label_struct_t);
	free(train_set_struct_t);
	free(train_label_struct_t);

	LOG_INFO(DEBUG,"Freeing memory allocated for 2nd set of data strcture data_t.\n");
	free(test_set2_struct_t);
	free(test_label2_struct_t);
	free(train_set2_struct_t);
	free(train_label2_struct_t);

	LOG_INFO(LOW,"Test %s: PASSED\n", testname);

}

void compare(data_t * data1, data_t * data2) {

	LOG_INFO(HIGH,"Start comparison\n", testname);

	int no_dims1 = 0;
	int * dimensions1 = NULL;
	data_type_e data_type1 = UNKNOWN;
	short no_bytes1 = 0;
	elementdatatype_t * elements1 = NULL;

	if (data1 != NULL) {
		// Fields of data1
		get_data_fields(data1, &no_dims1, &dimensions1, &data_type1, &no_bytes1, &elements1);
	}

	int no_dims2 = 0;
	int * dimensions2 = NULL;
	data_type_e data_type2 = UNKNOWN;
	short no_bytes2 = 0;
	elementdatatype_t * elements2 = NULL;

	if (data2 != NULL) {
		// Fields of data2
		get_data_fields(data2, &no_dims2, &dimensions2, &data_type2, &no_bytes2, &elements2);
	}

	// Ensures that either data1 and data2 are NULL pointers or are both non-NULL
	ASSERT (((data1 == NULL) & (data2 == NULL)) | ((data1 != NULL) & (data2 != NULL)));

	if ((data1 != NULL) & (data2 != NULL)) {
		// Compare number of dimensions
		LOG_INFO(DEBUG,"Number of dimensions: %0d vs %0d\n", no_dims1, no_dims2);
		ASSERT (no_dims1 >= 1);
		ASSERT (no_dims1 <= 3);
		ASSERT (no_dims2 >= 1);
		ASSERT (no_dims2 <= 3);
		ASSERT (no_dims1 == no_dims2);

		// Compare number of bytes of each element
		LOG_INFO(DEBUG,"Number of bytes: %0d vs %0d\n", no_bytes1, no_bytes2);
		ASSERT (no_bytes1 >= 1);
		ASSERT (no_bytes2 >= 1);
		ASSERT (no_bytes1 == no_bytes2);

		// Compare data types
		LOG_INFO(DEBUG,"Data type: %s vs %s\n", data_type_to_str(data_type1), data_type_to_str(data_type2));
		ASSERT (data_type1 != UNKNOWN);
		ASSERT (data_type2 != UNKNOWN);
		ASSERT (data_type1 == data_type2);

		// Compare dimensions
		ASSERT(dimensions1 != NULL);
		ASSERT(dimensions2 != NULL);
//		ASSERT(sizeof(dimensions1) == (no_dims1*sizeof(int)));
//		ASSERT(sizeof(dimensions2) == (no_dims2*sizeof(int)));
		for (int dim = 0; dim < no_dims1; dim++) {
			LOG_INFO(DEBUG,"Dimension %0d: %0d vs %0d\n", dimensions1[dim], dimensions2[dim]);
			ASSERT(dimensions1[dim] > 0);
			ASSERT(dimensions2[dim] > 0);
			ASSERT(dimensions1[dim] == dimensions2[dim]);
		}

		int total_elements1 = 0;
		total_elements1 = compute_total_no_elements(data1);
		int total_elements2 = 0;
		total_elements2 = compute_total_no_elements(data2);
		LOG_INFO(DEBUG,"Total number of elements: %0d vs %0d\n", total_elements1, total_elements2);
		ASSERT(total_elements1 == total_elements2);

		// Compare elements
		ASSERT(elements1 != NULL);
		ASSERT(elements2 != NULL);
//		ASSERT(sizeof(elements1) == (total_elements1*sizeof(elementdatatype_t)));
//		ASSERT(sizeof(elements2) == (total_elements2*sizeof(elementdatatype_t)));
		for (int el = 0; el < total_elements1; el++) {
			LOG_INFO(DEBUG,"Element %0d in data structures: %0d vs %0d\n", elements1[el], elements2[el]);
			ASSERT(elements1[el] == elements2[el]);
		}
	}

	free(dimensions1);
	free(dimensions2);
	free(elements1);
	free(elements2);

}
