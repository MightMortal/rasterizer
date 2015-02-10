#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include "types.h"

Vec2i vec2i_sum(const Vec2i a, const Vec2i b);
Vec2f vec2f_sum(const Vec2f a, const Vec2f b);
Vec3i vec3i_sum(const Vec3i a, const Vec3i b);
Vec3f vec3f_sum(const Vec3f a, const Vec3f b);

Vec2i vec2i_neg(const Vec2i a);
Vec2f vec2f_neg(const Vec2f a);
Vec3i vec3i_neg(const Vec3i a);
Vec3f vec3f_neg(const Vec3f a);

Vec2i vec2i_norm(const Vec2i a);
Vec2f vec2f_norm(const Vec2f a);
Vec3i vec3i_norm(const Vec3i a);
Vec3f vec3f_norm(const Vec3f a);

double vec2i_mod(const Vec2i a);
double vec2f_mod(const Vec2f a);
double vec3i_mod(const Vec3i a);
double vec3f_mod(const Vec3f a);

Vec2i vec2i_muli(const Vec2i a, const int b);
Vec2f vec2f_muli(const Vec2f a, const int b);
Vec3i vec3i_muli(const Vec3i a, const int b);
Vec3f vec3f_muli(const Vec3f a, const int b);

Vec2i vec2i_mulf(const Vec2i a, const float b);
Vec2f vec2f_mulf(const Vec2f a, const float b);
Vec3i vec3i_mulf(const Vec3i a, const float b);
Vec3f vec3f_mulf(const Vec3f a, const float b);

int vec2i_dot(const Vec2i a, const Vec2i b);
int vec3i_dot(const Vec3i a, const Vec3i b);
double vec2f_dot(const Vec2f a, const Vec2f b);
double vec3f_dot(const Vec3f a, const Vec3f b);

Vec3i vec3i_cross(const Vec3i a, const Vec3i b);
Vec3f vec3f_cross(const Vec3f a, const Vec3f b);

#endif // _GEOMETRY_H_
