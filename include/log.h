#ifndef LOG_H
#define LOG_H
/**
 * @copyright
 * @file log.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Log handling header file
*/

#include <stdbool.h>
#include "utility.h"
#include "file.h"

/** @defgroup LogGroup Log Doxygen Group
 *  Functions and defines logging progress
 *  @{
 */
/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE ml.log
#endif

/**
 * @brief Default verbosity level
 *
 */
#if !defined(VERBOSITY)
	#define VERBOSITY MEDIUM
#endif

/**
 * @brief log filename max length
 *
 */
#define LOGFILE_MAX_LENGTH 20

/**
 * @brief Bolean sring max length
 *
 */
#define BOOL_MAX_LENGTH 5

/**
 * @brief Verbosity levels
 *
 */
typedef enum verb_level_list {
	ZERO,
	LOW,
	MEDIUM,
	HIGH,
	DEBUG
} verb_level_e;


/**
 * @brief Pointer to log file
 *
 */
extern FILE * logfile;

/**
 * @brief LOG_ERROR(...)
 *
 * \param ... : variable number of arguments to provide to fprintf
 *
 * Print an error message to stderr and exits with EXIT_FAILURE status
 */
#define LOG_ERROR(...)\
	fprintf (stderr, "File %s at line %0d: ", __FILE__, __LINE__);\
	fprintf (stderr, __VA_ARGS__);\
	fprintf (stderr, "\n");\
	close_logfile ();\
	exit(EXIT_FAILURE);

/**
 * @brief LOG_INFO(VERBOSITY, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param ... :       variable number of arguments to provide to log_info
 *
 * Print an message message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define LOG_INFO(VERBOSITY, ...)\
	log_info(VERBOSITY, "File %s at line %0d: ", __FILE__, __LINE__);\
	log_info(VERBOSITY, __VA_ARGS__);\
	log_info(VERBOSITY, "\n");

/**
 * @brief ASSERT(EXPR)
 *
 * \param EXPR : expression to assert
 *
 * Assert the expression and if it fails, an error message is printed to stderr and the program exits with EXIT_FAILURE status
 */
#ifdef ENABLE_ASSERTIONS
#define ASSERT(EXPR)\
	if (!(EXPR)) {\
		LOG_ERROR("ASSERTION FAILED (%s)", STRINGIFY_EXPR(EXPR));\
	}
#else
#define ASSERT(EXPR)\
	if (!(EXPR)) {\
		LOG_INFO(ZERO,"ASSERTION FAILED (%s)", STRINGIFY_EXPR(EXPR));\
	}
#endif // ENABLE_ASSERTIONS

/** 
 * @brief Function: void log_info (verb_level_e verbosity, const char * str_format, ...)
 *
 * \param verbosity:   specify the minimum verbosity level required to print a message
 * \param str_format:  format string following same specification as format in printf
 * \param ...:         argument to replace whose value is replace in str_format string
 *
 * Log information to a logfile
 * If log file is not opened, it will open for write
 */
void log_info (verb_level_e verbosity, const char * str_format, ...);

/** 
 * @brief Function: void close_logfile ()
 *
 * Close logfile at the end of the program
 */
void close_logfile ();

/** 
 * @brief Function: char * bool_to_str (bool expr)
 *
 * Convert boolean to string
 */
char * bool_to_str (bool expr);

/** @} */ // End of LogGroup group
#endif // LOG_H
