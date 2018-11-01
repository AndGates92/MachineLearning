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
#include "parse_idx.h"

void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	parse_idx (test_set, train_set, test_label, train_label);

}
