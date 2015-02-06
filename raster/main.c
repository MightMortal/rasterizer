#include <stdio.h>
#include "types.h"
#include "targa.h"

int main(void) {
	TgaImage image = tga_image_init(100, 100);
	for (uint x = 0; x < 100; ++x) {
		for (uint y = 0; y < 100; ++y) {
			tga_image_set_pixel(image, x, y, TGA_COLOR_RGB(0x00, 0x00, 0x00));
		}
	}
	tga_image_save(image, "test.tga");
	
	return 0;
}