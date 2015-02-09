#ifndef _COLORS_H_
#define _COLORS_H_

#define COLOR_ARGB(a,r,g,b) (((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b) & 0xFF))
#define COLOR_RGB(r,g,b) (((0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b) & 0xFF))

#define COLOR_RED     (COLOR_RGB(0xFF, 0x00, 0x00))
#define COLOR_GREEN   (COLOR_RGB(0x00, 0xFF, 0x00))
#define COLOR_BLUE    (COLOR_RGB(0x00, 0x00, 0xFF))

#define COLOR_WHITE   (COLOR_RGB(0xFF, 0xFF, 0xFF))
#define COLOR_BLACK   (COLOR_RGB(0x00, 0x00, 0x00))

#define COLOR_MAGENTA (COLOR_RGB(0xFF, 0x00, 0xFF))
#define COLOR_CYAN    (COLOR_RGB(0x00, 0xFF, 0xFF))
#define COLOR_YELLOW  (COLOR_RGB(0xFF, 0xFF, 0x00))

#endif // _COLORS_H_
