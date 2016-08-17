#ifndef _WAVE_OBJECT_H_
#define _WAVE_OBJECT_H_

#include <util/types.h>
#include <math/geometry.h>

typedef void* WaveObject;

typedef struct TWaveObjectFace {
	uint v[3];
	uint vt[3];
	uint vn[3];
} WaveObjectFace;

WaveObject wave_object_load(char* path);

Vec3f* wave_object_get_v(WaveObject obj, uint index);
uint wave_object_get_v_count(WaveObject obj);

Vec3f* wave_object_get_vn(WaveObject obj, uint index);
uint wave_object_get_vn_count(WaveObject obj);

Vec2f* wave_object_get_vt(WaveObject obj, uint index);
uint wave_object_get_vt_count(WaveObject obj);

WaveObjectFace* wave_object_get_face(WaveObject obj, uint index);
uint wave_object_get_face_count(WaveObject obj);

void wave_object_destroy(WaveObject obj);

#endif // _WAVE_OBJECT_H_
