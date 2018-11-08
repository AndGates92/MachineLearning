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

/** @defgroup NeuronFunc Neuron Functions
 *  Functions concerning neurons
 *  @{
 */
/** 
 * @brief Function: double sigmoid (elementdatatype_t * elements)
 *
 * \param elements:    elements of the data strcture data_t to use in the sigmoid function
 *
 * Compute the sigmoid function value using input elements
 */
double sigmoid (elementdatatype_t * elements);

/** @} */ // End of NeuronFunc group
#endif // NEURON_H
