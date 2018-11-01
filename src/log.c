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
#include <assert.h>
#include "log.h"
#include "file.h"
#include "utility.h"

FILE * logfile;

void log_info(const char * str_format, ...) {

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

		logfile = fopen(filename, "w");
		if (logfile==NULL) {
			LOG_ERROR("Can't open file %s for write at %s, function %s, line %0d\n", filename, __FILE__, __func__, __LINE__);
		}
		log_info("Opened file %s for write. File descriptor %0d\n", filename, fileno(logfile));
		free(filename);
	}
	vfprintf (logfile, str_format, arglist);

	va_end(arglist);
}

void close_logfile () {
	char * filename = NULL;
	filename = (char *) malloc(LOGFILE_MAX_LENGTH*sizeof(char));
	if (filename==NULL) {
		LOG_ERROR("Can't allocate memory for log filename at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	strcpy(filename, STRINGIFY_EXPR(LOGFILE));

	log_info("Closing logfile %s\n", filename);
	file_close(logfile);
}
