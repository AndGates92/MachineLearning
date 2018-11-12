#ifndef MAIN_H
#define MAIN_H
/**
 * @copyright
 * @file main.h
 * @author Andrea Gianarda
 * @date 23rd of October 2018
 * @brief main header file
*/

/** @defgroup MainGroup Main file Doxygen Group
 *  Function and defines concerning top level file
 *  @{
 */
/**
 * @brief Maximum number of character allowed in the filename
 *
 */
#define FILENAME_MAX_LENGTH 200

/**
 * @brief training set option
 *
 */
const char* trs_opt = "-trs";

/**
 * @brief training label option
 *
 */
const char* trl_opt = "-trl";

/**
 * @brief test set option
 *
 */
const char* tes_opt = "-tes";

/**
 * @brief test label option
 *
 */
const char* tel_opt = "-tel";
/** @} */ // End of MainGroup group
#endif // MAIN_H
