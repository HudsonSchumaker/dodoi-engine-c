/**
* @file de_program.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_program.h"

program_t* program_new(void) {
	program_t* program = (program_t*)malloc(sizeof(program_t));
	if (program == NULL) {
		fprintf(stderr, "failed to allocate memory for program.\n");
		exit(EXIT_FAILURE);
	}
	return program;
}

void program_init(program_t* program) {
	program->id = glCreateProgram();
}

