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

double sigmoid (elementdatatype_t * elements) {

	LOG_INFO(DEBUG,"Number of bytes of all the element %0d\n",  (int)(sizeof(elements)));
	LOG_INFO(DEBUG,"Number of bytes of each element %0d\n",  (int)(sizeof(elementdatatype_t)));
	int no_elements = 0;
	no_elements = sizeof(elements)/sizeof(elementdatatype_t);
	LOG_INFO(HIGH,"Number of elements -> %0d/%0d = %0d\n", (int)(sizeof(elements)), (int)(sizeof(elementdatatype_t)), no_elements);
	ASSERT(no_elements > 0);

	double element_sum = 0.0;

	for (int el=0; el < no_elements; el++) {
		element_sum += *(elements + el);
	}

	double sigmoid_val = 0.0;
	sigmoid_val = 1/(1 + exp(element_sum));

	return sigmoid_val;

}
