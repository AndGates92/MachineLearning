/**
 * @copyright
 * @file log.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Log handling header file
*/

#include "file.h"

/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE ml.log
#endif

#define LOGFILE_MAX_LENGTH 20

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
 * Print an error message to stderr and exists with EXIT_FAILURE status
 */
#define LOG_ERROR(...)\
	fprintf (stderr, __VA_ARGS__);\
	close_logfile ();\
	exit(EXIT_FAILURE);

/** @defgroup LogFunc Log Functions
 *  Functions logging progress
 *  @{
 */
/** 
 * @brief Function: void log_info (const char * str_format, ...)
 *
 * \param str_format:  format string following same specification as format in printf
 * \param ...:         argument to replace whose value is replace in str_format string
 *
 * Log information to a logfile
 * If log file is not opened, it will open for write
 */
void log_info (const char * str_format, ...);

/** 
 * @brief Function: void close_logfile ()
 *
 * Close logfile at the end of the program
 */
void close_logfile ();

/** @} */ // End of LogFunc group
