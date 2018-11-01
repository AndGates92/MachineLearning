/**
 * @copyright
 * @file file.h
 * @author Andrea Gianarda
 * @date 24th of October 2018
 * @brief File handling header file
*/

/**
 * @brief Maximum number of character for file opening mode
 *
 */
#define MODE_MAX_CHAR 7

/** @defgroup FileFunc File Functions
 *  Functions concerning file manipulation
 *  @{
 */
/** 
 * @brief Function: FILE * file_open (const char * filename, const char * permission)
 *
 * \param filename:    filename of the file to open
 * \param permission:  permission requested
 * \return a pointer to the file
 *
 * Open a file and return a pointer to it
 */
FILE * file_open (const char * filename, const char * permission);

/** 
 * @brief Function: void file_close (FILE * fid)
 *
 * \param fid:    file ID of file to close
 *
 * Close a file
 */
void file_close (FILE * fid);
/** @} */ // End of FileFunc group
