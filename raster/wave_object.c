#include "wave_object.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct TWaveObjectS {
	DynList vertices;
	DynList faces;
} WaveObjectS;

WaveObject wave_object_load(char* path) {
	FILE* f = fopen(path, "r");
	if (!f) {
		return NULL;
	}
	WaveObjectS* obj = (WaveObjectS*)malloc(sizeof(WaveObjectS));
	obj->vertices = dynlist_init();
	obj->faces = dynlist_init();
	char buffer[16];
	fseek(f, 0, SEEK_END);
	size_t file_size = ftell(f);
	fseek(f, 0, SEEK_SET);
	while (ftell(f) != file_size) {
		fscanf(f, "%s", buffer);
		if (strcmp(buffer, "f") == 0) {
			WaveObjectFace* ff = (WaveObjectFace*)malloc(sizeof(WaveObjectFace));
			char buffer1[64], buffer2[64], buffer3[64];
			fscanf(f, "%s %s %s", buffer1, buffer2, buffer3);
			memset(ff->v, 0, sizeof(float)* 3);
			memset(ff->vt, 0, sizeof(float)* 3);
			memset(ff->vn, 0, sizeof(float)* 3);
			if (strstr(buffer1, "//") != NULL) {
				sscanf(buffer1, "%d//%d", &(ff->v[0]), &(ff->vn[0]));
				sscanf(buffer2, "%d//%d", &(ff->v[1]), &(ff->vn[1]));
				sscanf(buffer3, "%d//%d", &(ff->v[2]), &(ff->vn[2]));
			} else {
				sscanf(buffer1, "%d/%d/%d", &(ff->v[0]), &(ff->vt[0]), &(ff->vn[0]));
				sscanf(buffer2, "%d/%d/%d", &(ff->v[1]), &(ff->vt[1]), &(ff->vn[1]));
				sscanf(buffer3, "%d/%d/%d", &(ff->v[2]), &(ff->vt[2]), &(ff->vn[2]));
			}
			dynlist_push_back(obj->faces, ff);
		} else if (strcmp(buffer, "v") == 0) {
			Vec3f* v = (Vec3f*)malloc(sizeof(Vec3f));
			fscanf(f, "%lf %lf %lf", &(v->x), &(v->y), &(v->z));
			dynlist_push_back(obj->vertices, v);
		}
	}
	fclose(f);
	return obj;
}

Vec3f* wave_object_get_vertex(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((Vec3f*)dynlist_get_element(obj->vertices, index - 1));
}

uint wave_object_get_vertex_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->vertices);
}

WaveObjectFace* wave_object_get_face(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((WaveObjectFace*)dynlist_get_element(obj->faces, index));
}

uint wave_object_get_face_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->faces);
}

void wave_object_destroy(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	dynlist_destroy(obj->vertices);
	dynlist_destroy(obj->faces);
}
