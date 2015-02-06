#include <stdio.h>
#include "types.h"
#include "targa.h"
#include "asp_gl.h"

int main(void) {
	TgaImage image = tga_image_init(100, 100);
	for (uint x = 0; x < 100; ++x) {
		for (uint y = 0; y < 100; ++y) {
			tga_image_set_pixel(image, x, y, TGA_COLOR_RGB(0x00, 0x00, 0x00));
		}
	}
	asp_gl_draw_line(image, 13, 20, 80, 40, TGA_COLOR_RGB(0xFF, 0xFF, 0xFF));
	asp_gl_draw_line(image, 20, 13, 40, 80, TGA_COLOR_RGB(0xFF, 0x00, 0x00));
	asp_gl_draw_line(image, 80, 20, 13, 40, TGA_COLOR_RGB(0xFF, 0x00, 0x00));

	tga_image_save(image, "test.tga");
	
	return 0;
}