#ifndef _ASP_GL_H_
#define _ASP_GL_H_
#include "types.h"
#include "targa.h"

void asp_gl_draw_line(TgaImage image, int x0, int y0, int x1, int y1, Color color);
void asp_gl_draw_line_vec(TgaImage image, Vec2i p0, Vec2i p1, Color color);
void asp_gl_triangle(TgaImage image, Vec2i a, Vec2i b, Vec2i c, Color color);

#endif // _ASP_GL_H_