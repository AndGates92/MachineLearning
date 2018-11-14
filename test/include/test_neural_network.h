#ifndef TEST_NEURAL_NETWORK_H
#define TEST_NEURAL_NETWORK_H
/**
 * @copyright
 * @file test_neural_network.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Test parse IDX file header file
*/

/** @defgroup TestNeuralNetworkGroup Test neural network Doxygen Group
 *  Functions and defines concerning test network
 *  @{
 */
/** 
 * @brief Function: void test_neural_network (char * test_set, char * train_set, char * test_label, char * train_label)
 *
 * \param test_set: test set filename
 * \param train_set: training set filename
 * \param test_label: test label filename
 * \param train_label: training label filename
 *
 * Train neural network based on input data
 */
void test_neural_network (char * test_set, char * train_set, char * test_label, char * train_label);

/** 
 * @brief Function: void compare(data_t * data1, data_t * data2)
 *
 * \param data1: first data structure to compare
 * \param data2: second data structure to compare
 *
 * Compare two data structures
 */
void compare(data_t * data1, data_t * data2);
/** @} */ // End of TestNeuralNetworkGroup group
#endif // TEST_NEURAL_NETWORK_H
