#include <util/utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void util_printStruct(void* data, int size) {
	char* char_data = data;
	printf("Addres: %p\n", data);
	printf("Data:");
	for (int i = 0; i < size; i++) {
		printf("%02X", char_data[i]);
	}
	printf("\n");
}