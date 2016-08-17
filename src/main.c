#include <util/types.h>
#include <io/targa.h>
#include <gl/asp_gl.h>
#include <gl/colors.h>
#include <io/wave_object.h>
#include <math/geometry.h>

#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 800, HEIGHT = 800;

int main(void) {
	printf("Loading diffuse texture...");
	TgaImage texture = tga_image_load("resources/african_head/african_head_diffuse.tga");
	if (texture == NULL) {
		printf("failed\n");
		return -1;
	} else {
		printf("complete\n");
	}
	
	printf("Loading wave form object...");
	WaveObject obj = wave_object_load("resources/african_head/african_head.obj");
	if (obj == NULL) {
		printf("failed\n");
		return -1;
	} else {
		printf("complete\n");
	}

	TgaImage image = tga_image_init(WIDTH, HEIGHT);
	for (uint x = 0; x < WIDTH; ++x) {
		for (uint y = 0; y < HEIGHT; ++y) {
			tga_image_set_pixel(image, x, y, COLOR_BLACK);
		}
	}
	Buffer z_buffer = asp_gl_init_z_buffer(image);
	
	double r = 5;
	Mat4 space_matrix = asp_gl_init_space_matrix(r);
	Vec3f light_dir;
	light_dir.x = 0.0;
	light_dir.y = 0.0;
	light_dir.z =-1.0;

	printf("Start rendering\n");
	for (uint i = 0; i < wave_object_get_face_count(obj); ++i) {
		if (i % 10000 == 0 && i != 0)
			printf("drawed %d faces\n", i);

		WaveObjectFace *face = wave_object_get_face(obj, i);
		
		// Getting vertices coordinates
		Vec3f *v1 = wave_object_get_v(obj, face->v[0]),
			  *v2 = wave_object_get_v(obj, face->v[1]),
			  *v3 = wave_object_get_v(obj, face->v[2]);
		
		// Getting texture coordinates
		Vec2f vtt[3];
		vtt[0] = *wave_object_get_vt(obj, face->vt[0]); 
		vtt[1] = *wave_object_get_vt(obj, face->vt[1]); 
		vtt[2] = *wave_object_get_vt(obj, face->vt[2]);

		// Applying perspective projection
		Vec3f vs[3];
		vs[0] = aps_gl_perspective_projection(*v1, space_matrix);
		vs[1] = aps_gl_perspective_projection(*v2, space_matrix);
		vs[2] = aps_gl_perspective_projection(*v3, space_matrix);

		// Convert to screen coordinates
		Vec3i vv[3];
		vv[0].x = (int)((vs[0].x + 1.) * WIDTH / 2.);
		vv[1].x = (int)((vs[1].x + 1.) * WIDTH / 2.);
		vv[2].x = (int)((vs[2].x + 1.) * WIDTH / 2.);
		vv[0].y = (int)((vs[0].y + 1.) * HEIGHT / 2.);
		vv[1].y = (int)((vs[1].y + 1.) * HEIGHT / 2.);
		vv[2].y = (int)((vs[2].y + 1.) * HEIGHT / 2.);
		vv[0].z = vs[0].z * 100.;
		vv[1].z = vs[0].z * 100.;
		vv[2].z = vs[0].z * 100.;

		double light_intens = asp_gl_flat_light_intens(vs, light_dir); // Calculated light intens using Flat shading
		if (light_intens > 0) { // Backside culling
			asp_gl_triangle3D_textured(image, vv, vtt, light_intens, z_buffer, texture);
		}
	}

	tga_image_save(image, "test.tga");
	system("pause");
	return 0;
}
