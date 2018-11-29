/**
 * @copyright
 * @file feedforward_stage.c
 * @author Andrea Gianarda
 * @date 19th of November 2018
 * @brief Functions related to the feedforward stage of the neural network
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "neural_network.h"
#include "neuron.h"
#include "feedforward_stage.h"
#include "utility.h"

void feedforward_stage (double * weights, double * biases, int * layers_dim, elementdatatype_t * input_data, double ** node_val, elementdatatype_t * outcome) {

	int num_input_hidden_layers = 0;
	// Hidden layers plus input layer
	num_input_hidden_layers = (NUM_HIDDEN_LAYERS + 1);

	int weight_idx = 0;

	// Pointer to the output data of a layer
	double * data_nxt = NULL;

	int data_ptr = 0;

	for (int layer_no = 0; layer_no < num_input_hidden_layers; layer_no++) {
		int num_neurons = 0;
		num_neurons = (*(layers_dim + layer_no));
		LOG_INFO(DEBUG, "Neighbour layer dimensions: Current Layer %0d -> Dimension %0d", layer_no, num_neurons);

		// Pointer to the input data of a layer
		double * data = NULL;

		data = (double *) malloc(num_neurons*sizeof(double));
		if (data==NULL) {
			LOG_ERROR("Can't allocate memory for data array storing input data of the current processed layer");
		}

		if (layer_no == 0) {
			memcpy(data, input_data, (num_neurons*sizeof(double)));
		} else {
			memcpy(data, data_nxt, (num_neurons*sizeof(double)));
		}

		int num_neurons_nxt = 0;
		num_neurons_nxt = (*(layers_dim + layer_no + 1));
		LOG_INFO(DEBUG, "Neighbour layer dimensions: Next Layer %0d -> Dimension %0d", layer_no, num_neurons_nxt);

		free_memory(data_nxt);

		data_nxt = (double *) malloc(num_neurons_nxt*sizeof(double));
		if (data_nxt==NULL) {
			LOG_ERROR("Can't allocate memory for data array storing output data of the current processed layer");
		}

		int max_idx = 0;
		double max_val = 0;

		for (int neuron_nxt_idx = 0; neuron_nxt_idx < num_neurons_nxt; neuron_nxt_idx++) {

			double tmp_sum = 0.0;

			for (int neuron_idx = 0; neuron_idx <= num_neurons; neuron_idx++) {

				if (neuron_idx == 0) {
					tmp_sum += (*(weights + weight_idx)) * (*(biases + layer_no));
				} else {
					tmp_sum += (*(weights + weight_idx)) * (*(data + (neuron_idx - 1)));
				}

				weight_idx++;

			}

			*(data_nxt + neuron_nxt_idx) = sigmoid(tmp_sum);

			*(*node_val + data_ptr) = tmp_sum;

			if (max_val < tmp_sum) {
				max_idx = neuron_nxt_idx;
			}

			data_ptr++;

			LOG_INFO(DEBUG,"Feedfoward stage: Neuron %0d of stage %0d: %0d", neuron_nxt_idx, layer_no, *(data_nxt + neuron_nxt_idx));

		}

		if (layer_no == (num_input_hidden_layers - 1)) {
			*outcome = (elementdatatype_t) max_val;
			LOG_INFO(LOW,"Neural network guess: output index %0d certainty %0lf", max_idx, max_val);
		}

		free_memory(data);

	}

	free_memory(data_nxt);

}
