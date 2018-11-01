/**
 * @copyright
 * @file image.h
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Image handling header file
*/

/**
 * @brief pixel type
 *
 * Pixel type as per input file
 */

// Uncomment pixel data type
//typedef int pixeldatatype_t;
//typedef unsigned char pixeldatatype_t;
//typedef char pixeldatatype_t;
//typedef unsigned short pixeldatatype_t;
typedef short pixeldatatype_t;
//typedef float pixeldatatype_t;
//typedef double pixeldatatype_t;

/**
 * @brief image structure
 *
 */
typedef struct image {
	int width; /**< width of the image */
	int height; /**< height of the image */
	pixeldatatype_t * pixels; /**< pixels of the image */
} image_t;

/** @defgroup ImageFunc Image Functions
 *  Functions concerning image
 *  @{
 */
/** 
 * @brief Function: image_t * add_image (int width, int height)
 *
 * \param width:     width of the image
 * \param height:    height of the image
 * \return a pointer to an image structure
 *
 * Create and allocate memory for a new image
 */
image_t * add_image (int width, int height);

/**
 * @brief Function: void delete_image (image_t * img)
 *
 * \param img:  image to delete
 * 
 * Delete an image. Frees up memory as well.
 */
void delete_image (image_t * img);

// Set fields of image structure

/**
 * @brief Function: void set_width (image_t ** img, int width)
 *
 * \param img:    input image structure
 * \param width:  width of the image
 * 
 * Set the width of the image.
 */
void set_width (image_t ** img, int width);

/**
 * @brief Function: void set_height (image_t ** img, int height)
 *
 * \param img:    input image structure
 * \param height: height of the image
 * 
 * Set the height of the image.
 */
void set_height (image_t ** img, int height);

/**
 * @brief Function: void set_dimensions (image_t ** img, int width, int height)
 *
 * \param img:    input image structure
 * \param width:  width of the image
 * \param height: height of the image
 * 
 * Set the width and the height of the image.
 */
void set_dimensions (image_t ** img, int width, int height);

/**
 * @brief Function: void set_pixel (image_t ** img, pixeldatatype_t pixel, int x_pixel, int y_pixel)
 *
 * \param img:      input image structure 
 * \param pixel:    pixel of the image to add
 * \param x_pixel:  x coordinate of pixel to add
 * \param y_pixel:  y coordinate of pixel to add
 * 
 * Set a pixel of the image.
 */
void set_pixel (image_t ** img, pixeldatatype_t pixel, int x_pixel, int y_pixel);

/**
 * @brief Function: void set_pixel (image_t ** img, pixeldatatype_t* pixel)
 *
 * \param img:      input image structure 
 * \param pixel:    pixel of the image to add
 * 
 * Set pixels of the image.
 */
void set_img_pixels (image_t ** img, pixeldatatype_t * pixel);

// Get fields of image structure

/**
 * @brief Function: void get_width (image_t * img)
 *
 * \param img:    input image structure
 * \return the width of the image structure
 * 
 * Get the width of the image.
 */
int get_width (image_t * img);

/**
 * @brief Function: void get_height (image_t * img)
 *
 * \param img:    input image structure
 * \return the height of the image structure
 * 
 * Get the height of the image.
 */
int get_height (image_t * img);

/**
 * @brief Function: void get_img_pixels (image_t * img)
 *
 * \param img:    input image structure
 * \return the pixels of the image structure
 * 
 * Get an array of pixels of the image.
 */
pixeldatatype_t* get_img_pixels (image_t * img);

/**
 * @brief Function: void get_pixel (image_t * img, int x_pixel, int y_pixel)
 *
 * \param img:    input image structure
 * \param x_pixel:  x coordinate of pixel to return
 * \param y_pixel:  y coordinate of pixel to return
 * \return the pixel of the image structure at coordinates passed as input
 * 
 * Get a pixel of the image.
 */
pixeldatatype_t get_pixel (image_t * img, int x_pixel, int y_pixel);

/** @} */ // End of ImageFunc group
