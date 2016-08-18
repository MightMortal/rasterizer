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
	Vec3f camera, up, target;
	camera.x = 7; camera.y = 13; camera.z = 35;
	up.x = 0; up.y = 1; up.z = 0;
	target.x = 0; target.y = 0; target.z = 0;

	Mat4 space_matrix = asp_gl_get_space_matrix(r);
	Mat4 view_matrix = asp_gl_camera_look_at(camera, up, target);
	Mat4 viewport_matrix = asp_gl_get_viewport_matrix(0, 0, WIDTH, HEIGHT);
	Vec3f light_dir;
	light_dir.x = 0.0;
	light_dir.y = 0.0;
	light_dir.z =-1.0;

	Mat4 tranform = view_matrix; // Applying camera position
	tranform = geom_mat4_mul_mat4(space_matrix, tranform); // Applying perspective projection
	tranform = geom_mat4_mul_mat4(viewport_matrix, tranform); // Applying screen projection

	printf("Start rendering\n");
	for (uint i = 0; i < wave_object_get_face_count(obj); ++i) {
		if (i % 10000 == 0 && i != 0)
			printf("drawed %d faces\n", i);

		WaveObjectFace *face = wave_object_get_face(obj, i);
		
		// Getting vertices coordinates
		Vec3f vs[3];
		vs[0] = *wave_object_get_v(obj, face->v[0]);
		vs[1] = *wave_object_get_v(obj, face->v[1]);
		vs[2] = *wave_object_get_v(obj, face->v[2]);
		Vec4f v1 = geom_vec3f_to_vec4f(vs[0]),
			  v2 = geom_vec3f_to_vec4f(vs[1]),
			  v3 = geom_vec3f_to_vec4f(vs[2]);

		double light_intens = asp_gl_flat_light_intens(vs, light_dir); // Calculated light intens using Flat shading
		if (light_intens <= 0.0) { // Backside culling
			continue;
		}
		
		// Getting texture coordinates
		Vec2f vtt[3];
		vtt[0] = *wave_object_get_vt(obj, face->vt[0]); 
		vtt[1] = *wave_object_get_vt(obj, face->vt[1]); 
		vtt[2] = *wave_object_get_vt(obj, face->vt[2]);

		// Applying all transformations
		v1 = geom_vec4f_mul_mat4(v1, tranform);
		v2 = geom_vec4f_mul_mat4(v2, tranform);
		v3 = geom_vec4f_mul_mat4(v3, tranform);

		// Pack into vectors array
		vs[0] = geom_vec4f_to_vec3f(v1);
		vs[1] = geom_vec4f_to_vec3f(v2);
		vs[2] = geom_vec4f_to_vec3f(v3);

		// Convert to int vectors array
		Vec3i vv[3];
		for (int i = 0; i < 3; i++) {
			vv[i].x = vs[i].x;
			vv[i].y = vs[i].y;
			vv[i].z = vs[i].z * 100;
		}

		asp_gl_triangle3D_textured(image, vv, vtt, light_intens, z_buffer, texture);
	}

	tga_image_save(image, "test.tga");
	system("pause");
	return 0;
}
