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
 * @brief Function: void backward_propagation (double ** weights, double * biases, int * layers_dim, double * node_val, int label, double learn_rate, double alpha)
 *
 * \param weights: weights of neural network layers
 * \param bias: bias of neural network
 * \param layers_dim:  array storing dimensions of every layer in the neural network
 * \param node_val:  result from the neural network. It is a vector of values between zero and one
 * \param label:  label of the training set
 * \param learn_rate: learning rate of the neural network
 * \param alpha: alpha smoothing parameter
 *
 * Compute backward propagation algorithm to adjust weights
 */
void backward_propagation (double ** weights, double * biases, int * layers_dim, double * node_val, int label, double learn_rate, double alpha);

#endif // BACKWARD_PROPAGATION_H
