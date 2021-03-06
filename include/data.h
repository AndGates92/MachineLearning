#ifndef DATA_H
#define DATA_H
/**
 * @copyright
 * @file data.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Data handling header file
*/

/** @defgroup DataGroup Data Doxygen Group
 *  Functions and defines concerning data strcture data_t
 *  @{
 */
/**
 * @brief element type
 *
 * Datatype of elements in data structure data_t
 */
// Uncomment element data type
//typedef int elementdatatype_t;
//typedef unsigned char elementdatatype_t;
//typedef char elementdatatype_t;
//typedef unsigned short elementdatatype_t;
typedef short elementdatatype_t;
//typedef float elementdatatype_t;
//typedef double elementdatatype_t;

/**
 * @brief Length of data type string
 *
 */
#define MAX_DATA_TYPE_LENGTH 8

/**
 * @brief data type enumeration data_type_e
 *
 */
typedef enum data_type_list {
	UBYTE,
	SBYTE,
	SHORT,
	INTEGER,
	FLOAT,
	DOUBLE,
	UNKNOWN
} data_type_e;

/**
 * @brief data structure data_t
 *
 */
typedef struct data data_t;

/**
 * @brief Function: data_t * add_data (int * dimensions, int no_dims)
 *
 * \param dimensions: array with the dimensions of the data strcture data_t
 * \param no_dims:    number of dimensions of the data strcture data_t
 * \return a pointer to an data strcture data_t
 *
 * Create and allocate memory for a new data strcture data_t
 */
data_t * add_data (int * dimensions, int no_dims);

/**
 * @brief Function: void delete_data (data_t * data)
 *
 * \param data:  data strcture data_t to delete
 * 
 * Delete an data strcture data_t. Frees up memory as well.
 */
void delete_data (data_t * data);

// Set fields of data strcture data_t

/**
 * @brief Function: void set_dimensions (data_t ** data, int * dimensions)
 *
 * \param data:        input data strcture data_t
 * \param dimensions:  array with the dimensions of the data strcture data_t
 * 
 * Set the dimensions of the data strcture data_t.
 */
void set_dimensions (data_t ** data, int * dimensions);

/**
 * @brief Function: void set_no_dims (data_t ** data, int no_dims)
 *
 * \param data:    input data strcture data_t
 * \param no_dims: number of dimensions of the data strcture data_t
 * 
 * Set the number of domensions of the data strcture data_t.
 */
void set_no_dims (data_t ** data, int no_dims);

/**
 * @brief Function: void set_data_type (data_t ** data, data_type_e data_type)
 *
 * \param data:    input data strcture data_t
 * \param data_type: data type of elements of the data strcture data_t
 * 
 * Set the data type of the data strcture data_t.
 */
void set_data_type (data_t ** data, data_type_e data_type);

/**
 * @brief Function: void set_element (data_t ** data, elementdatatype_t element, int * coordinates)
 *
 * \param data:      input data strcture data_t 
 * \param element:    element of the data strcture data_t to add
 * \param coordinates:  coordinates of element to add
 * 
 * Set an element of the data strcture data_t.
 */
void set_element (data_t ** data, elementdatatype_t element, int * coordinates);

/**
 * @brief Function: void set_data_elements (data_t ** data, elementdatatype_t* elements)
 *
 * \param data:      input data strcture data_t 
 * \param elements:    elements of the data strcture data_t to add
 * 
 * Set elements of the data strcture data_t.
 */
void set_data_elements (data_t ** data, elementdatatype_t * elements);

/**
 * @brief Function: void set_min_element (data_t ** data, elementdatatype_t min_el_value)
 *
 * \param data:    input data strcture data_t
 * \param min_el_value:   value to set lowest element in array elements to
 * 
 * Set the lowest value stored in array elements.
 */
void set_min_element (data_t ** data, elementdatatype_t min_el_value);

/**
 * @brief Function: void set_max_element (data_t ** data, elementdatatype_t max_el_value)
 *
 * \param data:    input data strcture data_t
 * \param max_el_value:   value to set highest element in array elements to
 * 
 * Set the highest value stored in array elements.
 */
void set_max_element (data_t ** data, elementdatatype_t max_el_value);

// Get fields of data strcture data_t

/**
 * @brief Function: int * get_width (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return an array of the dimensions of the data structure data_t
 * 
 * Get the dimensions of the data structure data_t.
 */
int * get_dimensions (data_t * data);

/**
 * @brief Function: int get_width (data_t * data, int idx)
 *
 * \param data: input data strcture data_t
 * \param idx:  index of the dimension to return
 * \return the dimension of the data structure data_t matching the index
 * 
 * Get the dimension at index idx of the data structure data_t.
 */
int get_dimension (data_t * data, int idx);

/**
 * @brief Function: int get_no_dims (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the number of dimensions of the data structure
 * 
 * Get the number of dimensions of the data structure.
 */
int get_no_dims (data_t * data);

/**
 * @brief Function: data_type_e get_data_type (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the data type of elements in the data structure
 * 
 * Get the data type of element in the data structure.
 */
data_type_e get_data_type (data_t * data);

/**
 * @brief Function: short get_no_dims (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the number of bytes of the data type of the data structure
 * 
 * Get the number of bytes of the data type of the data structure.
 */
short get_no_bytes (data_t * data);

/**
 * @brief Function: elementdatatype_t get_min_element (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the lowest value stored in array elements of the data structure data_t
 * 
 * Get the lowest value stored in array elements.
 */
elementdatatype_t get_min_element (data_t * data);

/**
 * @brief Function: elementdatatype_t get_max_element (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the highest value stored in array elements of the data structure data_t
 * 
 * Get the highest value stored in array elements.
 */
elementdatatype_t get_max_element (data_t * data);

/**
 * @brief Function: elementdatatype_t get_element (data_t * data, int * coordinates)
 *
 * \param data:    input data strcture data_t
 * \param coordinates:  coordinates of element to return
 * \return the element of the data strcture data_t at coordinates passed as input
 * 
 * Get an element of the data strcture data_t.
 */
elementdatatype_t get_element (data_t * data, int * coordinates);

 /**
 * @brief Function: elementdatatype_t * get_elements_subset (data_t * data, int no_elements, int * start_position)
 *
 * \param data:    data structure
 * \param no_elements:    number of elements to return
 * \param start_position: index of the first element to return
 * \return an array of elements that stores elements with indexes between start_position and (start_position + no_elements - 1)
 *
 * Extract no_elemens elements from elements array starting with index start_position
 */
elementdatatype_t * get_elements_subset (data_t * data, int no_elements, int * start_position);

/**
 * @brief Function: elementdatatype_t * get_data_elements (data_t * data)
 *
 * \param data:    input data strcture data_t
 * \return the elements of the data structure data_t
 * 
 * Get an array of elements of the data strcture data_t.
 */
elementdatatype_t * get_data_elements (data_t * data);

/**
 * @brief Function: void get_data_fields(data_t * data, int * no_dims, int ** dimensions, data_type_e * data_type, short * no_bytes, elementdatatype_t ** elements)
 *
 * \param data:    input data strcture data_t
 * \param no_dims: number of dimensions of the data structure
 * \param dimensions: dimensions of the data structure
 * \param data_type: data type of the data structure
 * \param no_bytes: number fo bytes
 * \param elements: elements of the data stucture
 * 
 * Get all fields of the data structure.
 */
void get_data_fields(data_t * data, int * no_dims, int ** dimensions, data_type_e * data_type, short * no_bytes, elementdatatype_t ** elements);

/**
 * @brief Function: int compute_element_offset (data_t * data, int * coordinates)
 *
 * \param data:    input data strcture data_t
 * \param coordinates:  coordinates of element to return the absolute index
 * \return the absolute index of the element of the data strcture data_t at coordinates passed as input
 * 
 * Compute the coordinates of an element of the data strcture data_t.
 */
int compute_element_offset (data_t * data, int * coordinates);

/**
 * @brief Function: char * data_type_to_str (data_type_e data_type)
 *
 * \param data_type:    data type of data strcture data_t
 * \return a string with the name of the data type
 * 
 * Convert the data type to a string that can be printed.
 */
char * data_type_to_str (data_type_e data_type);

/**
 * @brief Function: short data_type_bytes (data_type_e data_type)
 *
 * \param data_type:    data type of data strcture data_t
 * \return the number of bytes of the data type
 * 
 * Compute the number of bytes of the data type.
 */
short data_type_bytes (data_type_e data_type);

 /**
 * @brief Function: int compute_total_no_elements(data_t * data)
 *
 * \param data:    data structure
 * \return the total number of elements in the array of elements
 * 
 * Compute the total number of elements in the array of elements.
 */
int compute_total_no_elements(data_t * data);

 /**
 * @brief Function: int element_size(data_t * data)
 *
 * \param data:    data structure
 * \return the size of the elements in the data strcture data_t assuming that the first dimension of array dimensions is the number of elements in the array
 * 
 * Compute the total number of elements in the array of elements.
 */
int element_size(data_t * data);

/**
 * @brief Function: size_t data_size()
 *
 * \return the size of data structure data_t
 * 
 * Get the size of data structure data_t.
 */
size_t data_size();

/** @} */ // End of DataGroup group
#endif // DATA_H
