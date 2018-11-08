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
#include "log.h"

void test_parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	LOG_INFO(LOW,"Start input file parsing\n");

	data_t * test_set_struct_t = NULL;
	data_t * test_label_struct_t = NULL;
	data_t * train_set_struct_t = NULL;
	data_t * train_label_struct_t = NULL;

	parse_idx(test_set, &test_set_struct_t);
	parse_idx(test_label, &test_label_struct_t);
	parse_idx(train_set, &train_set_struct_t);
	parse_idx(train_label, &train_label_struct_t);

	LOG_INFO(DEBUG,"Freeing memory allocated for data strcture data_t.\n");
	free(test_set_struct_t);
	free(test_label_struct_t);
	free(train_set_struct_t);
	free(train_label_struct_t);

	LOG_INFO(LOW,"End input file parsing\n");

}
