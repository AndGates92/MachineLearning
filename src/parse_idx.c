/**
 * @copyright
 * @file parse_idx.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body parsing IDX file
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "file.h"
#include "parse_idx.h"

void parse_idx (char * test_set, char * train_set, char * test_label, char * train_label) {

	parse_idx_file(test_set);
	parse_idx_file(test_label);
	parse_idx_file(train_set);
	parse_idx_file(train_label);

}

void parse_idx_file (char * filename) {
	FILE * fid = NULL;

	// Check is string is empty
	if (strcmp(filename, "")) {
		fid    = file_open(filename, "r");
	}

	if (fid!=NULL) {
		log_info("Parsing file %s\n", filename);
		char * fileline = NULL;
		fileline = (char *) malloc(LINE_MAX_LENGTH*sizeof(char));
		if (fileline==NULL) {
			LOG_ERROR("Can't allocate memory for variable to store parsed filelines at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
		}

		while (fgets(fileline, LINE_MAX_LENGTH, fid) == NULL) {

		}

		free(fileline);
	}

	file_close(fid);
}
