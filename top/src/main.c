/**
 * @copyright
 * @file image.c
 * @author Andrea Gianarda
 * @date 22nd of October 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "test_parse_idx.h"
#include "log.h"
#include "main.h"

/** @defgroup MainFunc Main Function
 *  Main function
 *  @{
 */
/** 
 * @brief Function: int main (int argc, char * argv[])
 *
 * \param argc: argument count. Number of arguments including the executable itself. 
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 * \return an integer corresponging to the exit status
 *
 * Decodes the arguments and call functions for further processing
 *
 * Syntax:
 * --> -trs <filename> : training set file
 * --> -tes <filename> : test set file
 * --> -trl <filename> : training label file
 * --> -tel <filename> : test label file
 *
 */

int main (int argc, char * argv []) {

	int test_set_no = -1;
	int train_set_no = -1;
	int test_label_no = -1;
	int train_label_no = -1;

	char * test_set = NULL;
	char * train_set = NULL;
	char * test_label = NULL;
	char * train_label = NULL;

	bool inputfile_given = false;

	// Needs at list 1 input file
	assert(argc > 1);
	// Program needs to know what the input file represents
	assert((argc-1)%2 == 0 );

	test_set = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (test_set==NULL) {
		LOG_ERROR("Can't allocate memory for test set filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	train_set = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (train_set==NULL) {
		LOG_ERROR("Can't allocate memory for training set filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	test_label = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (test_label==NULL) {
		LOG_ERROR("Can't allocate memory for test label filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	train_label = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (train_label==NULL) {
		LOG_ERROR("Can't allocate memory for training label filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	log_info("Command line:\n\tnumber of arguments %0d\n", argc);
	for (int i = 0; i < argc; i++) {
		log_info("\targument %0d: %s\n", i, argv[i]);
	}

	for (int i = 1; i < argc; i++) {
		// Assert that input file is shorter than estimation of input file length
		assert(strlen(argv[i]) < FILENAME_MAX_LENGTH);

		if (!(strcmp(argv[i],trs_opt))) {
			if (train_set_no > 0) {
				LOG_ERROR("Training set file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d\n", train_set_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Training set filename not given as number of arguments is %0d and filename expected position number is %0d\n", argc, (i+1))
			}
			train_set_no = i+1;
			log_info("Training Set argument number: %0d\n", (train_set_no/2));
		} else if (!(strcmp(argv[i],tes_opt))) {
			if (test_set_no > 0) {
				LOG_ERROR("Test set file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d\n", test_set_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Test set filename not given as number of arguments is %0d and filename expected position number is %0d\n", argc, (i+1))
			}
			test_set_no = i+1;
			log_info("Test Set argument number: %0d\n", (test_set_no/2));
		} else if (!(strcmp(argv[i],trl_opt))) {
			if (train_label_no > 0) {
				LOG_ERROR("Training label file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d\n", train_label_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Training label filename not given as number of arguments is %0d and filename expected position number is %0d\n", argc, (i+1))
			}
			train_label_no = i+1;
			log_info("Training Label argument number: %0d\n", (train_label_no/2));
		} else if (!(strcmp(argv[i],tel_opt))) {
			if (test_label_no > 0) {
				LOG_ERROR("Test label file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d\n", test_label_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Test label filename not given as number of arguments is %0d and filename expected position number is %0d\n", argc, (i+1))
			}
			test_label_no = i+1;
			log_info("Test Label argument number: %0d\n", (test_label_no/2));
		}
	}

	log_info("Input files:\n");
	if (test_set_no > 0) {
		strcpy(test_set, argv[test_set_no]);
		log_info("\ttest set: %s\n", test_set);
		inputfile_given = true;
	}
	if (train_set_no > 0) {
		strcpy(train_set, argv[train_set_no]);
		log_info("\ttrain set: %s\n", train_set);
		inputfile_given = true;
	}
	if (test_label_no > 0) {
		strcpy(test_label, argv[test_label_no]);
		log_info("\ttest label: %s\n", test_label);
		inputfile_given = true;
	}
	if (train_label_no > 0) {
		strcpy(train_label, argv[train_label_no]);
		log_info("\ttrain label: %s\n", train_label);
		inputfile_given = true;
	}

	// If no input file is given
	if (inputfile_given == false) {
		log_info("\tNo input file provided:\n");
	}

	test_parse_idx(test_set, train_set, test_label, train_label);

	free(test_set);
	free(train_set);
	free(test_label);
	free(train_label);

	log_info("Tests completed.\n");
	close_logfile();

	return EXIT_SUCCESS;

}
/** @} */ // End of MainFunc group
