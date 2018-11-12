/**
 * @copyright
 * @file neural_network.c
 * @author Andrea Gianarda
 * @date 12th of November 2018
 * @brief Function body parsing IDX file
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "parse_idx.h"
#include "neural_network.h"

void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t) {

	LOG_INFO(LOW,"Start parsing all IDX files\n");

	parse_idx(test_set, test_set_struct_t);
	parse_idx(test_label, test_label_struct_t);
	parse_idx(train_set, train_set_struct_t);
	parse_idx(train_label, train_label_struct_t);

	LOG_INFO(LOW,"End parsing all IDX files\n");

}
