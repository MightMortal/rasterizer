#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "targa.h"
#include "asp_gl.h"
#include "colors.h"
#include "wave_object.h"
#include "geometry.h"

int main(void) {
	const int width = 800, height = 800;
	TgaImage image = tga_image_init(width, height);
	for (uint x = 0; x < width; ++x) {
		for (uint y = 0; y < height; ++y) {
			tga_image_set_pixel(image, x, y, COLOR_BLACK);
		}
	}
	WaveObject obj = wave_object_load("african_head.obj");
	Vec3f light_dir;
	light_dir.x = 0.0;
	light_dir.y = 0.0;
	light_dir.z =-1.0;
	for (uint i = 0; i < wave_object_get_face_count(obj); ++i) {
		WaveObjectFace *face = wave_object_get_face(obj, i);
		Vec3f *v1 = wave_object_get_vertex(obj, face->v[0]),
			  *v2 = wave_object_get_vertex(obj, face->v[1]),
			  *v3 = wave_object_get_vertex(obj, face->v[2]);
		int x1 = (int)((v1->x + 1.) * width / 2.),
			x2 = (int)((v2->x + 1.) * width / 2.),
			x3 = (int)((v3->x + 1.) * width / 2.);
		int y1 = (int)((v1->y + 1.) * height / 2.),
			y2 = (int)((v2->y + 1.) * height / 2.),
			y3 = (int)((v3->y + 1.) * height / 2.);
		Vec3f n = vec3f_cross(vec3f_sum(*v3, vec3f_neg(*v1)), vec3f_sum(*v2, vec3f_neg(*v1)));
		n = vec3f_norm(n);
		double light_intens = vec3f_dot(n, light_dir);
		Vec2i a, b, c; a.x = x1; a.y = y1; b.x = x2; b.y = y2; c.x = x3; c.y = y3;
		if (light_intens > 0)
			asp_gl_triangle(image, a, b, c, COLOR_RGB((int)(light_intens * 255), (int)(light_intens * 255), (int)(light_intens * 255)));
	}

	tga_image_save(image, "test.tga");
	system("pause");
	return 0;
}
