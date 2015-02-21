#ifndef _TYPES_H_
#define _TYPES_H_

typedef   signed char  int8;
typedef unsigned char uint8;

typedef   signed short  int16;
typedef unsigned short uint16;

typedef   signed int  int32;
typedef unsigned int uint32;
typedef unsigned int uint;

typedef   signed long long  int64;
typedef unsigned long long uint64;

typedef uint32 Color;

typedef struct {
	int x, y;
} Vec2i;

typedef struct {
	double x, y;
} Vec2f;

typedef struct {
	int x, y, z;
} Vec3i;

typedef struct {
	double x, y, z;
} Vec3f;

typedef struct {
	int x, y, z, w;
} Vec4i;

typedef struct {
	double x, y, z, w;
} Vec4f;

typedef struct {
	double v[2][2];
} Mat2;

typedef struct {
	double v[3][3];
} Mat3;

typedef struct {
	double v[4][4];
} Mat4;

#endif // _TYPES_H_
