#ifndef _TARGA_H_
#define _TARGA_H_

#include "types.h"

typedef void* TgaImage;
typedef uint32 TgaColor;

#define TGA_COLOR_ARGB(a,r,g,b) (((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b) & 0xFF))
#define TGA_COLOR_RGB(r,g,b) (((0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b) & 0xFF))

TgaImage tga_image_init(uint width, uint height);
int tga_image_save(TgaImage image, const char* path);
TgaImage tga_image_load(const char* path);
void tga_image_close(TgaImage image);

TgaColor tga_image_get_pixel(TgaImage image, uint x, uint y);
int tga_image_set_pixel(TgaImage image, uint x, uint y, TgaColor color);

uint tga_image_get_width(TgaImage image);
uint tga_image_get_height(TgaImage image);
void tga_image_get_size(TgaImage image, uint* width_o, uint* height_o);

#endif // _TARGA_H_