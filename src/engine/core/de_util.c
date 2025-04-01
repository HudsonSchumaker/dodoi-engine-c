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
