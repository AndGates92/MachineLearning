#ifndef UTILITY_H
#define UTILITY_H
/**
 * @copyright
 * @file file.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Utility handling header file
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

/** @} */ // End of UtilityFunc group
#endif // UTILITY_H
