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
	uint x, y;
} Vec2u;

typedef struct {
	double x, y;
} Vec2f;

typedef struct {
	int x, y, z;
} Vec3i;

typedef struct {
	uint x, y, z;
} Vec3u;

typedef struct {
	double x, y, z;
} Vec3f;

#endif // _TYPES_H_
