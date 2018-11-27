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
#include "feedforward_stage.h"
#include "backward_propagation.h"
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
	double learn_rate = 0;
	double alpha = 0;

	// Layer dimensions
	int * layers_dim = NULL;

	parse_all_idx (test_set, train_set, test_label, train_label, &test_set_struct_t, &test_label_struct_t, &train_set_struct_t, &train_label_struct_t);

	if ((test_set_struct_t != NULL) && (test_label_struct_t != NULL) && (train_set_struct_t != NULL) && (train_label_struct_t != NULL)) {
		// Randomize the weight and the bias of every layer
		initialize_neuronetwork(&weights, &biases, &layers_dim, test_set_struct_t, test_label_struct_t, &learn_rate, &alpha);

		train_neural_network(weights, biases, layers_dim, train_set_struct_t, train_label_struct_t, learn_rate, alpha); 
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

void initialize_neuronetwork(double ** weights, double ** biases, int ** layers_dim, data_t * data_set, data_t * data_label, double * learn_rate, double * alpha) { 
	int input_layer_size = 0;
	int output_layer_size = 0;
	int num_input_hidden_layers = 0;
	int total_num_layers = 0;

	input_layer_size = element_size(data_set);
	output_layer_size = get_max_element(data_label);

	// Hidden layers plus input layer
	num_input_hidden_layers = (NUM_HIDDEN_LAYERS + 1);

	// Hidden layers plus input layer plus output layer
	total_num_layers = (num_input_hidden_layers + 1);

	(*layers_dim) = (int *) malloc(total_num_layers*sizeof(int));
	if ((*layers_dim)==NULL) {
		LOG_ERROR("Can't allocate memory for the array of dimensions of each layer of the neural network");
	}

	int total_num_weights = 0;
	total_num_weights = 0;
	// Randomize weights between MIN_WEIDTH and MAX_WEIGHT
	for (int idx_layer = 0; idx_layer < total_num_layers; idx_layer++) {
		double layer_dim = 0;
		double prev_layer_dim = 0;
		// Constantly move from the size of the input layer to that of the output layer
		layer_dim = (((input_layer_size-output_layer_size) * (total_num_layers - idx_layer))/total_num_layers) + output_layer_size;
		(*((*layers_dim) + idx_layer)) = layer_dim;
		LOG_INFO(HIGH, "Randomizing layer dimensions: Layer[%0d]: %0d\n", idx_layer, (*((*layers_dim) + idx_layer)));
		if (input_layer_size > output_layer_size) {
			ASSERT((layer_dim <= (input_layer_size + 1)) && (layer_dim >= (output_layer_size)));
		} else {
			ASSERT((layer_dim >= (input_layer_size + 1)) && (layer_dim <= (output_layer_size)));
		}
		ASSERT(layer_dim > 0);

		// Weights are between input layer and the first hidden layer and between 2 consecutive hidden layers 
		if (idx_layer > 0) {
			// elements in unit contains the number of weights required for the neural network training set but it doesn't account for the bias, hence add 1
			// Weights are between every node of a layer to each node of the next layer
			total_num_weights += layer_dim*(prev_layer_dim + 1);
		}

		prev_layer_dim = layer_dim;

	}

	(*weights) = (double *) malloc(total_num_weights*sizeof(double));
	if ((*weights)==NULL) {
		LOG_ERROR("Can't allocate memory for weights of the neural network");
	}

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
	if ((*biases)==NULL) {
		LOG_ERROR("Can't allocate memory for biases of the neural network");
	}

	for (int idx_bias = 0; idx_bias < num_input_hidden_layers; idx_bias++) {
		double bias = 0;
		bias = ((rand()/RAND_MAX) * (MAX_BIAS - MIN_BIAS)) + MIN_BIAS;
		(*((*biases) + idx_bias)) = bias;
		LOG_INFO(HIGH, "Randomizing bias: Bias[%0d]: %0d\n", idx_bias, (*((*biases) + idx_bias)));
		ASSERT(bias >= MIN_BIAS);
		ASSERT(bias <= MAX_BIAS);
	}

	*learn_rate = ((rand()/RAND_MAX) * (MAX_LEARN_RATE - MIN_LEARN_RATE)) + MIN_LEARN_RATE;
	LOG_INFO(HIGH, "Randomizing learning rate: %0d\n", learn_rate);
	ASSERT(*learn_rate >= MIN_LEARN_RATE);
	ASSERT(*learn_rate <= MAX_LEARN_RATE);

	*alpha = ((rand()/RAND_MAX) * (MAX_ALPHA - MIN_ALPHA)) + MIN_ALPHA;
	LOG_INFO(HIGH, "Randomizing alpha: %0d\n", alpha);
	ASSERT(*alpha >= MIN_ALPHA);
	ASSERT(*alpha <= MAX_ALPHA);
}

void train_neural_network(double * weights, double * biases, int * layers_dim, data_t * data_set, data_t * data_label, double learn_rate, double alpha) {

	int el_size = 0;
	el_size = element_size(data_set);

	int num_el = 0;
	num_el = get_dimension(data_set, 0);

	int total_num_layers = 0;
	// Hidden layers plus input layer plus output layer
	total_num_layers = (NUM_HIDDEN_LAYERS + 2);

	int total_num_nodes = 0;

	for (int layer_no = 0; layer_no < total_num_layers; layer_no++) {
		total_num_nodes += (*(layers_dim + layer_no));
	}

	double * node_val = NULL;
	node_val = (double *) malloc(total_num_nodes*sizeof(double));

	int total_el = 0;
	total_el = compute_total_no_elements(data_set);

	for (int start_el_idx = 0; start_el_idx < num_el; start_el_idx++) {
		// Assert that remain an integer number of elements
		ASSERT(((total_el - start_el_idx) % el_size) == 0);

		int set_no_dims = 0;
		set_no_dims = get_no_dims(data_set);
		int * set_coord = NULL;
		set_coord = (int *) malloc(set_no_dims*sizeof(int));

		for (int set_dim = 0; set_dim < set_no_dims; set_dim++) {
			int coordinate = 0;
			switch (set_dim) {
				case 0:
					coordinate = start_el_idx;
					break;
				default:
					coordinate = 0;
					break;
			}
			set_coord[set_dim] = coordinate;
			LOG_INFO(LOW, "Start label coordinate %0d: %0d\n", set_dim, set_coord[set_dim]);
		}

		elementdatatype_t * input_data = NULL;
		input_data = get_elements_subset(data_set, el_size, set_coord);

		int label_no_dims = 0;
		label_no_dims = get_no_dims(data_label);
		int * label_coord = NULL;
		label_coord = (int *) malloc(label_no_dims*sizeof(int));

		for (int lab_dim = 0; lab_dim < label_no_dims; lab_dim++) {
			int coordinate = 0;
			switch (lab_dim) {
				case 0:
					coordinate = start_el_idx;
					break;
				default:
					coordinate = 0;
					break;
			}
			label_coord[lab_dim] = coordinate;
			LOG_INFO(LOW, "Start label coordinate %0d: %0d\n", lab_dim, label_coord[lab_dim]);
		}

		elementdatatype_t label = 0;
		label = get_element(data_label, label_coord);
		LOG_INFO(LOW, "Label %0lf\n", (double)label);

		LOG_INFO(LOW, "Feedforward stage: Start iteration %0d out of %0d\n", start_el_idx, num_el);
		feedforward_stage(weights, biases, layers_dim, input_data, &node_val);

		LOG_INFO(LOW, "Backward propagation stage: Start iteration %0d out of %0d\n", start_el_idx, num_el);
		backward_propagation(&weights, biases, layers_dim, node_val, label, learn_rate, alpha);

		free_memory(input_data);
	}


	free_memory(node_val);

}
