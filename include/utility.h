#ifndef UTILITY_H
#define UTILITY_H
/**
 * @copyright
 * @file utility.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Utility handling header file
*/
#include "data.h"

/** @defgroup UtilityGroup Utility Doxygen Group
 *  Functions and defines concerning utility
 *  @{
 */
/**
 * @brief STRINGIFY(x)
 *
 * \param x : argument to stringify
 *
 * Stringify input argumet
 *
 */
#define STRINGIFY(x) #x

/**
 * @brief STRINGIFY_EXPR(x)
 *
 * \param x : argument to stringify
 *
 * Evaluate input argument and pass it on to STRINGIFY macro
 *
 */
#define STRINGIFY_EXPR(x) STRINGIFY(x)

/**
 * @brief max(x,y)
 *
 * \param x : first argument
 * \param y : second argument
 *
 * Returns the maximum value between x and y
 *
 */
#define max(x,y) \
	({ __typeof__ (x) first_el = (x); \
	__typeof__ (y) second_el = (y); \
	(first_el > second_el) ? first_el : second_el; })

/**
 * @brief max(x,y)
 *
 * \param x : first argument
 * \param y : second argument
 *
 * Returns the minimum value between x and y
 *
 */
#define min(x,y) \
	({ __typeof__ (x) first_el = (x); \
	__typeof__ (y) second_el = (y); \
	(first_el < second_el) ? first_el : second_el; })

/**
 * @brief A byte constains 8 bits
 *
 */
#define BIT_IN_BYTE 8

/**
 * @brief Progress bar symbol
 *
 */
#define PROGRESS_BAR_SYMBOL #

/**
 * @brief Progress bar length
 *
 */
#define PROGRESS_BAR_LENGTH 50



/**
 * @brief Function: void free_memory (void * ptr)
 *
 * \param ptr: pointer to the memory to free
 * 
 * Free memory pointed to the input argument pointer if ti is different from NULL.
 */
void free_memory (void * ptr);

/**
 * @brief Function: unsigned char * cast_array_to_unsigned_byte (elementdatatype_t * element_set, int dimension)
 *
 * \param element_set: array fo elements to cast to unsigned char
 * \param dimension: dimension of the array to cast
 *
 * Cast elements of array element_set to unsigned char.
 */
unsigned char * cast_array_to_unsigned_byte (elementdatatype_t * element_set, int dimension);

/**
 * @brief Function: float * cast_array_to_float (elementdatatype_t * element_set, int dimension)
 *
 * \param element_set: array fo elements to cast to float
 * \param dimension: dimension of the array to cast
 *
 * Cast elements of array element_set to float.
 */
float * cast_array_to_float (elementdatatype_t * element_set, int dimension);

/**
 * @brief Function: double * cast_array_to_double (elementdatatype_t * element_set, int dimension)
 *
 * \param element_set: array fo elements to cast to double
 * \param dimension: dimension of the array to cast
 *
 * Cast elements of array element_set to double.
 */
double * cast_array_to_double (elementdatatype_t * element_set, int dimension);

/**
 * @brief Function: double * normalize_elements (double * element_set, elementdatatype_t max_element, int dimension)
 *
 * \param element_set: array of elements to cast to double
 * \param max_element: maximum element in the dataset
 * \param dimension: dimension of the array to cast
 *
 * Normalize elements of the input array.
 */
double * normalize_elements (double * element_set, elementdatatype_t max_element, int dimension);

/**
 * @brief Function: int * cast_array_to_int (elementdatatype_t * element_set, int dimension)
 *
 * \param element_set: array of elements to cast to int
 * \param dimension: dimension of the array to cast
 *
 * Cast elements of array element_set to int.
 */
int * cast_array_to_int (elementdatatype_t * element_set, int dimension);

/**
 * @brief Function: void statusbar(char * str, int idx, int max_val)
 *
 * \param str: string to put in front of percentage
 * \param idx: current index
 * \param max_val: maximum value of idx
 *
 * Prints a progress bar on the screen using the following format: [\<str\> percentage] \<bar\>.
 */
void statusbar(char * str, int idx, int max_val);

/** @} */ // End of UtilityGroup group
#endif // UTILITY_H
