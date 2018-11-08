/**
 * @copyright
 * @file file.c
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief Function body handling files
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "file.h"
#include "utility.h"

FILE * file_open (const char * filename, const char * permission) {

	FILE * fid = NULL;

	char * mode;
	mode = (char *) malloc(MODE_MAX_CHAR*sizeof(char));

	if (!(strcmp(permission, "r"))) {
		strcpy(mode, "read");
	} else if (!(strcmp(permission, "w"))) {
		strcpy(mode, "write");
	} else if (!(strcmp(permission, "w"))) {
		strcpy(mode, "append");
	} else {
		LOG_ERROR("Unknown permission requested: %s", permission);
	}

	log_info(HIGH, "File %s in function %s at line %0d: Attempting to open file %s for %s\n", __FILE__, __func__, __LINE__,  filename, mode);

	fid = fopen(filename, permission);
	if (fid==NULL) {
		LOG_ERROR("Can't open file %s for %s at %s, function %s, line %0d\n", filename, mode, __FILE__, __func__, __LINE__);
	}

	log_info(DEBUG, "File %s in function %s at line %0d: Opened file %s for %s. File descriptor %0d\n", __FILE__, __func__, __LINE__,  filename, mode, fileno(fid));

	free(mode);

	return fid;
}

void file_close (FILE * fid) {
	if (fid!=NULL) {
		log_info(HIGH, "File %s in function %s at line %0d: Closing file associated with file descriptor %0d\n", __FILE__, __func__, __LINE__,  fileno(fid));
		fclose(fid);
	}
}
