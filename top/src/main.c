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
#include <string.h>
#include <time.h>
#include "test_parse_idx.h"
#include "test_neural_network.h"
#include "log.h"
#include "utility.h"
#include "main.h"

/** @addtogroup MainGroup
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

	// Initialize seed
	srand(time(NULL));

	// Needs at list 1 input file
	ASSERT(argc > 1);
	// Program needs to know what the input file represents
	ASSERT((argc-1)%2 == 0 );

	test_set = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (test_set==NULL) {
		LOG_ERROR("Can't allocate memory for test set filename");
	}

	train_set = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (train_set==NULL) {
		LOG_ERROR("Can't allocate memory for training set filename");
	}

	test_label = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (test_label==NULL) {
		LOG_ERROR("Can't allocate memory for test label filename");
	}

	train_label = (char *) malloc(FILENAME_MAX_LENGTH*sizeof(char));
	if (train_label==NULL) {
		LOG_ERROR("Can't allocate memory for training label filename");
	}

	LOG_INFO(ZERO,"[Main] Verbosity level: %0d", VERBOSITY);
	LOG_INFO(DEBUG,"[Main] Command line:");
	LOG_INFO(DEBUG,"[Main] Number of arguments %0d",  argc);
	for (int i = 0; i < argc; i++) {
		LOG_INFO(DEBUG,"[Main] \targument %0d: %s",  i, argv[i]);
	}

	for (int i = 1; i < argc; i++) {
		// Assert that input file is shorter than estimation of input file length
		ASSERT(strlen(argv[i]) < FILENAME_MAX_LENGTH);

		if (!(strcmp(argv[i],trs_opt))) {
			if (train_set_no > 0) {
				LOG_ERROR("Training set file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d", train_set_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Training set filename not given as number of arguments is %0d and filename expected position number is %0d", argc, (i+1))
			}
			train_set_no = i+1;
			LOG_INFO(DEBUG,"[Main] Training Set argument number: %0d",  (train_set_no/2));
		} else if (!(strcmp(argv[i],tes_opt))) {
			if (test_set_no > 0) {
				LOG_ERROR("Test set file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d", test_set_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Test set filename not given as number of arguments is %0d and filename expected position number is %0d", argc, (i+1))
			}
			test_set_no = i+1;
			LOG_INFO(DEBUG,"[Main] Test Set argument number: %0d",  (test_set_no/2));
		} else if (!(strcmp(argv[i],trl_opt))) {
			if (train_label_no > 0) {
				LOG_ERROR("Training label file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d", train_label_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Training label filename not given as number of arguments is %0d and filename expected position number is %0d", argc, (i+1))
			}
			train_label_no = i+1;
			LOG_INFO(DEBUG,"[Main] Training Label argument number: %0d",  (train_label_no/2));
		} else if (!(strcmp(argv[i],tel_opt))) {
			if (test_label_no > 0) {
				LOG_ERROR("Test label file has already been provided as an argument. Previous rgument position was %0d. New argument position is %0d", test_label_no, (i+1))
			}
			if (argc < (i+1)) {
				LOG_ERROR("Test label filename not given as number of arguments is %0d and filename expected position number is %0d", argc, (i+1))
			}
			test_label_no = i+1;
			LOG_INFO(DEBUG,"[Main] Test Label argument number: %0d",  (test_label_no/2));
		}
	}

	LOG_INFO(LOW, "[Main] Input files:");
	if (test_set_no > 0) {
		strcpy(test_set, argv[test_set_no]);
		LOG_INFO(LOW,"[Main] \ttest set file: %s", test_set);
		inputfile_given = true;
	}
	if (train_set_no > 0) {
		strcpy(train_set, argv[train_set_no]);
		LOG_INFO(LOW,"[Main] \ttraining set file: %s",  train_set);
		inputfile_given = true;
	}
	if (test_label_no > 0) {
		strcpy(test_label, argv[test_label_no]);
		LOG_INFO(LOW,"[Main] \ttest label file: %s",  test_label);
		inputfile_given = true;
	}
	if (train_label_no > 0) {
		strcpy(train_label, argv[train_label_no]);
		LOG_INFO(LOW,"[Main] \ttraining label file: %s",  train_label);
		inputfile_given = true;
	}

	// If no input file is given
	ASSERT(inputfile_given == true);

	test_parse_idx(test_set, train_set, test_label, train_label);

	test_neural_network(test_set, train_set, test_label, train_label);

	free_memory(test_set);
	free_memory(train_set);
	free_memory(test_label);
	free_memory(train_label);

	LOG_INFO(ZERO,"[Main] Tests completed.");
	close_logfile();

	return EXIT_SUCCESS;

}
/** @} */ // End of addtogroup Main group
