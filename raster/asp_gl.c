#include "asp_gl.h"

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "macro.h"
#include "colors.h"

void asp_gl_draw_line(TgaImage image, int x0, int y0, int x1, int y1, Color color) {
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

void asp_gl_draw_line_vec(TgaImage image, Vec2i p0, Vec2i p1, Color color) {
	asp_gl_draw_line(image, p0.x, p0.y, p1.x, p1.y, color);
}

void asp_gl_triangle(TgaImage image, Vec2i a, Vec2i b, Vec2i c, Color color) {
	if (a.y == b.y && b.y == c.y) return;
	if (a.y > b.y) SWAP_VEC2I(a, b);
	if (a.y > c.y) SWAP_VEC2I(a, c);
	if (b.y > c.y) SWAP_VEC2I(b, c);
	int xl, xr;
	float alpha, beta;
	for (int y = a.y; y <= c.y; y++) {
		alpha = (float)(y - a.y) / (c.y - a.y);
		xl = a.x + (int)((c.x - a.x) * alpha);
		if (y < b.y) {
			beta = (float)(y - a.y) / (b.y - a.y);
			xr = a.x + (int)((b.x - a.x) * beta);
		} else {
			beta = (float)(y - b.y) / (c.y - b.y);
			xr = b.x + (int)((c.x - b.x) * beta);
		}
		
		if (xr < xl) {
			SWAP_INT32(xl, xr);
		}

		for (int x = xl; x <= xr; x++) {
			tga_image_set_pixel(image, x, y, color);
		}
	}
}