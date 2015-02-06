#include "targa.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	uint width;
	uint height;
	TgaColor* data;
} TgaImageS;

#pragma pack(push,1)
typedef struct {
	int8 id_long;
	int8 color_map_type;
	int8 image_type;
	int16 color_map_ind;
	int16 color_map_lng;
	int8 color_map_size;
	int16 image_off_x;
	int16 image_off_y;
	int16 image_w;
	int16 image_h;
	int8 image_bpp;
	int8 image_descriptor;
} TgaHeader;
typedef struct {
	int32 offset1;
	int32 offset2;
	char magic_word[18];
} TgaBasement;
#pragma pack(pop)

TgaImage tga_image_init(uint width, uint height) {
	// TODO: Checking allocations
	TgaImageS* image = malloc(sizeof(TgaImageS));
	image->height = height;
	image->width = width;
	image->data = calloc(height * width, sizeof(TgaColor));
	return image;
}

int tga_image_save(TgaImage image_p, const char* path) {
	FILE* f = fopen(path, "wb");
	TgaImageS* image = (TgaImageS*)image_p;
	TgaHeader header;
	memset(&header, 0, sizeof(TgaHeader));
	header.image_type = 2;
	header.image_w = image->width;
	header.image_h = image->height;
	header.image_bpp = 32;
	header.image_descriptor = 0x10; // b00010000
	TgaBasement basement;
	memset(&basement, 0, sizeof(TgaBasement));
	basement.magic_word[0] = 'T'; // "TRUEVISION-XFILE.";
	basement.magic_word[1] = 'R';
	basement.magic_word[2] = 'U';
	basement.magic_word[3] = 'E';
	basement.magic_word[4] = 'V';
	basement.magic_word[5] = 'I';
	basement.magic_word[6] = 'S';
	basement.magic_word[7] = 'I';
	basement.magic_word[8] = 'O';
	basement.magic_word[9] = 'N';
	basement.magic_word[10] = '-';
	basement.magic_word[11] = 'X';
	basement.magic_word[12] = 'F';
	basement.magic_word[13] = 'I';
	basement.magic_word[14] = 'L';
	basement.magic_word[15] = 'E';
	basement.magic_word[16] = '.';
	basement.magic_word[17] = '\0';

	int out = fwrite(&header, sizeof(TgaHeader), 1, f);
	if (out != 1) {
		return -1; // TODO: Error codes.
	}

	out = fwrite(image->data, sizeof(TgaColor), image->width * image->height, f);
	if (out != image->width * image->height) {
		return -1; // TODO: Error codes.
	}
	
	out = fwrite(&basement, sizeof(TgaBasement), 1, f);
	if (out != 1) {
		return -1; // TODO: Error codes.
	}

	fflush(f);
	fclose(f);

	return 0;
}

TgaImage tga_image_load(const char* path) {
	TgaHeader header;
	TgaBasement basement;
	FILE* f = fopen(path, "rb");
	int out = fread(&header, sizeof(TgaHeader), 1, f);
	if (out != 1) {
		return NULL; // TODO: Error codes.
	}
	TgaImageS* image = tga_image_init(header.image_w, header.image_h);
	out = fread(image->data, sizeof(TgaColor), image->width * image->height, f);
	if (out != image->width * image->height) {
		tga_image_close(image);
		return NULL; // TODO: Error codes.
	}

	fclose(f);

	return image;
}

void tga_image_close(TgaImage image_p) {
	TgaImageS* image = (TgaImageS*)image_p;
	free(image->data);
	free(image);
}

TgaColor tga_image_get_pixel(TgaImage image_p, uint x, uint y) {
	TgaImageS* image = (TgaImageS*)image_p;
	if (x >= image->width || y >= image->height) {
		return TGA_COLOR_ARGB(0x00, 0x00, 0x00, 0x00); // TODO: Print error
	}
	return image->data[y * image->width + x];
}

int tga_image_set_pixel(TgaImage image_p, uint x, uint y, TgaColor color) {
	TgaImageS* image = (TgaImageS*)image_p;
	if (x >= image->width || y >= image->height) {
		return -1; // TODO: Error codes.
	}
	image->data[y * image->width + x] = color;
	return 0;
}

uint tga_image_get_width(TgaImage image_p) {
	return ((TgaImageS*)image_p)->width;
}

uint tga_image_get_height(TgaImage image_p) {
	return ((TgaImageS*)image_p)->height;
}

void tga_image_get_size(TgaImage image_p, uint* width_o, uint* height_o) {
	TgaImageS* image = (TgaImageS*)image_p;
	*width_o = image->width;
	*height_o = image->height;
}