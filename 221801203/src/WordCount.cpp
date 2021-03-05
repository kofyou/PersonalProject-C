#define _CRT_SECURE_NO_WARNINGS
#include "CountCore.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {

	if (argc != 3) {		// 参数个数必须为3 

		printf("Usage: %s [input_file] [output_file]\n", argv[0]);
		return 1;
	}

	wordcount(argv[1], argv[2]);

	return 0;
}

