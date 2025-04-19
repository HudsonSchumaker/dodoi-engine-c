/**
* @file de_shader_manager.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"
#include "../../include/de_model.h"
#include "../../include/de_program.h"
#include "../../include/de_collection.h"
#include "../../include/de_shader_manager.h"

static bool shader_mgr_is_compiled(const char* name) {
	char* file_path = create_binary_path(name);
	return file_exists(file_path);
}

void shader_mgr_pre_compile(list_t* recipes) {
	for (size_t i = 0; i < recipes->size; ++i) {
		recipe_t* recipe = (recipe_t*)((char*)recipes->array + i * recipes->type_size);
		if (shader_mgr_is_compiled(recipe->name)) {
			continue;
		}

		program_t* program = program_new();
		char* binary_path = create_binary_path(recipe->name);
		char* vertex_shader_path = create_shader_path(recipe->vert);
		char* fragment_shader_path = create_shader_path(recipe->frag);

		program_compile(program, vertex_shader_path, fragment_shader_path);
		program_save_binary(program, binary_path);

		program_delete(program);
		free(program);
		free(binary_path);
		free(vertex_shader_path);
		free(fragment_shader_path);
	}
}
