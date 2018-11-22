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
 * @brief Function: void feedforward_stage (double * weights, double * biases, int * layers_dim, elementdatatype * input_data, elementdatatype ** node_val)
 *
 *
 * \param weights: weights of neural network layers
 * \param bias: bias of neural network
 * \param layers_dim:  array storing dimensions of every layer in the neural network
 * \param input_data:  array of one element to process
 * \param node_val:  result from the neural network. It is a vector of values between zero and one
 *
 * Initialize weight and bias of neural network
 */
void feedforward_stage (double * weights, double * biases, int * layers_dim, elementdatatype * input_data, elementdatatype ** node_val):

#endif // FEEDFORWARD_STAGE_H
