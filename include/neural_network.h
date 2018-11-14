#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
/**
 * @copyright
 * @file neural_network.h
 * @author Andrea Gianarda
 * @date 12th of November 2018
 * @brief Neural network header file
*/

#include <stdbool.h>
#include "data.h"


/** @defgroup NeuralNetowrk Neural network top level functions
 *  Functions and defines neural network
 *  @{
 */
/**
 * @brief Number of hidden layers
 *
 */
#define NO_HIDDEN_LAYERS 1

/**
 * @brief Maximum value of weights
 *
 */
#define MAX_WEIGHT 1

/**
 * @brief Minimum value of weights
 *
 */
#define MIN_WEIGHT 0

/**
 * @brief Maximum value of bias
 *
 */
#define MAX_BIAS 1

/**
 * @brief Minimum value of bias
 *
 */
#define MIN_BIAS 0


/** 
 * @brief Function: void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t)
 *
 * \param test_set: filename of the IDX file containing the test set
 * \param train_set: filename of the IDX file containing the training set
 * \param test_label: filename of the IDX file containing the test labels
 * \param train_label: filename of the IDX file containing the training labels
 * \param test_set_struct_t: pointer to the data structure storing the test set
 * \param train_set_struct_t: pointer to the data structure storing the training set
 * \param test_label_struct_t: pointer to the data structure storing the test labels
 * \param train_label_struct_t: pointer to the data structure storing the training labels
 *
 * Parse IDX file and store data into structure
 */
void parse_all_idx (char * test_set, char * train_set, char * test_label, char * train_label, data_t ** test_set_struct_t, data_t ** test_label_struct_t, data_t ** train_set_struct_t, data_t ** train_label_struct_t);

/** 
 * @brief Function: void neural_network (char * test_set, char * train_set, char * test_label, char * train_label)
 *
 * \param test_set: filename of the IDX file containing the test set
 * \param train_set: filename of the IDX file containing the training set
 * \param test_label: filename of the IDX file containing the test labels
 * \param train_label: filename of the IDX file containing the training labels
 *
 * Neural network top level function
 */
void neural_network (char * test_set, char * train_set, char * test_label, char * train_label);

/** 
 * @brief Function: void initialize_neuronetwork(elementdatatype_t ** elements, elementdatatype_t ** bias, data_t * set)
 *
 * \param weights: weights of neural network layers
 * \param bias: bias of neural network
 * \param set:  data structure to extract dimensions of each layer of neural network
 *
 * Initialize weight and bias of neural network
 */
void initialize_neuronetwork(elementdatatype_t ** weights, elementdatatype_t ** bias, data_t * set);
/** @} */ // End of NeuralNetwork group
#endif // NEURAL_NETWORK_H
