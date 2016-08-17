#include <io/wave_object.h>

#include <util/list.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TWaveObjectS {
	DynList v;
	DynList f;
	DynList vn;
	DynList vt;
} WaveObjectS;

WaveObject wave_object_load(char* path) {
	FILE* f = fopen(path, "r");
	if (!f) {
		fprintf(stderr, "File not found file %s\n", path);
		return NULL;
	}
	WaveObjectS* obj = (WaveObjectS*)malloc(sizeof(WaveObjectS));
	obj->v = dynlist_init();
	obj->vn = dynlist_init();
	obj->vt = dynlist_init();
	obj->f = dynlist_init();
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
			dynlist_push_back(obj->f, ff);
		} else if (strcmp(buffer, "v") == 0) {
			Vec3f* v = (Vec3f*)malloc(sizeof(Vec3f));
			fscanf(f, "%lf %lf %lf", &(v->x), &(v->y), &(v->z));
			dynlist_push_back(obj->v, v);
		} else if (strcmp(buffer, "vt") == 0) {
			Vec2f* v = (Vec2f*)malloc(sizeof(Vec2f));
			fscanf(f, "%lf %lf", &(v->x), &(v->y));
			dynlist_push_back(obj->vt, v);
		} else if (strcmp(buffer, "vn") == 0) {
			Vec3f* v = (Vec3f*)malloc(sizeof(Vec3f));
			fscanf(f, "%lf %lf %lf", &(v->x), &(v->y), &(v->z));
			dynlist_push_back(obj->vn, v);
		}
	}
	fclose(f);
	return obj;
}

Vec3f* wave_object_get_v(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((Vec3f*)dynlist_get_element(obj->v, index - 1));
}

uint wave_object_get_v_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->v);
}

Vec3f* wave_object_get_vn(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((Vec3f*)dynlist_get_element(obj->vn, index - 1));
}

uint wave_object_get_vn_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->vn);
}

Vec2f* wave_object_get_vt(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((Vec2f*)dynlist_get_element(obj->vt, index - 1));
}

uint wave_object_get_vt_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->vt);
}

WaveObjectFace* wave_object_get_face(WaveObject obj_descriptor, uint index) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return ((WaveObjectFace*)dynlist_get_element(obj->f, index));
}

uint wave_object_get_face_count(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	return dynlist_size(obj->f);
}

void wave_object_destroy(WaveObject obj_descriptor) {
	WaveObjectS* obj = (WaveObjectS*)obj_descriptor;
	dynlist_destroy(obj->v);
	dynlist_destroy(obj->vn);
	dynlist_destroy(obj->vt);
	dynlist_destroy(obj->f);
}
