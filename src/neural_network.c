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
#include "utility.h"

void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t) {

	LOG_INFO(LOW,"Start parsing all IDX files\n");

	parse_idx(test_set, test_set_struct_t);
	parse_idx(test_label, test_label_struct_t);
	parse_idx(train_set, train_set_struct_t);
	parse_idx(train_label, train_label_struct_t);

	LOG_INFO(LOW,"End parsing all IDX files\n");

}

void neural_network (char * test_set, char * train_set, char * test_label, char * train_label) {

	// Declare data structures
	data_t * test_set_struct_t = NULL;
	data_t * test_label_struct_t = NULL;
	data_t * train_set_struct_t = NULL;
	data_t * train_label_struct_t = NULL;

	// Array of weights of the neural network
	elementdatatype_t * weights;
	elementdatatype_t * biases;

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set_struct_t, &test_label_struct_t, &train_set_struct_t, &train_label_struct_t);

	if (test_set_struct_t != NULL) {
		// Randomize the weight and the bias of every layer
		initialize_neuronetwork(&weights, &biases, test_set_struct_t);

//		feedfoward_propagation();

//		backwards_propagation();
	} else {
		LOG_INFO(LOW,"Can't run neural network as input informations are not sufficient\n");
	}

	LOG_INFO(DEBUG,"Freeing memory allocated for weights and biases of neural network.\n");
	free_memory(weights);
	free_memory(biases);

	LOG_INFO(DEBUG,"Freeing memory allocated for data strctures data_t.\n");
	delete_data(test_set_struct_t);
	delete_data(test_label_struct_t);
	delete_data(train_set_struct_t);
	delete_data(train_label_struct_t);

}

void initialize_neuronetwork(elementdatatype_t ** weights, elementdatatype_t ** biases, data_t * set) { 

	int no_dims = 0;
	int * dimensions = NULL;

	no_dims = get_no_dims(set);
	ASSERT(no_dims > 0);
	dimensions = get_dimensions(set);

	int elements_in_unit = 0;

	for (int dim = 0; dim < no_dims; dim++) {
		switch (dim) {
			case 0:
				// Number of sets of data
				elements_in_unit = 1;
				break;
			case 1:
				// Elements in each set of data
				elements_in_unit *= dimensions[dim];
				break;
			case 2:
				// Elements in each set of data (2nd dimension)
				elements_in_unit *= dimensions[dim];
				break;
			default:
				LOG_ERROR("Not supported more than 3 dimensions.\n Failure");
				break;
		}
	}

	free_memory(dimensions);

	int num_layers_p1 = 0;
	int total_num_weights = 0;

	// Hidden layers plus input layer
	num_layers_p1 = (NO_HIDDEN_LAYERS + 1);

	total_num_weights = num_layers_p1*elements_in_unit;

	(*weights) = (elementdatatype_t *) malloc(total_num_weights*sizeof(elementdatatype_t));

	for (int idx_el = 0; idx_el < total_num_weights; idx_el++) {
		elementdatatype_t weight = 0;
		weight = ((rand()/RAND_MAX) * (MAX_WEIGHT - MIN_WEIGHT)) + MIN_WEIGHT;
		(*((*weights) + idx_el)) = weight;
		LOG_INFO(HIGH, "Randomizing weights: Weight[%0d]: %0d\n", idx_el, (*((*weights) + idx_el)));
		ASSERT(weight >= MIN_WEIGHT);
		ASSERT(weight <= MAX_WEIGHT);
	}

	(*biases) = (elementdatatype_t *) malloc(num_layers_p1*sizeof(elementdatatype_t));
	for (int idx_bias = 0; idx_bias < num_layers_p1; idx_bias++) {
		elementdatatype_t bias = 0;
		bias = ((rand()/RAND_MAX) * (MAX_BIAS - MIN_BIAS)) + MIN_BIAS;
		(*((*biases) + idx_bias)) = bias;
		LOG_INFO(HIGH, "Randomizing bias: Bias[%0d]: %0d\n", idx_bias, (*((*biases) + idx_bias)));
		ASSERT(bias >= MIN_BIAS);
		ASSERT(bias <= MAX_BIAS);
	}

}
