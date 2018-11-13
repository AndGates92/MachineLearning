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
/** @} */ // End of NeuralNetwork group
#endif // NEURAL_NETWORK_H
