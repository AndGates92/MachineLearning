/**
 * @copyright
 * @file neuron.c
 * @author Andrea Gianarda
 * @date 8th of November 2018
 * @brief Function body of neurons
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "neuron.h"
#include "log.h"

double sigmoid (double elements) {

	double sigmoid_val = 0.0;
	sigmoid_val = 1.0/(1.0 + exp(-elements));

	LOG_INFO(DEBUG,"[Sigmoid] S(%0f): %0f",  elements, sigmoid_val);

	return sigmoid_val;

}

double sigmoid_der (double elements) {

	double sigmoid_val = 0.0;
	sigmoid_val = sigmoid(elements) * (1.0 - sigmoid(elements));

	LOG_INFO(DEBUG,"[Sigmoid derivative] S(%0f)': %0f",  elements, sigmoid_val);

	return sigmoid_val;

}
