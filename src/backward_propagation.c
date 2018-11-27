/**
 * @copyright
 * @file backward_propagation.c
 * @author Andrea Gianarda
 * @date 19th of November 2018
 * @brief Functions related to the backward propagation of the neural network
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "neural_network.h"
#include "neuron.h"
#include "backward_propagation.h"
#include "utility.h"

void backward_propagation (double ** weights, double * biases, int * layers_dim, double * node_val, double label, double learn_rate, double alpha) {

	int total_num_layers = 0;
	// Hidden layers plus input layer plus output layer
	total_num_layers = (NUM_HIDDEN_LAYERS + 2);

	// base node used as reference to access data.
	int base_node = 0;

	for (int layer_no = 0; layer_no < total_num_layers; layer_no++) {
		base_node += (*(layers_dim + layer_no));
	}

	// base weight used as reference to access weights.
	int base_weight = 0;

	for (int layer_no = 0; layer_no < (total_num_layers - 1); layer_no++) {
		base_weight += ((*(layers_dim + layer_no)) * (*(layers_dim + layer_no + 1)));
	}

	double * phi_arr = NULL;

	for (int layer_no = (total_num_layers - 1); layer_no > 0; layer_no--) {

		int num_neurons = 0;
		num_neurons = (*(layers_dim + layer_no));
		LOG_INFO(LOW, "Neighbour layer dimensions: Current Layer %0d -> Dimension %0d", layer_no, num_neurons);

		int num_neurons_prev = 0;
		num_neurons_prev = (*(layers_dim + layer_no - 1));
		LOG_INFO(LOW, "Neighbour layer dimensions: Previous Layer %0d -> Dimension %0d", (layer_no-1), num_neurons_prev);

		int phi_arr_dim = 0;
		phi_arr_dim = num_neurons_prev * num_neurons;

		int num_neurons_nxt = 0;

		int phi_arr_prev_dim = 0;

		double * phi_arr_prev = NULL;

		if (layer_no < (total_num_layers - 1)) {
			num_neurons_nxt = (*(layers_dim + layer_no + 1));
			LOG_INFO(LOW, "Neighbour layer dimensions: Next Layer %0d -> Dimension %0d", (layer_no+1), num_neurons_nxt);

			phi_arr_prev_dim = num_neurons_nxt * num_neurons;

			phi_arr_prev = (double *) malloc(phi_arr_prev_dim*sizeof(double));
			if (phi_arr_prev==NULL) {
				LOG_ERROR("Can't allocate memory for array storing values of phi collected in the previous iteration");
			}

			memcpy(phi_arr_prev, phi_arr, (phi_arr_prev_dim*sizeof(double)));
		}

		free_memory(phi_arr);

		phi_arr = (double *) malloc(phi_arr_dim*sizeof(double));
		if (phi_arr==NULL) {
			LOG_ERROR("Can't allocate memory for array storing values of phi collected in the current iteration");
		}

		for (int neuron_idx = 0; neuron_idx < num_neurons; neuron_idx++) {

			double node_val_start = 0.0;
			node_val_start = *(node_val + (base_node - neuron_idx - 1));

			double sigmoid_node_start = 0.0;
			sigmoid_node_start = sigmoid(node_val_start);

			double sigmoid_der_node_start = 0.0;
			sigmoid_der_node_start = sigmoid_der(node_val_start);

			for (int neuron_prev_idx = 0; neuron_prev_idx <=num_neurons_prev; neuron_prev_idx++) {

				double node_val_end = 0.0;
				double sigmoid_node_end = 0.0;

				int curr_weight_offset = 0;

				if (neuron_prev_idx == 0) {
					// Adjust weight of bias
					node_val_end = *(biases + layer_no);
					sigmoid_node_end = node_val_end;

					// Weight pointer points at the first weight if the next layer, therefore we need to compute the the offset to access the weight of interest
					// Add 1 to account for the bias
					curr_weight_offset = (num_neurons_prev*num_neurons + 1);
				} else {
					node_val_end = *(node_val + (base_node - num_neurons - neuron_prev_idx - 1));
					sigmoid_node_end = sigmoid(node_val_end);
					// Weight pointer points at the first weight if the next layer, therefore we need to compute the the offset to access the weight of interest
					// No correction for bias at it has been processed at loop variable equal 0
					curr_weight_offset = (num_neurons_prev*num_neurons) - neuron_prev_idx*num_neurons - neuron_idx;
				}

				ASSERT(curr_weight_offset >= 0);

				double phi = 0.0;

				if (layer_no == (total_num_layers - 1)) {

					double exp_val = 0.0;
					exp_val = (double)(neuron_idx == label);

					// output layer
					phi = sigmoid_der_node_start * (exp_val - sigmoid_node_start); 

				} else {

					double sum_phi_weight = 0.0;

					for (int neuron_nxt_idx = 0; neuron_nxt_idx < num_neurons_nxt; neuron_nxt_idx++) {

						int offset = 0;
						// compute offset with respect to 1st weight/phi of the current layer
						offset = ((neuron_idx * num_neurons_nxt) + neuron_nxt_idx);
						ASSERT(offset >= 0);

						double weight_el = 0.0;
						weight_el = *(*weights + (base_weight + offset - 1));

						double phi_el = 0.0;
						phi_el = *(phi_arr_prev + (offset - 1));

						sum_phi_weight += (weight_el * phi_el);

						LOG_INFO(DEBUG, "Backpropoagation stage: [Hidden layer of Input layer] Weight (base %0d offset %0d): %0d\n", base_weight, offset, weight_el);
						LOG_INFO(DEBUG, "Backpropoagation stage: [Hidden layer of Input layer] phi (offset %0d): %0d\n", offset, phi_el);

					}

					phi = sigmoid_der_node_start * sum_phi_weight; 

				}

				double curr_weight = 0.0;
				// Add 1 to compensate start from 0
				curr_weight = *(*weights + ((base_weight + 1) - curr_weight_offset));

				double delta_weight = 0.0;
				delta_weight = learn_rate * (phi * sigmoid_node_end + alpha * curr_weight);
				LOG_INFO(DEBUG, "Backpropoagation stage: [Weight update] phi = %0d learning rate = %0d delta weight %0d\n", phi, learn_rate, delta_weight);

				*(*weights + ((base_weight + 1) - curr_weight_offset)) += delta_weight;
				LOG_INFO(HIGH, "Backpropoagation stage: [Weight update] Old value %0d Delta = %0d New value = %0d\n", curr_weight, delta_weight, *(*weights + ((base_weight + 1) - curr_weight_offset)));

			}

		}

		// Value used in the next iteration.
		// Take out the number of weight between the previous layer (that will be current layer in the next iteration) and those in the current layer (next layer during next iteration).
		base_weight -= (num_neurons_prev * num_neurons);
		ASSERT(base_weight >= 0);

		free_memory(phi_arr_prev);

		base_node =- num_neurons;

		ASSERT(base_node >= num_neurons_prev);

	}

	free_memory(phi_arr);

	// base_node here is expected to be equal to the number of node of the input layer
	ASSERT(base_node == *layers_dim);

	// base_weight here is expected to be 0 because the input layer has been reached
	ASSERT(base_weight == 0);
}
