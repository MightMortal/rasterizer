#ifndef _TARGA_H_
#define _TARGA_H_

#include "types.h"

typedef void* TgaImage;

TgaImage tga_image_init(uint width, uint height);
int tga_image_save(TgaImage image, const char* path);
TgaImage tga_image_load(const char* path);
void tga_image_close(TgaImage image);

Color tga_image_get_pixel(TgaImage image, uint x, uint y);
int tga_image_set_pixel(TgaImage image, uint x, uint y, Color color);

uint tga_image_get_width(TgaImage image);
uint tga_image_get_height(TgaImage image);
void tga_image_get_size(TgaImage image, uint* width_o, uint* height_o);

#endif // _TARGA_H_