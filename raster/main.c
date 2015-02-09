#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "targa.h"
#include "asp_gl.h"
#include "colors.h"

int main(void) {
	const int width = 200, height = 200;
	TgaImage image = tga_image_init(width, height);
	for (uint x = 0; x < width; ++x) {
		for (uint y = 0; y < height; ++y) {
			tga_image_set_pixel(image, x, y, COLOR_BLACK);
		}
	}
	Vec2i t0[3];
	t0[0].x = 10; t0[0].y = 70;
	t0[1].x = 50; t0[1].y = 160;
	t0[2].x = 70; t0[2].y = 80;
	
	Vec2i t1[3];
	t1[0].x = 180; t1[0].y = 50;
	t1[1].x = 150; t1[1].y = 1;
	t1[2].x = 70; t1[2].y = 180;
	
	Vec2i t2[3];
	t2[0].x = 180; t2[0].y = 150;
	t2[1].x = 120; t2[1].y = 160;
	t2[2].x = 130; t2[2].y = 180;

	asp_gl_triangle(image, t0[0], t0[1], t0[2], COLOR_RED);
	asp_gl_triangle(image, t1[0], t1[1], t1[2], COLOR_WHITE);
	asp_gl_triangle(image, t2[0], t2[1], t2[2], COLOR_GREEN);

	tga_image_save(image, "test.tga");
	system("pause");
	return 0;
}
