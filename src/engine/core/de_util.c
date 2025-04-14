/**
* @file util.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"

int sign(register float value) {
	return (value > 0) - (value < 0);
}

char* create_model_path(const char* model) {
	return concat(OBJ_FOLDER, model);
}
char* create_shader_path(const char* shader) {
	return concat(SHADER_FOLDER, shader);
}
char* create_texture_path(const char* texture) {
	return concat(IMAGE_FOLDER, texture);
}
char* create_binary_path(const char* binary) {
	return concat(BINARY_FOLDER, binary);
}

char* concat(const char* s1, const char* s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1); // +1 for the null-terminator
	
    if (!result) {
		fprintf(stderr, "failed to allocate memory for concat.\n");
		exit(EXIT_FAILURE);
	}

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}

bool file_exists(const char* path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
