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

	if (verbosity <= VERBOSITY) { 
		va_list arglist;

		// Initialize argptr for number of arguments argnum 
		va_start(arglist, str_format);

		if (logfile==NULL) {
			char * filename = NULL;
			filename = (char *) malloc(LOGFILE_MAX_LENGTH*sizeof(char));
			if (filename==NULL) {
				LOG_ERROR("Can't allocate memory for log filename");
			}
			strcpy(filename, STRINGIFY_EXPR(LOGFILE));

			logfile = fopen(filename, "a");
			if (logfile==NULL) {
				LOG_ERROR("Can't open file %s for write", filename);
			}
			LOG_INFO(HIGH, "[Log Info] Opened file %s for write. File descriptor %0d", filename, fileno(logfile));
			free_memory(filename);
		}
		vfprintf (logfile, str_format, arglist);
		va_end(arglist);
	}
}

void close_logfile () {
	char * filename = NULL;
	filename = (char *) malloc(LOGFILE_MAX_LENGTH*sizeof(char));
	if (filename==NULL) {
		LOG_ERROR("Can't allocate memory for log filename");
	}
	strcpy(filename, STRINGIFY_EXPR(LOGFILE));

	LOG_INFO(HIGH,"[Close Logfile] Closing logfile %s",  filename);
	file_close(logfile);
	free_memory(filename);
}

char * bool_to_str (bool expr) {
	return (expr ? "True" : "False");
}
