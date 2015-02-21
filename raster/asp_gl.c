#include "asp_gl.h"

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "macro.h"
#include "colors.h"

typedef struct TBufferS {
	uint width;
	uint height;
	int* buffer;
} BufferS;

Buffer asp_gl_init_z_buffer(TgaImage image) {
	BufferS* buffer = (BufferS*)malloc(sizeof(BufferS));
	tga_image_get_size(image, &(buffer->width), &(buffer->height));
	buffer->buffer = (int*)calloc(buffer->width * buffer->height, sizeof(int));
	for (int i = 0; i < buffer->width * buffer->height; ++i) {
		buffer->buffer[i] = INT_MIN;
	}
	return buffer;
}

void asp_gl_destroy_z_buffer(Buffer buffer_descripter) {
	BufferS* buffer = (BufferS*)buffer_descripter;
	buffer->width = 0;
	buffer->height = 0;
	free(buffer->buffer);
	free(buffer);
}

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
	int err = 0;
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

void asp_gl_triangle2D(TgaImage image, Vec2i t0, Vec2i t1, Vec2i t2, Color color) {
	if (t0.y == t1.y && t1.y == t2.y) return;
	if (t0.y > t1.y) SWAP_VEC2I(t0, t1);
	if (t0.y > t2.y) SWAP_VEC2I(t0, t2);
	if (t1.y > t2.y) SWAP_VEC2I(t1, t2);
	int xl, xr;
	float alpha, beta;
	for (int y = t0.y; y < t2.y; y++) {
		alpha = (float)(y - t0.y) / (t2.y - t0.y);
		xl = t0.x + (int)((t2.x - t0.x) * alpha);
		if (y < t1.y) {
			beta = (float)(y - t0.y) / (t1.y - t0.y);
			xr = t0.x + (int)((t1.x - t0.x) * beta);
		} else {
			beta = (float)(y - t1.y) / (t2.y - t1.y);
			xr = t1.x + (int)((t2.x - t1.x) * beta);
		}
		
		if (xr < xl) {
			SWAP_INT32(xl, xr);
		}

		for (int x = xl; x <= xr; x++) {
			tga_image_set_pixel(image, x, y, color);
		}
	}
}

void asp_gl_triangle3D(TgaImage image, Vec3i t0, Vec3i t1, Vec3i t2, Color color, Buffer z_buffer_descriptor) {
	if (t0.y == t1.y && t1.y == t2.y) return;
	BufferS* z_buffer = (BufferS*)z_buffer_descriptor;
	if (t0.y > t1.y) SWAP_VEC3I(t0, t1);
	if (t0.y > t2.y) SWAP_VEC3I(t0, t2);
	if (t1.y > t2.y) SWAP_VEC3I(t1, t2);
	int xl, xr, zl, zr;
	float alpha, beta;
	for (int y = t0.y; y < t2.y; y++) {
		alpha = (float)(y - t0.y) / (t2.y - t0.y);
		xl = t0.x + (int)((t2.x - t0.x) * alpha);
		zl = t0.z + (int)((t2.z - t0.z) * alpha);
		if (y < t1.y) {
			beta = (float)(y - t0.y) / (t1.y - t0.y);
			xr = t0.x + (int)((t1.x - t0.x) * beta);
			zr = t0.z + (int)((t1.z - t0.z) * beta);
		}
		else {
			beta = (float)(y - t1.y) / (t2.y - t1.y);
			xr = t1.x + (int)((t2.x - t1.x) * beta);
			zr = t1.z + (int)((t2.z - t1.z) * beta);
		}

		if (xr < xl) {
			SWAP_INT32(xl, xr);
			SWAP_INT32(zl, zr);
		}

		for (int x = xl; x <= xr; x++) {
			double phi = (xl == xr) ? 1. : (x - xl) / (xr - xl);
			int z = (int)zl + (phi * (zr - zr));
			if (x > z_buffer->width || x < 0 || y > z_buffer->height || y < 0)
				continue;
			if (z > z_buffer->buffer[x + y * z_buffer->width]) {
				tga_image_set_pixel(image, x, y, color);
				z_buffer->buffer[x + y * z_buffer->width] = z;
			}
			
		}
	}
}

void asp_gl_triangle3D_textured(TgaImage image, Vec3i* v, Vec2f* vt, double intense, Buffer z_buffer_descriptor, TgaImage texture) {
	if (v[0].y == v[1].y && v[1].y == v[2].y) return;
	intense = CLAMP(intense, 0.0, 1.0);
	BufferS* z_buffer = (BufferS*)z_buffer_descriptor;
	if (v[0].y > v[1].y) {
		SWAP_VEC3I(v[0], v[1]);
		SWAP_VEC2F(vt[0], vt[1]);
	}
	if (v[0].y > v[2].y) {
		SWAP_VEC3I(v[0], v[2]);
		SWAP_VEC2F(vt[0], vt[2]);
	}
	if (v[1].y > v[2].y) {
		SWAP_VEC3I(v[1], v[2]);
		SWAP_VEC2F(vt[1], vt[2]);
	}
	int xl, xr, zl, zr;
	Vec2f luv, ruv;
	float alpha, beta;
	for (int y = v[0].y; y < v[2].y; y++) {
		alpha = (float)(y - v[0].y) / (v[2].y - v[0].y);
		xl = v[0].x + (int)((v[2].x - v[0].x) * alpha);
		zl = v[0].z + (int)((v[2].z - v[0].z) * alpha);

		luv.x = vt[0].x + alpha * (vt[2].x - vt[0].x);
		luv.y = vt[0].y + alpha * (vt[2].y - vt[0].y);

		if (y < v[1].y) {
			beta = (float)(y - v[0].y) / (v[1].y - v[0].y);
			xr = v[0].x + (int)((v[1].x - v[0].x) * beta);
			zr = v[0].z + (int)((v[1].z - v[0].z) * beta);

			ruv.x = vt[0].x + beta * (vt[1].x - vt[0].x);
			ruv.y = vt[0].y + beta * (vt[1].y - vt[0].y);
		}
		else {
			beta = (float)(y - v[1].y) / (v[2].y - v[1].y);
			xr = v[1].x + (int)((v[2].x - v[1].x) * beta);
			zr = v[1].z + (int)((v[2].z - v[1].z) * beta);

			ruv.x = vt[1].x + beta * (vt[2].x - vt[1].x);
			ruv.y = vt[1].y + beta * (vt[2].y - vt[1].y);
		}

		if (xr < xl) {
			SWAP_INT32(xl, xr);
			SWAP_INT32(zl, zr);
			SWAP_VEC2F(luv, ruv);
		}

		for (int x = xl; x <= xr; x++) {
			double phi = (xl == xr) ? 1. : (double)(x - xl) / (xr - xl);
			int z = zl + (int)(phi * (zr - zl));
			Vec2f g;
			g.x = luv.x + phi * (ruv.x - luv.x);
			g.y = luv.y + phi * (ruv.y - luv.y);
			if (x > z_buffer->width || x < 0 || y > z_buffer->height || y < 0)
				continue;
			if (z > z_buffer->buffer[x + y * z_buffer->width]) {
				Vec2i texture_coord;
				texture_coord.y = (int)(tga_image_get_width(texture) * g.y);
				texture_coord.x = (int)(tga_image_get_height(texture) * g.x);
				Color col = tga_image_get_pixel(texture, texture_coord.x, texture_coord.y);
				// Color col = COLOR_RGB((int)(0xFF * intense), (int)(0xFF * intense), (int)(0xFF * intense));
				tga_image_set_pixel(image, x, y, color_mult(col, intense));
				z_buffer->buffer[x + y * z_buffer->width] = z;
			}
		}
	}
}
