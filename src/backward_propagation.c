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

void backward_propagation (double ** weights, double * biases, int * layers_dim, double * node_val, int label, double learn_rate, double alpha) {

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
		int curr_layer_dim = 0;
		curr_layer_dim = (*(layers_dim + layer_no));
		int nxt_layer_dim = 0;
		nxt_layer_dim = (*(layers_dim + layer_no + 1));
		base_weight += ((curr_layer_dim + 1) * (nxt_layer_dim));
	}

	double * phi_arr_prev = NULL;

	for (int layer_no = (total_num_layers - 1); layer_no > 0; layer_no--) {

		int num_neurons = 0;
		num_neurons = (*(layers_dim + layer_no));
		LOG_INFO(DEBUG, "[Backpropoagation stage] [Neighbour layer dimensions] Current Layer %0d -> Dimension %0d", layer_no, num_neurons);

		int num_neurons_prev = 0;
		// Add 1 for the bias
		num_neurons_prev = (*(layers_dim + layer_no - 1)) + 1;
		LOG_INFO(DEBUG, "[Backpropoagation stage] [Neighbour layer dimensions] Previous Layer %0d -> Dimension %0d", (layer_no-1), num_neurons_prev);

		int phi_arr_dim = 0;
		phi_arr_dim = num_neurons;

		double * phi_arr = NULL;

		phi_arr = (double *) malloc(phi_arr_dim*sizeof(double));
		if (phi_arr==NULL) {
			LOG_ERROR("Can't allocate memory for array storing values of phi collected in the current iteration");
		}

		for (int neuron_idx = 0; neuron_idx < num_neurons; neuron_idx++) {

			int curr_node_offset = 0;
			// base_node points to the first element of the next layer
			curr_node_offset = (num_neurons - neuron_idx);
			LOG_INFO(DEBUG, "[Backpropoagation stage] [Nodes] base node %0d Neurons: current %0d out of %0d -> Current node offset: %0d", base_node, neuron_idx, num_neurons, curr_node_offset);
			ASSERT(curr_node_offset > 0);

			int node_start_offset = 0;
			node_start_offset = (base_node - curr_node_offset);
			ASSERT(node_start_offset >= 0);

			double node_val_start = 0.0;
			node_val_start = *(node_val + node_start_offset);

			double sigmoid_node_start = 0.0;
			sigmoid_node_start = sigmoid(node_val_start);

			double sigmoid_der_node_start = 0.0;
			sigmoid_der_node_start = sigmoid_der(node_val_start);
			LOG_INFO(MEDIUM, "[Backpropoagation stage] [Backpropoagation stage] [Node start %0d] value %0f sigmoid %0f derivative %0f", node_start_offset, node_val_start, sigmoid_node_start, sigmoid_der_node_start);

			double sum_phi_weight = 0.0;

			if (layer_no == (total_num_layers - 1)) {

				double exp_val = 0.0;
				if (neuron_idx == label) {
					exp_val = 1.0;
				} else {
					exp_val = 0.0;
				}

				// output layer
				sum_phi_weight = (exp_val - sigmoid_node_start);

			} else {

				int num_neurons_nxt = 0;

				num_neurons_nxt = (*(layers_dim + layer_no + 1));
				LOG_INFO(DEBUG, "[Backpropoagation stage] [Neighbour layer dimensions] Next Layer %0d -> Dimension %0d", (layer_no+1), num_neurons_nxt);

				for (int neuron_nxt_idx = 0; neuron_nxt_idx < num_neurons_nxt; neuron_nxt_idx++) {

					int offset = 0;
					// compute offset with respect to 1st weight/phi of the current layer
					offset = ((neuron_nxt_idx * (num_neurons + 1)) + neuron_idx + 1);
					ASSERT(offset >= 0);

					int total_weight_offset = 0;
					total_weight_offset = (base_weight + offset);
					ASSERT(total_weight_offset >= 0);

					double weight_el = 0.0;
					weight_el = *(*weights + total_weight_offset);

					double phi_el = 0.0;
					phi_el = *(phi_arr_prev + neuron_nxt_idx);

					sum_phi_weight += (weight_el * phi_el);

					LOG_INFO(HIGH, "[Backpropoagation stage] [Hidden layer or Input layer] Weight (base %0d offset %0d: index %0d): %0f", base_weight, offset, total_weight_offset, weight_el);
					LOG_INFO(HIGH, "[Backpropoagation stage] [Hidden layer or Input layer] phi (offset %0d): %0f", neuron_nxt_idx, phi_el);
					LOG_INFO(HIGH, "[Backpropoagation stage] [Hidden layer or Input layer] sum_phi_weight: %0f", sum_phi_weight);

				}

			}

			double phi = 0.0;
			phi = sigmoid_der_node_start * sum_phi_weight;
			LOG_INFO(HIGH, "[Backpropoagation stage] [phi layer %0d Neuron %0d] phi %0f (sigmoid_der_node_start %0f sum_phi_weight %0f)", layer_no, neuron_idx, phi, sigmoid_der_node_start, sum_phi_weight);

			*(phi_arr + neuron_idx) = phi;

			for (int neuron_prev_idx = 0; neuron_prev_idx < num_neurons_prev; neuron_prev_idx++) {

				double node_val_end = 0.0;
				double sigmoid_node_end = 0.0;

				if (neuron_prev_idx == 0) {
					// Adjust weight of bias
					// Select bias of the previous layer
					node_val_end = *(biases + layer_no - 1);
					sigmoid_node_end = node_val_end;
					LOG_INFO(MEDIUM, "[Backpropoagation stage] [Bias %0d] value %0f sigmoid %0f", (layer_no - 1), node_val_end, sigmoid_node_end);
				} else {

					int prev_node_offset = 0;
					// No need to take out 1 as:
					// num_neurons_prev: the total number of neurons in the previous layer (num_neurons_prev) accounts lso for the bias
					// neuron_prev_idx: the actual index of the node of interest is (neuron_prev_idx - 1) because the 1st node is the bias
					prev_node_offset = (num_neurons_prev - neuron_prev_idx);
					ASSERT(prev_node_offset >= 0);
					int total_prev_node_offset = 0;
					total_prev_node_offset = (num_neurons + prev_node_offset);
					ASSERT(total_prev_node_offset >= 0);

					int node_end_offset = 0;
					// Take out 1 to curr_weight_offset to account that index starts at 0
					node_end_offset = (base_node -  total_prev_node_offset);
					ASSERT(node_end_offset >= 0);

					// base_node points to the first element of the next layer
					// need to take out the number of neurons present on the current layer
					node_val_end = *(node_val + node_end_offset);
					LOG_INFO(DEBUG, "[Backpropoagation stage] [Nodes] base node %0d Neurons: total number current layer %0d, previous layer index %0d out of %0d -> Previous node offset: %0d", base_node, num_neurons, neuron_prev_idx, num_neurons_prev, total_prev_node_offset);
					sigmoid_node_end = sigmoid(node_val_end);
					LOG_INFO(MEDIUM, "[Backpropoagation stage] [Node end %0d] value %0f sigmoid %0f", node_end_offset, node_val_end, sigmoid_node_end);
				}

				int curr_weight_offset = 0;
				// Weight pointer points at the first weight if the next layer, therefore we need to compute the the offset to access the weight of interest
				// No correction for bias at it has been processed at loop variable equal 0
				curr_weight_offset = (num_neurons_prev*num_neurons) - neuron_idx*num_neurons_prev - neuron_prev_idx;
				ASSERT(curr_weight_offset > 0);

				int weight_offset = 0;
				weight_offset = (base_weight - curr_weight_offset);
				ASSERT(weight_offset >= 0);

				LOG_INFO(DEBUG, "[Backpropoagation stage] [Weights] base weight %0d Neurons: current %0d out of %0d, previous %0d out of %0d -> Weight offset: %0d", base_weight, neuron_idx, num_neurons, neuron_prev_idx, num_neurons_prev, weight_offset);

				double curr_weight = 0.0;
				curr_weight = *(*weights + weight_offset);

				double delta_weight = 0.0;
				delta_weight = - learn_rate * (phi * sigmoid_node_end + alpha * curr_weight);
				LOG_INFO(MEDIUM, "[Backpropoagation stage] [Weight update %0d] phi %0f sigmoid_node_end %0d learning rate %0f alpha %0f curr_weight %0d -> delta weight %0f", weight_offset, phi, sigmoid_node_end, learn_rate, alpha, curr_weight, delta_weight);

				*(*weights + weight_offset) += delta_weight;
				LOG_INFO(MEDIUM, "[Backpropoagation stage] [Weight update %0d] Old value %0f Delta %0f -> New value %0f", weight_offset, curr_weight, delta_weight, *(*weights  + weight_offset));

			}

		}

		// Value used in the next iteration.
		// Take out the number of weight between the previous layer (that will be current layer in the next iteration) and those in the current layer (next layer during next iteration).
		base_weight -= (num_neurons_prev * num_neurons);
		ASSERT(base_weight >= 0);

		free_memory(phi_arr_prev);
		phi_arr_prev = NULL;
		phi_arr_prev = (double *) malloc(phi_arr_dim*sizeof(double));
		if (phi_arr_prev==NULL) {
			LOG_ERROR("Can't allocate memory for array storing values of phi collected in the current iteration");
		}

		memcpy(phi_arr_prev, phi_arr, (phi_arr_dim*sizeof(double)));
		free_memory(phi_arr);

		// Make phi_arr_prev point to the location phi_arr is pointing to
//		phi_arr_prev = phi_arr;
		phi_arr = NULL;

		base_node -= num_neurons;

		// (num_neurons_prev - 1): Take out 1 as the total number of neurons in the previous layer (num_neurons_prev) accounts lso for the bias
		ASSERT(base_node >= (num_neurons_prev - 1));
	}

	free_memory(phi_arr_prev);

	// base_node here is expected to be equal to the number of node of the input layer
	ASSERT(base_node == *layers_dim);
}
