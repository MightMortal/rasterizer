#include "asp_gl.h"
#include "macro.h"
#include <stdbool.h>
#include <math.h>

void asp_gl_draw_line(TgaImage image, int x0, int y0, int x1, int y1, TgaColor color) {
	bool vert = false;
	if (abs(y1 - y0) > abs(x1 - x0)) {
		SWAP_INT32(x0, y0);
		SWAP_INT32(x1, y1);
		vert = true;
	}
	if (x0 > x1) {
		SWAP_INT32(x0, x1);
		SWAP_INT32(y0, y1);
	}

	int dx = (x1 - x0);
	int k = 2 * abs(y1 - y0);
	int err = 0.0;
	int y = y0;
	for (int x = x0; x <= x1; ++x) {
		if (vert)
			tga_image_set_pixel(image, y, x, color);
		else
			tga_image_set_pixel(image, x, y, color);
		err += k;
		if (err >= dx) {
			y += (y1 > y0 ? 1 : -1);
			err -= 2 * dx;
		}
	}
}