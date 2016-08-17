#include <gl/colors.h>

#include <util/macro.h>

Color color_mix(Color col1, Color col2) {
	uint8 col1a = ((col1 >> 24) & 0xFF);
	uint8 col1b = (col1 & 0xFF) * 0.5 * col1a / 255.;
	uint8 col1g = ((col1 >> 8) & 0xFF) * 0.5 * col1a / 255.;
	uint8 col1r = ((col1 >> 16) & 0xFF) * 0.5 * col1a / 255.;

	uint8 col2a = ((col2 >> 24) & 0xFF);
	uint8 col2b = (col2 & 0xFF) * 0.5 * col2a / 255.;
	uint8 col2g = ((col2 >> 8) & 0xFF) * 0.5 * col2a / 255.;
	uint8 col2r = ((col2 >> 16) & 0xFF) * 0.5 * col2a / 255.;
	return COLOR_ARGB(col1a + col2a, col1r + col2r, col1g + col2g, col1b + col2b);
}

Color color_mult(Color col1, double m) {
	m = CLAMP(m, 0.0, 1.0);
	uint8 col1b = (col1 & 0xFF) * m;
	uint8 col1g = ((col1 >> 8) & 0xFF) * m;
	uint8 col1r = ((col1 >> 16) & 0xFF) * m;
	uint8 col1a = ((col1 >> 24) & 0xFF);
	return COLOR_ARGB(col1a, col1r, col1g, col1b);
}
