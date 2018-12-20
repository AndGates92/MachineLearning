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
#include <math.h>
#include "log.h"
#include "parse_idx.h"
#include "graphics.h"
#include "neural_network.h"
#include "feedforward_stage.h"
#include "backward_propagation.h"
#include "utility.h"

void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t) {

	LOG_INFO(LOW,"[Parse All IDX Files] Start parsing all IDX files");

	parse_idx(test_set, test_set_struct_t);
	parse_idx(test_label, test_label_struct_t);
	parse_idx(train_set, train_set_struct_t);
	parse_idx(train_label, train_label_struct_t);

	LOG_INFO(LOW,"[Parse All IDX Files] End parsing all IDX files");

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

		create_elements_window(test_set_struct_t, test_label_struct_t);

		// Randomize the weight and the bias of every layer
		initialize_neuronetwork(&weights, &biases, &layers_dim, test_set_struct_t, test_label_struct_t, &learn_rate, &alpha);

		train_neural_network(weights, biases, layers_dim, train_set_struct_t, train_label_struct_t, learn_rate, alpha); 
	} else {
		LOG_INFO(LOW,"[Neural Network] Can't run neural network as input informations are not sufficient");
	}

	LOG_INFO(DEBUG,"[Neural Network] Freeing memory allocated for storing layer dimensionk.");
	free_memory(layers_dim);

	LOG_INFO(DEBUG,"[Neural Network] Freeing memory allocated for weights and biases of neural network.");
	free_memory(weights);
	free_memory(biases);

	LOG_INFO(DEBUG,"[Neural Network] Freeing memory allocated for data strctures data_t.");
	delete_data(test_set_struct_t);
	delete_data(test_label_struct_t);
	delete_data(train_set_struct_t);
	delete_data(train_label_struct_t);

}

void initialize_neuronetwork(double ** weights, double ** biases, int ** layers_dim, data_t * data_set, data_t * data_label, double * learn_rate, double * alpha) { 

	int input_layer_size = 0;
	input_layer_size = element_size(data_set);
	input_layer_size = 4;
	int output_layer_size = 0;
	output_layer_size = (int)get_max_element(data_label);
	output_layer_size = 2;

	int num_input_hidden_layers = 0;
	// Hidden layers plus input layer
	num_input_hidden_layers = (NUM_HIDDEN_LAYERS + 1);

	int total_num_layers = 0;
	// Hidden layers plus input layer plus output layer
	total_num_layers = (num_input_hidden_layers + 1);

	(*layers_dim) = (int *) malloc(total_num_layers*sizeof(int));
	if ((*layers_dim)==NULL) {
		LOG_ERROR("Can't allocate memory for the array of dimensions of each layer of the neural network");
	}

	int total_num_weights = 0;
	total_num_weights = 0;
	double prev_layer_dim = 0;
	// Randomize weights between MIN_WEIGTH and MAX_WEIGHT
	for (int idx_layer = 0; idx_layer < total_num_layers; idx_layer++) {
		double weight_dim = 0.0;
		weight_dim = ((double)((total_num_layers - 1) - idx_layer))/((double)(total_num_layers - 1));

		double absolute_dim = 0.0;
		absolute_dim = ((double)input_layer_size-(double)output_layer_size) * weight_dim;

		int layer_dim = 0;
		// Constantly move from the size of the input layer to that of the output layer
		layer_dim = (int)(absolute_dim + output_layer_size);
		(*((*layers_dim) + idx_layer)) = layer_dim;
		LOG_INFO(MEDIUM, "[Initialize Neural Network] Randomizing layer dimensions: Layer[%0d]: %0d", idx_layer, (*((*layers_dim) + idx_layer)));
		if (input_layer_size > output_layer_size) {
			ASSERT((layer_dim <= input_layer_size) && (layer_dim >= (output_layer_size)));
		} else {
			ASSERT((layer_dim >= input_layer_size) && (layer_dim <= (output_layer_size)));
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
		double variance = 0.0;
		variance = pow((double)WEIGHT_STD_DEV,2);
		double max_size = 0.0;
		if (input_layer_size > output_layer_size) {
			max_size = (double)input_layer_size;
		} else {
			max_size = (double)output_layer_size;
		}
		double weight = 0;
		weight = (1.0/sqrt(2.0*M_PI*variance))*(exp((pow((((double)rand()/RAND_MAX) - (double)WEIGHT_MEAN),2))/(2.0*(variance))));
		weight /= max_size;
		(*((*weights) + idx_el)) = weight;
		LOG_INFO(MEDIUM, "[Initialize Neural Network] Randomizing weights: Weight[%0d]: %0f (expected %0f)", idx_el, (*((*weights) + idx_el)), weight);
	}

	// Randomize biases between MIN_BIASES and MAX_BIASES
	(*biases) = (double *) malloc(num_input_hidden_layers*sizeof(double));
	if ((*biases)==NULL) {
		LOG_ERROR("Can't allocate memory for biases of the neural network");
	}

	for (int idx_bias = 0; idx_bias < num_input_hidden_layers; idx_bias++) {
		double bias = 0;
		bias = (((double)rand()/RAND_MAX) * (double)(MAX_BIAS - MIN_BIAS)) + (double)MIN_BIAS;
		(*((*biases) + idx_bias)) = bias;
		LOG_INFO(MEDIUM, "[Initialize Neural Network] Randomizing bias: Bias[%0d]: %0f (expected %0f)", idx_bias, (*((*biases) + idx_bias)), bias);
		ASSERT(bias >= MIN_BIAS);
		ASSERT(bias <= MAX_BIAS);
	}

	*learn_rate = (((double)rand()/RAND_MAX) * (double)(MAX_LEARN_RATE - MIN_LEARN_RATE)) + (double)MIN_LEARN_RATE;
	LOG_INFO(MEDIUM, "[Initialize Neural Network] Randomizing learning rate: %0f", *learn_rate);
	ASSERT(*learn_rate >= MIN_LEARN_RATE);
	ASSERT(*learn_rate <= MAX_LEARN_RATE);

	*alpha = (((double)rand()/RAND_MAX) * (double)(MAX_ALPHA - MIN_ALPHA)) + (double)MIN_ALPHA;
	LOG_INFO(MEDIUM, "[Initialize Neural Network] Randomizing alpha: %0f", *alpha);
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

//	for (int start_el_idx = 0; start_el_idx < num_el; start_el_idx++) {
	for (int start_el_idx = 0; start_el_idx < 3; start_el_idx++) {

		int no_dims = 0;
		no_dims = get_no_dims(data_set);

		int * set_coord = NULL;
		set_coord = (int *) malloc(no_dims*sizeof(int));
		if (set_coord==NULL) {
			LOG_ERROR("Can't allocate memory for data set element coordinate");
		}

		for (int set_dim = 0; set_dim < no_dims; set_dim++) {
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
			LOG_INFO(HIGH, "[Neural network training] Start data set coordinate %0d out of %0d: %0d", set_dim, no_dims, set_coord[set_dim]);
		}

		elementdatatype_t * input_data = NULL;
		input_data = get_elements_subset(data_set, el_size, set_coord);

		free_memory(set_coord);

		double * input_data_double = NULL;
		input_data_double = cast_array_to_double (input_data, el_size);

		free_memory(input_data);

		elementdatatype_t max_el = 0;
		max_el =  get_max_element (data_set);

		double * input_data_double_norm = NULL;
		input_data_double_norm = normalize_elements (input_data_double, max_el, el_size);

		free_memory(input_data_double);

		int label_no_dims = 0;
		label_no_dims = get_no_dims(data_label);
		int * label_coord = NULL;
		label_coord = (int *) malloc(label_no_dims*sizeof(int));
		if (label_coord==NULL) {
			LOG_ERROR("Can't allocate memory for label element coordinate");
		}

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
			LOG_INFO(HIGH, "[Neural network training] Start label coordinate %0d: %0d", lab_dim, label_coord[lab_dim]);
		}

		elementdatatype_t label = 0;
		label = get_element(data_label, label_coord);

		// Cast label to integer
		int label_int = 0;
		label_int = (int) label;

		free_memory(label_coord);

		int outcome = 0;

		LOG_INFO(LOW, "[Neural network training] Feedforward stage: Start iteration %0d out of %0d", start_el_idx, num_el);
		feedforward_stage(weights, biases, layers_dim, input_data_double_norm, &node_val, &outcome);

		free_memory(input_data_double_norm);

		LOG_INFO(LOW,"[Neural network training] Neural network estimates: %0d Label %0d", outcome, label_int);
		if (outcome == label_int) {
			LOG_INFO(LOW,"[Neural network training] PASS: label matches neural network prediction");
		} else {
			LOG_INFO(LOW,"[Neural network training] FAIL: label doesn't match neural network prediction");
		}

		LOG_INFO(LOW, "[Neural network training] Backward propagation stage: Start iteration %0d out of %0d", start_el_idx, num_el);
		backward_propagation(&weights, biases, layers_dim, node_val, label_int, learn_rate, alpha);

	}

	free_memory(node_val);

}

void create_elements_window(data_t * data_set, data_t * data_label) {
	int no_dims = 0;
	no_dims = get_no_dims(data_set);

	int num_el = 0;
	if (no_dims > 1) {
		num_el = get_dimension(data_set, 0);
	} else {
		LOG_ERROR("Can't get number of elements in elements array as number of dimensions is set to 0");
	}

	int img_width = 0;
	if (no_dims > 1) {
		img_width = get_dimension(data_set, 1);
	} else {
		LOG_ERROR("Can't get image width as number of dimensions is 1");
	}

	int img_height = 0;
	if (no_dims > 2) {
		img_height = get_dimension(data_set, 2);
	} else {
		LOG_ERROR("Can't get image width as number of dimensions less than or equal to 2");
	}

	elementdatatype_t * pixels = NULL;
	pixels = get_data_elements(data_set);

	int no_pixels = 0;
	no_pixels = compute_total_no_elements(data_set);

	double * pixels_double = NULL;
	pixels_double = cast_array_to_double(pixels, no_pixels);

	free_memory(pixels);

	elementdatatype_t * labels = NULL;
	labels = get_data_elements(data_label);

	int no_labels = 0;
	no_labels = compute_total_no_elements(data_label);

	int * labels_int = NULL;
	labels_int = cast_array_to_int(labels, no_labels);

	create_window(num_el, img_width, img_height, pixels_double, labels_int, DATASET);

}
