#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAVE_SIZE 0x404
#define CHECKSUM_OFFSET 0x8

static char saveBuffer[SAVE_SIZE];

static inline FILE* openFile(const char* path) {
	FILE* file = fopen(path, "r+b");
	if (!file) printf("%s: %s\n", path, strerror(errno));

	return file;
}

static inline void fixCheckSum() {
	uint32_t* sumData = (uint32_t*)saveBuffer;
	sumData[CHECKSUM_OFFSET / sizeof(uint32_t)] = 0;

	uint32_t checksum = 0;
	for (size_t i = 0; i < SAVE_SIZE / sizeof(uint32_t); i++) {
		checksum += sumData[i];
	}

	sumData[CHECKSUM_OFFSET / sizeof(uint32_t)] = checksum;
}

void fixSaveFile(const char* filePath) {
	FILE* fileData = openFile(filePath);
	if (!fileData) return;

	fread(saveBuffer, sizeof(char), SAVE_SIZE, fileData);
	fixCheckSum();

	fseek(fileData, 0, SEEK_SET);
	fwrite(saveBuffer, sizeof(char), SAVE_SIZE, fileData);
	fclose(fileData);

	printf("%s: Success !!\n", filePath);
}

int main(int argc, const char** argv) {
	if (argc < 2) {
		printf("Usage : executable_name save1 {save2...}\n");
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++) {
		fixSaveFile(argv[i]);
	}

	return EXIT_SUCCESS;
}
