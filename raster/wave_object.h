#ifndef _WAVE_OBJECT_H_
#define _WAVE_OBJECT_H_
#include "types.h"

typedef void* WaveObject;

typedef struct TWaveObjectFace {
	uint v[3];
	uint vt[3];
	uint vn[3];
} WaveObjectFace;

WaveObject wave_object_load(char* path);
Vec3f* wave_object_get_vertex(WaveObject obj, uint index);
uint wave_object_get_vertex_count(WaveObject obj);
WaveObjectFace* wave_object_get_face(WaveObject obj, uint index);
uint wave_object_get_face_count(WaveObject obj);
void wave_object_destroy(WaveObject obj);

#endif // _WAVE_OBJECT_H_
