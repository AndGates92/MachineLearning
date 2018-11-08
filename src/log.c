/**
 * @copyright
 * @file log.c
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Logging functions
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "file.h"
#include "utility.h"

FILE * logfile;

void log_info(verb_level_e verbosity, const char * str_format, ...) {

	if (verbosity < DEFAULT_VERBOSITY) { 
		va_list arglist;

		// Initialize argptr for number of arguments argnum 
		va_start(arglist, str_format);

		if (logfile==NULL) {
			char * filename = NULL;
			filename = (char *) malloc(LOGFILE_MAX_LENGTH*sizeof(char));
			if (filename==NULL) {
				LOG_ERROR("Can't allocate memory for log filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
			}
			strcpy(filename, STRINGIFY_EXPR(LOGFILE));

			logfile = fopen(filename, "a");
			if (logfile==NULL) {
				LOG_ERROR("Can't open file %s for write at %s, function %s, line %0d\n", filename, __FILE__, __func__, __LINE__);
			}
			log_info(HIGH, "File %s in function %s at line %0d: Opened file %s for write. File descriptor %0d\n", __FILE__, __func__, __LINE__,  filename, fileno(logfile));
			free(filename);
		}
		vfprintf (logfile, str_format, arglist);

		va_end(arglist);
	}
}

void close_logfile () {
	char * filename = NULL;
	filename = (char *) malloc(LOGFILE_MAX_LENGTH*sizeof(char));
	if (filename==NULL) {
		LOG_ERROR("Can't allocate memory for log filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	strcpy(filename, STRINGIFY_EXPR(LOGFILE));

	log_info(HIGH, "File %s in function %s at line %0d: Closing logfile %s\n", __FILE__, __func__, __LINE__,  filename);
	file_close(logfile);
}

char * bool_to_str (bool expr) {
	return (expr ? "True" : "False");
}
