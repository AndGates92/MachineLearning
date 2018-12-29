#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
/**
 * @copyright
 * @file neural_network.h
 * @author Andrea Gianarda
 * @date 12th of November 2018
 * @brief Neural network header file
*/

#include "data.h"


/** @defgroup NeuralNetowrk Neural network top level functions
 *  Functions and defines neural network
 *  @{
 */
/**
 * @brief Number of hidden layers
 *
 */
#define NUM_HIDDEN_LAYERS 1

/**
 * @brief Mean value of weights
 *
 */
#define WEIGHT_MEAN 0

/**
 * @brief Standard deviation of weights
 *
 */
#define WEIGHT_STD_DEV 1

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
 * @brief Maximum value of weights
 *
 */
#define MAX_ALPHA 1

/**
 * @brief Minimum value of weights
 *
 */
#define MIN_ALPHA 0

/**
 * @brief Maximum value of bias
 *
 */
#define MAX_LEARN_RATE 1

/**
 * @brief Minimum value of bias
 *
 */
#define MIN_LEARN_RATE 0

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
 * @brief Function: void initialize_neuronetwork(double ** weights, double ** biases, int ** layers_dim, data_t * data_set, data_t * data_label, double * learn_rate, double * alpha)
 *
 * \param weights: weights of neural network layers
 * \param biases: bias of neural network
 * \param layers_dim: array storing the dimension of the layers of the neural network
 * \param data_set:  data structure to extract dimensions of the input layer of the neural network
 * \param data_label:  data structure to extract dimensions of the output layer of the neural network
 * \param learn_rate: learning rate of the neural network
 * \param alpha: alpha smoothing parameter
 *
 * Initialize weight and bias of neural network and compute the dimensions of all the layers of the neuronetwork
 */
void initialize_neuronetwork(double ** weights, double ** biases, int ** layers_dim, data_t * data_set, data_t * data_label, double * learn_rate, double * alpha);

/** 
 * @brief Function: void create_elements_window(data_t * data_set, data_t * data_label, char * win_name_prefix)
 *
 * \param data_set:  data structure to extract dimensions of the input layer of the neural network
 * \param data_label:  data structure to extract dimensions of the output layer of the neural network
 * \param win_name_prefix: window name prefix
 *
 * Create a windows where elements can be displayed
 */
void create_elements_window(data_t * data_set, data_t * data_label, char * win_name_prefix);

/**
 * @brief Function: void train_neural_network(double * weights, double * biases, int * layers_dim, data_t * data_set, data_t * data_label, double learn_rate, double alpha)
 *
 * \param weights: weights of neural network layers
 * \param biases: bias of neural network
 * \param layers_dim: array storing the dimension of the layers of the neural network
 * \param data_set:  data structure whose elements are used to train the neural network
 * \param data_label:  data structure containing the label of each element in data structure data_set
 * \param learn_rate: learning rate of the neural network
 * \param alpha: alpha smoothing parameter
 *
 * Train neural network
 */
void train_neural_network(double * weights, double * biases, int * layers_dim, data_t * data_set, data_t * data_label, double learn_rate, double alpha);

/**
 * @brief Function: void testing_neural_network(double * weights, double * biases, int * layers_dim, data_t * data_set, data_t * data_label)
 *
 * \param weights: weights of neural network layers
 * \param biases: bias of neural network
 * \param layers_dim: array storing the dimension of the layers of the neural network
 * \param data_set:  data structure whose elements are used to train the neural network
 * \param data_label:  data structure containing the label of each element in data structure data_set
 *
 * Test neural network
 */
void testing_neural_network(double * weights, double * biases, int * layers_dim, data_t * data_set, data_t * data_label);

/**
 * @brief Function: int * set_el_coord(int no_dims, int el_idx)
 *
 * \param no_dims: Number of dimensions
 * \param el_idx: index of element
 *
 * Set coordinate array
 */
int * set_el_coord(int no_dims, int el_idx);

/**
 * @brief Function: double * get_data_el(data_t * data_set, int el_idx)
 *
 * \param data_set: data set used in neural network
 * \param el_idx: index of element
 *
 * Get dataset element and normalize it
 */
double * get_data_el(data_t * data_set, int el_idx);

/**
 * @brief Function: int get_label_el(data_t * data_label, int el_idx)
 *
 * \param data_label: label data set used in neural network
 * \param el_idx: index of element
 *
 * Get label dataset element
 */
int get_label_el(data_t * data_label, int el_idx);
/** @} */ // End of NeuralNetwork group
#endif // NEURAL_NETWORK_H
