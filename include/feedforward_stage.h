#ifndef FEEDFORWARD_STAGE_H
#define FEEDFORWARD_STAGE_H
/**
 * @copyright
 * @file feedforward_stage.h
 * @author Andrea Gianarda
 * @date 14th of November 2018
 * @brief Feedforwards stage header file
*/

#include "data.h"
/** 
 * @brief Function: void feedforward_stage (data_t * data_set, double * weights, double * biases, double ** output_node_val, int * layers_dim)
 *
 *
 * \param weights: weights of neural network layers
 * \param bias: bias of neural network
 * \param data_set:  data structure to extract dimensions of each layer of neural network
 * \param output_node_val:  result from the neural network. It is a vector of values between zero and one
 * \param layers_dim:  array storing dimensions of every layer in the neural network
 *
 * Initialize weight and bias of neural network
 */
void feedforward_stage (data_t * data_set, elementdatatype_t * weights, elementdatatype_t * biases, elementdatatype ** output_node_val, int * layers_dim):

#endif // FEEDFORWARD_STAGE_H
