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

/** 
 * @brief Function: void parse_command_line (int argc, char * argv [], char ** test_set, char ** train_set, char ** test_label, char ** train_label)
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 * \param test_set: test set filename
 * \param train_set: training set filename
 * \param test_label: test label filename
 * \param train_label: training label filename
 *
 * Parse and process command line (argc and argv)
 */
void parse_command_line (int argc, char * argv [], char ** test_set, char ** train_set, char ** test_label, char ** train_label);
/** @} */ // End of MainGroup group
#endif // MAIN_H
