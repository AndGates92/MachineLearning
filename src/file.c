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

	LOG_INFO(HIGH,"Attempting to open file %s for %s\n",  filename, mode);

	fid = fopen(filename, permission);
	if (fid==NULL) {
		LOG_ERROR("Can't open file %s for %s", filename, mode);
	}

	LOG_INFO(DEBUG,"Opened file %s for %s. File descriptor %0d\n",  filename, mode, fileno(fid));

	free_memory(mode);

	return fid;
}

void file_close (FILE * fid) {
	if (fid!=NULL) {
		LOG_INFO(HIGH,"Closing file associated with file descriptor %0d\n",  fileno(fid));
		fclose(fid);
	}
}
