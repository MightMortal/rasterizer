#include <stdio.h>
#include "types.h"
#include "targa.h"

int main(void) {
	printf("Hello World!\n");
	TgaImage image = tga_image_init(100, 100);
	for (uint x = 0; x < 100; ++x) {
		for (uint y = 0; y < 100; ++y) {
			tga_image_set_pixel(image, x, y, TGA_COLOR_RGB(0xFF, 0x00, 0xFF));
		}
	}
	tga_image_save(image, "test.tga");
	return 0;
}