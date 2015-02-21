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
	TgaImage texture = tga_image_load("african_head_diffuse.tga");
	Buffer z_buffer = asp_gl_init_z_buffer(image);
	for (uint x = 0; x < width; ++x) {
		for (uint y = 0; y < height; ++y) {
			tga_image_set_pixel(image, x, y, COLOR_BLACK);
		}
	}
	double r = 5;
	Mat4 space_matrix;
	space_matrix.v[0][0] = 1; space_matrix.v[0][1] = 0; space_matrix.v[0][2] = 0   ; space_matrix.v[0][3] = 0;
	space_matrix.v[1][0] = 0; space_matrix.v[1][1] = 1; space_matrix.v[1][2] = 0   ; space_matrix.v[1][3] = 0;
	space_matrix.v[2][0] = 0; space_matrix.v[2][1] = 0; space_matrix.v[2][2] = 1   ; space_matrix.v[2][3] = 0;
	space_matrix.v[3][0] = 0; space_matrix.v[3][1] = 0; space_matrix.v[3][2] = -1./r; space_matrix.v[3][3] = 1;
	WaveObject obj = wave_object_load("head.obj");
	Vec3f light_dir;
	light_dir.x = 0.0;
	light_dir.y = 0.0;
	light_dir.z =-1.0;
	for (uint i = 0; i < wave_object_get_face_count(obj); ++i) {
		if (i % 10000 == 0 && i != 0)
			printf("drawed %d faces\n", i);
		WaveObjectFace *face = wave_object_get_face(obj, i);
		Vec3f *v1 = wave_object_get_v(obj, face->v[0]),
			  *v2 = wave_object_get_v(obj, face->v[1]),
			  *v3 = wave_object_get_v(obj, face->v[2]);
		Vec2f *vt1 = wave_object_get_vt(obj, face->vt[0]),
			  *vt2 = wave_object_get_vt(obj, face->vt[1]),
			  *vt3 = wave_object_get_vt(obj, face->vt[2]);
		Vec2f vtt[3];
		vtt[0] = *vt1; vtt[1] = *vt2; vtt[2] = *vt3;
		Vec4f v1f, v2f, v3f;
		v1f.x = v1->x; v1f.y = v1->y; v1f.z = v1->z; v1f.w = 1;
		v2f.x = v2->x; v2f.y = v2->y; v2f.z = v2->z; v2f.w = 1;
		v3f.x = v3->x; v3f.y = v3->y; v3f.z = v3->z; v3f.w = 1;
		
		v1f = geom_mul_vec4f_mat4(v1f, space_matrix);
		v2f = geom_mul_vec4f_mat4(v2f, space_matrix);
		v3f = geom_mul_vec4f_mat4(v3f, space_matrix);

		Vec3f vs[3];
		vs[0].x = v1f.x / (v1f.w);
		vs[1].x = v2f.x / (v2f.w);
		vs[2].x = v3f.x / (v3f.w);
		vs[0].y = v1f.y / (v1f.w);
		vs[1].y = v2f.y / (v2f.w);
		vs[2].y = v3f.y / (v3f.w);
		vs[0].z = v1f.z / (v1f.w);
		vs[1].z = v2f.z / (v2f.w);
		vs[2].z = v3f.z / (v3f.w);

		Vec3i vv[3];
		vv[0].x = (int)((vs[0].x + 1.) * width / 2.);
		vv[1].x = (int)((vs[1].x + 1.) * width / 2.);
		vv[2].x = (int)((vs[2].x + 1.) * width / 2.);
		vv[0].y = (int)((vs[0].y + 1.) * height / 2.);
		vv[1].y = (int)((vs[1].y + 1.) * height / 2.);
		vv[2].y = (int)((vs[2].y + 1.) * height / 2.);
		vv[0].z = vs[0].z * 100.;
		vv[1].z = vs[0].z * 100.;
		vv[2].z = vs[0].z * 100.;
		Vec3f n = vec3f_cross(vec3f_sum(*v3, vec3f_neg(*v1)), vec3f_sum(*v2, vec3f_neg(*v1)));
		n = vec3f_norm(n);
		double light_intens = vec3f_dot(n, light_dir);

		if (light_intens > 0) {
			asp_gl_triangle3D_textured(image, vv, vtt, light_intens, z_buffer, texture);
		}
	}

	tga_image_save(image, "test.tga");
	system("pause");
	return 0;
}
