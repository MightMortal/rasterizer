#include <math/geometry.h>

#include <math.h>
#include <string.h>

Vec2i geom_vec2i_sum(const Vec2i a, const Vec2i b) {
	Vec2i c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

Vec2f geom_vec2f_sum(const Vec2f a, const Vec2f b) {
	Vec2f c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

Vec3i geom_vec3i_sum(const Vec3i a, const Vec3i b) {
	Vec3i c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vec3f geom_vec3f_sum(const Vec3f a, const Vec3f b) {
	Vec3f c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vec2i geom_vec2i_neg(const Vec2i a) {
	Vec2i c;
	c.x = -a.x;
	c.y = -a.y;
	return c;
}

Vec2f geom_vec2f_neg(const Vec2f a) {
	Vec2f c;
	c.x = -a.x;
	c.y = -a.y;
	return c;
}

Vec3i geom_vec3i_neg(const Vec3i a) {
	Vec3i c;
	c.x = -a.x;
	c.y = -a.y;
	c.z = -a.z;
	return c;
}

Vec3f geom_vec3f_neg(const Vec3f a) {
	Vec3f c;
	c.x = -a.x;
	c.y = -a.y;
	c.z = -a.z;
	return c;
}

Vec2i geom_vec2i_muli(const Vec2i a, const int b) {
	Vec2i c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

Vec2f geom_vec2f_muli(const Vec2f a, const int b) {
	Vec2f c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

Vec3i geom_vec3i_muli(const Vec3i a, const int b) {
	Vec3i c;
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	return c;
}

Vec3f geom_vec3f_muli(const Vec3f a, const int b) {
	Vec3f c;
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	return c;
}

Vec2i geom_vec2i_mulf(const Vec2i a, const float b) {
	Vec2i c;
	c.x = (int)(a.x * b);
	c.y = (int)(a.y * b);
	return c;
}

Vec2f geom_vec2f_mulf(const Vec2f a, const float b) {
	Vec2f c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

Vec3i geom_vec3i_mulf(const Vec3i a, const float b) {
	Vec3i c;
	c.x = (int)(a.x * b);
	c.y = (int)(a.y * b);
	c.z = (int)(a.z * b);
	return c;
}

Vec3f geom_vec3f_mulf(const Vec3f a, const float b) {
	Vec3f c;
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	return c;
}

int geom_vec2i_dot(const Vec2i a, const Vec2i b) {
	int res = 0;
	res = a.x * b.x + a.y * b.y;
	return res;
}

int geom_vec3i_dot(const Vec3i a, const Vec3i b) {
	int res = 0;
	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return res;
}

double geom_vec2f_dot(const Vec2f a, const Vec2f b) {
	double res = 0;
	res = a.x * b.x + a.y * b.y;
	return res;
}

double geom_vec3f_dot(const Vec3f a, const Vec3f b) {
	double res = 0;
	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return res;
}


Vec3i geom_vec3i_cross(const Vec3i a, const Vec3i b) {
	Vec3i res;
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

Vec3f geom_vec3f_cross(const Vec3f a, const Vec3f b) {
	Vec3f res;
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

Vec2i geom_vec2i_norm(const Vec2i a) {
	Vec2i b;
	double m = geom_vec2i_mod(a);
	b.x = (int)(a.x / m);
	b.y = (int)(a.y / m);
	return b;
}

Vec2f geom_vec2f_norm(const Vec2f a) {
	Vec2f b;
	double m = geom_vec2f_mod(a);
	b.x = a.x / m;
	b.y = a.y / m;
	return b;
}

Vec3i geom_vec3i_norm(const Vec3i a) {
	Vec3i b;
	double m = geom_vec3i_mod(a);
	b.x = (int)(a.x / m);
	b.y = (int)(a.y / m);
	b.z = (int)(a.z / m);
	return b;
}

Vec3f geom_vec3f_norm(const Vec3f a) {
	Vec3f b;
	double m = geom_vec3f_mod(a);
	b.x = a.x / m;
	b.y = a.y / m;
	b.z = a.z / m;
	return b;
}

double geom_vec2i_mod(const Vec2i a) {
	return sqrt(a.x * a.x * 1. + a.y * a.y * 1.);
}

double geom_vec2f_mod(const Vec2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

double geom_vec3i_mod(const Vec3i a) {
	return sqrt(a.x * a.x * 1. + a.y * a.y * 1. + a.z * a.z * 1.);
}

double geom_vec3f_mod(const Vec3f a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vec4f geom_vec4f_mul_mat4(const Vec4f v, const Mat4 mat) {
	Vec4f result;
	result.x = v.x * mat.v[0][0] + v.y * mat.v[0][1] + v.z * mat.v[0][2] + v.w * mat.v[0][3];
	result.y = v.x * mat.v[1][0] + v.y * mat.v[1][1] + v.z * mat.v[1][2] + v.w * mat.v[1][3];
	result.z = v.x * mat.v[2][0] + v.y * mat.v[2][1] + v.z * mat.v[2][2] + v.w * mat.v[2][3];
	result.w = v.x * mat.v[3][0] + v.y * mat.v[3][1] + v.z * mat.v[3][2] + v.w * mat.v[3][3];
	return result;
}

Vec3f geom_vec3f_mul_mat3(const Vec3f v, const Mat3 mat) {
	Vec3f result;
	result.x = v.x * mat.v[0][0] + v.y * mat.v[0][1] + v.z * mat.v[0][2];
	result.y = v.x * mat.v[1][0] + v.y * mat.v[1][1] + v.z * mat.v[1][2];
	result.z = v.x * mat.v[2][0] + v.y * mat.v[2][1] + v.z * mat.v[2][2];
	return result;
}

Vec2f geom_vec2f_mul_mat2(const Vec2f v, const Mat2 mat) {
	Vec2f result;
	result.x = v.x * mat.v[0][0] + v.y * mat.v[0][1];
	result.y = v.x * mat.v[1][0] + v.y * mat.v[1][1];
	return result;
}

Mat4 geom_mat4_mul_mat4(const Mat4 mat1, const Mat4 mat2) {
	Mat4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.v[i][j] = mat1.v[i][0] * mat2.v[0][j] + mat1.v[i][1] * mat2.v[1][j] + mat1.v[i][2] * mat2.v[2][j] + mat1.v[i][3] * mat2.v[3][j];
		}
	}
	return result;
}

Mat3 geom_mat3_mul_mat3(const Mat3 mat1, const Mat3 mat2) {
	Mat3 result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.v[i][j] = mat1.v[i][0] * mat2.v[0][j] + mat1.v[i][1] * mat2.v[1][j] + mat1.v[i][2] * mat2.v[2][j];
		}
	}
	return result;
}

Mat2 geom_mat2_mul_mat2(const Mat2 mat1, const Mat2 mat2) {
	Mat2 result;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			result.v[i][j] = mat1.v[i][0] * mat2.v[0][j] + mat1.v[i][1] * mat2.v[1][j];
		}
	}
	return result;
}

Vec4f geom_vec3f_to_vec4f(const Vec3f v) {
	Vec4f result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	result.w = 1.0;
	return result;
}

Vec3f geom_vec2f_to_vec3f(const Vec2f v) {
	Vec3f result;
	result.x = v.x;
	result.y = v.y;
	result.z = 1.0;
	return result;
}

Vec3f geom_vec4f_to_vec3f(const Vec4f v) {
	Vec3f result;
	result.x = v.x / v.w;
	result.y = v.y / v.w;
	result.z = v.z / v.w;
	return result;
}

Vec2f geom_vec3f_to_vec2f(const Vec3f v) {
	Vec2f result;
	result.x = v.x / v.z;
	result.y = v.y / v.z;
	return result;
}

Mat2 geom_mat2_identity() {
	Mat2 result;
	memset(&result, 0, sizeof(result));
	for (int i = 0; i < 2; i++) {
		result.v[i][i] = 1;
	}
	return result;
}

Mat3 geom_mat3_identity() {
	Mat3 result;
	memset(&result, 0, sizeof(result));
	for (int i = 0; i < 3; i++) {
		result.v[i][i] = 1;
	}
	return result;
}

Mat4 geom_mat4_identity() {
	Mat4 result;
	memset(&result, 0, sizeof(result));
	for (int i = 0; i < 4; i++) {
		result.v[i][i] = 1;
	}
	return result;
}
