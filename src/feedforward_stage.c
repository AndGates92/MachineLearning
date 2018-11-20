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

void feedforward_stage (double * weights, double * biases, int * layers_dim, elementdatatype_t * input_data, double ** output_node_val) {

	int num_input_hidden_layers = 0;
	// Hidden layers plus input layer
	num_input_hidden_layers = (NUM_HIDDEN_LAYERS + 1);

	int weight_idx = 0;

	// Pointer to the input data of a layer
	double * data = NULL;

	// Pointer to the output data of a layer
	double * data_nxt = NULL;

	for (int layer_no = 0; layer_no < num_input_hidden_layers; layer_no++) {
		int num_neurons = 0;
		num_neurons = (*(layers_dim + layer_no));

		free_memory(data);

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

		free_memory(data_nxt);

		data_nxt = (double *) malloc(num_neurons_nxt*sizeof(double));
		if (data_nxt==NULL) {
			LOG_ERROR("Can't allocate memory for data array storing output data of the current processed layer");
		}

		for (int neuron_nxt_idx = 0; neuron_nxt_idx < num_neurons_nxt; neuron_nxt_idx++) {

			double tmp_sum = 0.0;

			for (int neuron_idx = 0; neuron_idx < num_neurons; neuron_idx++) {

				if (neuron_idx == 0) {
					tmp_sum += (*(weights + weight_idx)) * (*(bias + layer_no));
				} else {
					tmp_sum += (*(weights + weight_idx)) * (*(data + (neuron_idx - 1)));
				}

				weight_idx++;

			}

			*(data_nxt + neuron_nxt_idx) = sigmoid(tmp_sum);

			LOG_INFO(DEBUG,"Neuron %0d of stage %0d: %0d\n", neuron_nxt_idx, (layer_no+1), *(data_nxt + neuron_nxt_idx));

		}

	}
}
