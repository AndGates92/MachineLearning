/**
 * @copyright
 * @file image.c
 * @author Andrea Gianarda
 * @date 16th of October 2018
 * @brief Function body handling images
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "log.h"
#include "image.h"

image_t * add_image (int width, int height) {
	image_t * img = NULL;

	img = (image_t *) malloc(sizeof(image_t));
	if (img==NULL) {
		LOG_ERROR("Can't allocate memory for a new image img at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}
	img->width = width;
	img->height = height;
	img->pixels = NULL;
	img->pixels = (pixeldatatype_t *) malloc(width*height*sizeof(pixeldatatype_t));
	if (img->pixels==NULL) {
		LOG_ERROR("Can't allocate memory for pixels of image img at %s, function %s, line %0d\n", __FILE__, __func__, __LINE__);
	}

	return img;
}

void delete_image (image_t * img) {
	free(img->pixels);
	log_info("Free image pixels -> COMPLETED\n");
	free(img);
	log_info("Free image structure -> COMPLETED\n");
}

void set_width (image_t ** img, int width) {
	(*img)->width = width;
	log_info("Set image width to %0d\n", width);
}

void set_height (image_t ** img, int height) {
	(*img)->height = height;
	log_info("Set image height to %0d\n", height);
}

void set_dimensions (image_t ** img, int width, int height) {
	(*img)->width = width;
	log_info("Set image width to %0d\n", width);
	(*img)->height = height;
	log_info("Set image height to %0d\n", height);
}

void set_pixel (image_t ** img, pixeldatatype_t pixel, int x_pixel, int y_pixel) {
	int img_width = get_width(*img);
	assert(x_pixel < img_width);
	int img_height = get_height(*img);
	assert(y_pixel < img_height);
	int pixel_no = (x_pixel*img_width+y_pixel);
	(*img)->pixels[pixel_no] = pixel;
	log_info("Set image pixel(%0d,%0d) : %0lf\n", x_pixel, y_pixel, (double)pixel);
}

void set_img_pixels (image_t ** img, pixeldatatype_t * pixel) {
	(*img)->pixels = pixel;
	#ifdef VERBOSE
		int img_width = get_width(*img);
		int img_height = get_height(*img);
		int tot_pixel = (x_pixel*y_pixel);
		int x_pixel=0;
		int y_pixel=0;
		for (int i=0; i<tot_pixel; i++) {
			x_pixel = (int)(i % img_width);
			y_pixel = (int)(i/img_width);
			log_info("Set image pixel(%0d,%0d) : %0lf\n", x_pixel, y_pixel, (double)(*(pixel+i)));
		}
	#endif // VERBOSE
}

int get_width (image_t * img) {
	log_info("image width: %0d\n", img->width);
	return img->width;
}

int get_height (image_t * img) {
	log_info("image height: %0d\n", img->height);
	return img->height;
}

pixeldatatype_t get_pixel (image_t * img, int x_pixel, int y_pixel) {
	int img_width = get_width(img);
	assert(x_pixel < img_width);
	int img_height = get_height(img);
	assert(y_pixel < img_height);
	int pixel_no = (x_pixel*img_width+y_pixel);
	pixeldatatype_t pixel = img->pixels[pixel_no];
	log_info("Image pixel(%0d,%0d) : %0lf\n", x_pixel, y_pixel, (double)(pixel));
	return pixel;
}

pixeldatatype_t * get_img_pixels (image_t * img) {
	#ifdef VERBOSE
		int img_width = get_width(img);
		int img_height = get_height(img);
		int tot_pixel = (x_pixel*y_pixel);
		int x_pixel=0;
		int y_pixel=0;
		for (int i=0; i<tot_pixel; i++) {
			x_pixel = (int)(i % img_width);
			y_pixel = (int)(i/img_width);
			log_info("Image pixel(%0d,%0d) : %0lf\n", x_pixel, y_pixel, (double)(img->(*(pixels+i))));
		}
	#endif // VERBOSE

	return img->pixels;
}
