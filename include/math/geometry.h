#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <util/types.h>

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

Vec2i geom_vec2i_sum(const Vec2i a, const Vec2i b);
Vec2f geom_vec2f_sum(const Vec2f a, const Vec2f b);
Vec3i geom_vec3i_sum(const Vec3i a, const Vec3i b);
Vec3f geom_vec3f_sum(const Vec3f a, const Vec3f b);

Vec2i geom_vec2i_neg(const Vec2i a);
Vec2f geom_vec2f_neg(const Vec2f a);
Vec3i geom_vec3i_neg(const Vec3i a);
Vec3f geom_vec3f_neg(const Vec3f a);

Vec2i geom_vec2i_norm(const Vec2i a);
Vec2f geom_vec2f_norm(const Vec2f a);
Vec3i geom_vec3i_norm(const Vec3i a);
Vec3f geom_vec3f_norm(const Vec3f a);

double geom_vec2i_mod(const Vec2i a);
double geom_vec2f_mod(const Vec2f a);
double geom_vec3i_mod(const Vec3i a);
double geom_vec3f_mod(const Vec3f a);

Vec2i geom_vec2i_muli(const Vec2i a, const int b);
Vec2f geom_vec2f_muli(const Vec2f a, const int b);
Vec3i geom_vec3i_muli(const Vec3i a, const int b);
Vec3f geom_vec3f_muli(const Vec3f a, const int b);

Vec2i geom_vec2i_mulf(const Vec2i a, const float b);
Vec2f geom_vec2f_mulf(const Vec2f a, const float b);
Vec3i geom_vec3i_mulf(const Vec3i a, const float b);
Vec3f geom_vec3f_mulf(const Vec3f a, const float b);

int geom_vec2i_dot(const Vec2i a, const Vec2i b);
int geom_vec3i_dot(const Vec3i a, const Vec3i b);
double geom_vec2f_dot(const Vec2f a, const Vec2f b);
double geom_vec3f_dot(const Vec3f a, const Vec3f b);

Vec3i geom_vec3i_cross(const Vec3i a, const Vec3i b);
Vec3f geom_vec3f_cross(const Vec3f a, const Vec3f b);

Vec4f geom_vec4f_mul_mat4(const Vec4f v, const Mat4 mat);
Vec3f geom_vec3f_mul_mat3(const Vec3f v, const Mat3 mat);
Vec2f geom_vec2f_mul_mat2(const Vec2f v, const Mat2 mat);
Mat4  geom_mat4_mul_mat4(const Mat4 mat1, const Mat4 mat2);
Mat3  geom_mat3_mul_mat3(const Mat3 mat1, const Mat3 mat2);
Mat2  geom_mat2_mul_mat2(const Mat2 mat1, const Mat2 mat2);

Vec4f geom_vec3f_to_vec4f(const Vec3f v);
Vec3f geom_vec2f_to_vec3f(const Vec2f v);
Vec3f geom_vec4f_to_vec3f(const Vec4f v);
Vec2f geom_vec3f_to_vec2f(const Vec3f v);

Mat2 geom_mat2_identity();
Mat3 geom_mat3_identity();
Mat4 geom_mat4_identity();

#endif // _GEOMETRY_H_
