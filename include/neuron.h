#ifndef NEURON_H
#define NEURON_H
/**
 * @copyright
 * @file neuron.h
 * @author Andrea Gianarda
 * @date 8th of November 2018
 * @brief Neuron handling header file
 */

#include "data.h"

/** @defgroup NeuronNetworkGroup Neuron Doxygen Group
 *  Functions and defines concerning neurons
 *  @{
 */
/** 
 * @brief Function: double sigmoid (double * elements)
 *
 * \param elements:    elements of the data strcture data_t to use in the sigmoid function
 *
 * Compute the sigmoid function value using input elements
 */
double sigmoid (double elements);

/** 
 * @brief Function: double sigmoid_der (double * elements)
 *
 * \param elements:    elements of the data strcture data_t to use in the derivative of sigmoid function
 *
 * Compute the derivatinve of the sigmoid function value using input elements
 */
double sigmoid_der (double elements);


/** @} */ // End of NeuronNetworkGroup group
#endif // NEURON_H
