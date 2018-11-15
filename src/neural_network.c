/**
 * @copyright
 * @file neural_network.c
 * @author Andrea Gianarda
 * @date 12th of November 2018
 * @brief Top level functions of neural network
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
	double * weights = NULL;
	double * biases = NULL;

	// Layer dimensions
	int * layers_dim = NULL;

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set_struct_t, &test_label_struct_t, &train_set_struct_t, &train_label_struct_t);

	if ((test_set_struct_t != NULL) && (test_label_struct_t != NULL) && (train_set_struct_t != NULL) && (train_label_struct_t != NULL)) {
		// Randomize the weight and the bias of every layer
		initialize_neuronetwork(&weights, &biases, &layers_dim, test_set_struct_t, test_label_struct_t);

//		feedfoward_stage();

//		backwards_propagation();
	} else {
		LOG_INFO(LOW,"Can't run neural network as input informations are not sufficient\n");
	}

	LOG_INFO(DEBUG,"Freeing memory allocated for storing layer dimensionk.\n");
	free_memory(layers_dim);

	LOG_INFO(DEBUG,"Freeing memory allocated for weights and biases of neural network.\n");
	free_memory(weights);
	free_memory(biases);

	LOG_INFO(DEBUG,"Freeing memory allocated for data strctures data_t.\n");
	delete_data(test_set_struct_t);
	delete_data(test_label_struct_t);
	delete_data(train_set_struct_t);
	delete_data(train_label_struct_t);

}

void initialize_neuronetwork(double ** weights, double ** biases, int ** layers_dim, data_t * data_set, data_t * data_label) { 
	int input_layer_size = 0;
	int output_layer_size = 0;
	int num_input_hidden_layers = 0;
	int total_num_weights = 0;
	int total_num_layers = 0;

	input_layer_size = element_size(data_set);
	output_layer_size = element_size(data_label);

	// Hidden layers plus input layer
	num_input_hidden_layers = (NO_HIDDEN_LAYERS + 1);

	// Hidden layers plus input layer plus output layer
	total_num_layers = (num_input_hidden_layers + 1);

	// elements in unit contains the number of weights required for the neural network training set but it doesn't account for the bias, hence add 1 
	total_num_weights = num_input_hidden_layers*(input_layer_size + 1);

	(*layers_dim) = (int *) malloc(total_num_layers*sizeof(int));

	// Randomize weights between MIN_WEIDTH and MAX_WEIGHT
	for (int idx_layer = 0; idx_layer < total_num_layers; idx_layer++) {
		double layer_dim = 0;
		// Constantly move from the size of the input layer to that of the output layer
		layer_dim = (((input_layer_size-output_layer_size) * (total_num_layers - idx_layer))/total_num_layers) + output_layer_size;
		(*((*layers_dim) + idx_layer)) = layer_dim;
		LOG_INFO(HIGH, "Randomizing layer dimensions: Layer[%0d]: %0d\n", idx_layer, (*((*layers_dim) + idx_layer)));
		ASSERT(layer_dim <= (input_layer_size + 1));
		ASSERT(layer_dim > 0);
	}

	(*weights) = (double *) malloc(total_num_weights*sizeof(double));

	// Randomize weights between MIN_WEIDTH and MAX_WEIGHT
	for (int idx_el = 0; idx_el < total_num_weights; idx_el++) {
		double weight = 0;
		weight = ((rand()/RAND_MAX) * (MAX_WEIGHT - MIN_WEIGHT)) + MIN_WEIGHT;
		(*((*weights) + idx_el)) = weight;
		LOG_INFO(HIGH, "Randomizing weights: Weight[%0d]: %0d\n", idx_el, (*((*weights) + idx_el)));
		ASSERT(weight >= MIN_WEIGHT);
		ASSERT(weight <= MAX_WEIGHT);
	}

	// Randomize biases between MIN_BIASES and MAX_BIASES
	(*biases) = (double *) malloc(num_input_hidden_layers*sizeof(double));
	for (int idx_bias = 0; idx_bias < num_input_hidden_layers; idx_bias++) {
		double bias = 0;
		bias = ((rand()/RAND_MAX) * (MAX_BIAS - MIN_BIAS)) + MIN_BIAS;
		(*((*biases) + idx_bias)) = bias;
		LOG_INFO(HIGH, "Randomizing bias: Bias[%0d]: %0d\n", idx_bias, (*((*biases) + idx_bias)));
		ASSERT(bias >= MIN_BIAS);
		ASSERT(bias <= MAX_BIAS);
	}

}
