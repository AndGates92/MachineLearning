#ifndef UTILITY_H
#define UTILITY_H
/**
 * @copyright
 * @file utility.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Utility handling header file
*/

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
 * @brief Function: void free_memory (void * ptr)
 *
 * \param ptr: pointer to the memory to free
 * 
 * Free memory pointed to the input argument pointer if ti is different from NULL.
 */
void free_memory (void * ptr);

/** @} */ // End of UtilityGroup group
#endif // UTILITY_H
