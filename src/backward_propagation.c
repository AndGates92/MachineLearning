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

		int num_neurons_prev = 0;
		num_neurons_prev = (*(layers_dim + layer_no - 1));

		int phi_arr_dim = 0;
		phi_arr_dim = num_neurons_prev * num_neurons;

		int num_neurons_nxt = 0;

		int phi_arr_prev_dim = 0;

		double * phi_arr_prev = NULL;

		if (layer_no < (total_num_layers - 1)) {

			num_neurons_nxt = (*(layers_dim + layer_no + 1));

			phi_arr_prev_dim = num_neurons_nxt * num_neurons;

			phi_arr_prev = (double *) malloc(phi_arr_prev_dim*sizeof(double));

			memcpy(phi_arr_prev, phi_arr, (phi_arr_prev_dim*sizeof(double)));
		}

		free_memory(phi_arr);

		phi_arr = (double *) malloc(phi_arr_dim*sizeof(double));


		for (int neuron_idx = 0; neuron_idx < num_neurons; neuron_idx++) {

			double node_val_start = 0.0;
			node_val_start = *(node_val + (base_node - neuron_idx - 1));

			double sigmoid_node_start = 0.0;
			sigmoid_node_start = sigmoid(node_val_start);

			double sigmoid_der_node_start = 0.0;
			sigmoid_der_node_start = sigmoid_der(node_val_start);

			for (int neuron_prev_idx = 0; neuron_prev_idx < num_neurons_prev; neuron_prev_idx++) {

				double node_val_end = 0.0;

				double sigmoid_node_end = 0.0;
				if (neuron_prev_idx == (num_neurons_prev + 1)) {
					node_val_end = *(biases + layer_no);
					sigmoid_node_end = node_val_end;
				} else {
					node_val_end = *(node_val + (base_node - num_neurons - neuron_prev_idx - 1));
					sigmoid_node_end = sigmoid(node_val_end);
				}

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
						offset = ((num_neurons_prev - neuron_prev_idx) * num_neurons_nxt) - neuron_nxt_idx;

						double weight_el = 0.0;
						weight_el = *(*weights + (base_weight + offset - 1));

						double phi_el = 0.0;
						phi_el = *(phi_arr_prev + (phi_arr_prev_dim - 1));

						sum_phi_weight += (weight_el * phi_el);

						phi_arr_prev_dim--;

						LOG_INFO(DEBUG, "Backpropoagation stage: [Hidden layer of Input layer] Weight (base %0d offset %0d): %0d\n", base_weight, offset, weight_el);
						LOG_INFO(DEBUG, "Backpropoagation stage: [Hidden layer of Input layer] phi (offset %0d): %0d\n", phi_arr_prev_dim, phi_el);

					}

					phi = sigmoid_der_node_start * sum_phi_weight; 

				}

				double curr_weight = 0.0;
				curr_weight = *(*weights + (base_weight - neuron_prev_idx - 1));

				double delta_weight = 0.0;
				delta_weight = learn_rate * (phi * sigmoid_node_end + alpha * curr_weight);
				LOG_INFO(DEBUG, "Backpropoagation stage: [Weight update] phi = %0d learning rate = %0d delta weight %0d\n", phi, learn_rate, delta_weight);

				*(*weights + (base_weight - neuron_prev_idx - 1)) += delta_weight;
				LOG_INFO(HIGH, "Backpropoagation stage: [Weight update] Old value %0d Delta = %0d New value = %0d\n", curr_weight, delta_weight, *(*weights + (base_weight - neuron_prev_idx - 1)));

			}

			base_weight -= num_neurons_prev;

		}

		free_memory(phi_arr_prev);

		base_node =- num_neurons;

		ASSERT(base_node >= num_neurons_prev);

		// base_weight here is expected to be 0 because the input layer has been reached
		ASSERT(phi_arr_prev_dim == 0);

	}

	free_memory(phi_arr);

	// base_node here is expected to be equal to the number of node of the input layer
	ASSERT(base_node == *layers_dim);

	// base_weight here is expected to be 0 because the input layer has been reached
	ASSERT(base_weight == 0);
}
