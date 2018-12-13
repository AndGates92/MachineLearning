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

void feedforward_stage (double * weights, double * biases, int * layers_dim, double * input_data, double ** node_val, int * outcome) {

	int num_input_hidden_layers = 0;
	// Hidden layers plus input layer
	num_input_hidden_layers = (NUM_HIDDEN_LAYERS + 1);

	int weight_idx = 0;

	// Pointer to the output data of a layer
	double * data_nxt = NULL;

	int data_ptr = 0;

	for (int layer_no = 0; layer_no < num_input_hidden_layers; layer_no++) {
		int num_neurons = 0;
		// Add 1 for the bias
		num_neurons = (*(layers_dim + layer_no));
		LOG_INFO(HIGH, "[Feedforward stage] [Neighbour layer dimensions] Current Layer %0d -> Dimension %0d", layer_no, num_neurons);

		// Pointer to the input data of a layer
		double * data = NULL;

		data = (double *) malloc(num_neurons*sizeof(double));
		if (data==NULL) {
			LOG_ERROR("Can't allocate memory for data array storing input data of the current processed layer");
		}

		if (layer_no == 0) {
			memcpy(data, input_data, (num_neurons*sizeof(double)));
			memcpy(*node_val, input_data, (num_neurons*sizeof(double)));
			data_ptr += num_neurons;
		} else {
			memcpy(data, data_nxt, (num_neurons*sizeof(double)));
		}

		int num_neurons_nxt = 0;
		num_neurons_nxt = (*(layers_dim + layer_no + 1));
		LOG_INFO(HIGH, "[Feedforward stage] [Neighbour layer dimensions] Next Layer %0d -> Dimension %0d", layer_no, num_neurons_nxt);

		free_memory(data_nxt);

		data_nxt = (double *) malloc(num_neurons_nxt*sizeof(double));
		if (data_nxt==NULL) {
			LOG_ERROR("Can't allocate memory for data array storing output data of the current processed layer");
		}

		int max_idx = 0;
		double max_certainty = 0;

		for (int neuron_nxt_idx = 0; neuron_nxt_idx < num_neurons_nxt; neuron_nxt_idx++) {

			double tmp_sum = 0.0;

			for (int neuron_idx = 0; neuron_idx <= num_neurons; neuron_idx++) {

				if (neuron_idx == 0) {
					tmp_sum += (*(weights + weight_idx)) * (*(biases + layer_no));
					LOG_INFO(HIGH,"[Feedfoward stage] [Neuron %0d of stage %0d] Partial Sum of weight[weight_idx = %0d] %0f and bias[layer = %0d] %0f: %0f", neuron_nxt_idx, (layer_no + 1), weight_idx, (*(weights + weight_idx)), layer_no, (*(biases + layer_no)), tmp_sum);
				} else {
					tmp_sum += (*(weights + weight_idx)) * (double)(*(data + (neuron_idx - 1)));
					LOG_INFO(HIGH,"[Feedfoward stage] [Neuron %0d of stage %0d] Partial Sum of weight[weight_idx = %0d] %0f and neuron[neuron_num = %0d] %0f: %0f", neuron_nxt_idx, (layer_no + 1), weight_idx, (*(weights + weight_idx)), (neuron_idx - 1), (*(data + (neuron_idx - 1))), tmp_sum);
				}

				weight_idx++;

			}

			double certainty = 0.0;
			certainty = sigmoid(tmp_sum);
			*(data_nxt + neuron_nxt_idx) = certainty;

			*(*node_val + data_ptr) = tmp_sum;
			LOG_INFO(MEDIUM,"[Feedfoward stage] [Neuron %0d of stage %0d] Sum of all weights by all neurons %0f -> Sigmoid S(%0f) = %0f", neuron_nxt_idx, (layer_no + 1), tmp_sum, tmp_sum, *(data_nxt + neuron_nxt_idx));

			ASSERT(certainty >= 0.0);

			if (max_certainty < certainty) {
				max_idx = neuron_nxt_idx;
				max_certainty = certainty;
			}

			data_ptr++;

		}

		if (layer_no == (num_input_hidden_layers - 1)) {
			*outcome = max_idx;
			LOG_INFO(LOW,"[Feedforward stage] [Neural network guess] output index %0d certainty %0f", max_idx, max_certainty);
		}

		free_memory(data);

	}

	free_memory(data_nxt);

}
