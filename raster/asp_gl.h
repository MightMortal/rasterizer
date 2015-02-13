#ifndef _ASP_GL_H_
#define _ASP_GL_H_
#include "types.h"
#include "targa.h"

typedef void* Buffer;

Buffer asp_gl_init_z_buffer(TgaImage image);
void asp_gl_destroy_z_buffer(Buffer buffer);
void asp_gl_draw_line(TgaImage image, int x0, int y0, int x1, int y1, Color color);
void asp_gl_draw_line_vec(TgaImage image, Vec2i p0, Vec2i p1, Color color);
void asp_gl_triangle2D(TgaImage image, Vec2i t0, Vec2i t1, Vec2i t2, Color color);
void asp_gl_triangle3D(TgaImage image, Vec3i t0, Vec3i t1, Vec3i t2, Color color, Buffer z_buffer);

#endif // _ASP_GL_H_
