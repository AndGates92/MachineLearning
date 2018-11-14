/**
 * @copyright
 * @file test_neural_network.c
 * @author Andrea Gianarda
 * @date 13th of November 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>
#include "test_parse_idx.h"
#include "neural_network.h"
#include "log.h"
#include "test_neural_network.h"

/** \addtogroup TestNeuralNetworkGroup
 *  @{
 */

/**
 * @brief Test name
 *
 */
static const char* testname = "test_neural_network";

/** @} */ // End of addtogroup TestParseIDXGroup

void test_neural_network (char * test_set, char * train_set, char * test_label, char * train_label) {

	LOG_INFO(LOW,"Start test: %s\n", testname);

	neural_network (test_set, train_set, test_label, train_label);

	LOG_INFO(LOW,"Test %s: PASSED\n", testname);
}
/** @} */ // End of TestNeuralNetworkGroup group
