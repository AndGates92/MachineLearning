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
	#define DEFAULT_VERBOSITY MEDIUM
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
	fprintf (stderr, __VA_ARGS__);\
	close_logfile ();\
	exit(EXIT_FAILURE);

/**
 * @brief ASSERT(EXPR)
 *
 * \param EXPR : expression to assert
 *
 * Assert the expression and if it fails, an error message is printed to stderr and the program exits with EXIT_FAILURE status
 */
#define ASSERT(EXPR)\
	if (!(EXPR)) {\
		LOG_ERROR("ASSERTION FAILED (%s) at %s, function %s, line %0d\n", STRINGIFY_EXPR(EXPR), __FILE__, __func__, __LINE__);\
	}

/** @defgroup LogFunc Log Functions
 *  Functions logging progress
 *  @{
 */
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

/** @} */ // End of LogFunc group
#endif // LOG_H
