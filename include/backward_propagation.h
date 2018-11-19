#ifndef BACKWARD_PROPAGATION_H
#define BACKWARD_PROPAGATION_H
/**
 * @copyright
 * @file backward_propagation.h
 * @author Andrea Gianarda
 * @date 14th of November 2018
 * @brief Backward propagation header file
*/

/** 
 * @brief Function: void backward_propagation (double ** weights, double * biases, int * layers_dim, double * output_node_val, double * label)
 *
 *
 * \param weights: weights of neural network layers
 * \param bias: bias of neural network
 * \param layers_dim:  array storing dimensions of every layer in the neural network
 * \param output_node_val:  result from the neural network. It is a vector of values between zero and one
 * \param label:  label of the training set
 *
 * Compute backward propagation algorithm to adjust weights
 */
void backward_propagation (double ** weights, double * biases, int * layers_dim, double * output_node_val, double * label);

#endif // BACKWARD_PROPAGATION_H
