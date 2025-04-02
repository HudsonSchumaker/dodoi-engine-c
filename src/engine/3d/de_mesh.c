/**
* @file de_mesh.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_mesh.h"
#include "../../include/de_util.h"
#include "../../include/de_obj_loader.h"

mesh_t* mesh_new(void) {
	mesh_t* mesh = (mesh_t*)malloc(sizeof(mesh_t));
	if (mesh == NULL) {
		fprintf(stderr, "failed to allocate memory for mesh.\n");
		exit(EXIT_FAILURE);
	}
	return mesh;
}

void mesh_load_obj(mesh_t* mesh, const char* path) {
	char* mesh_path = create_model_path(path);
	obj_load(mesh, mesh_path);
}

void mesh_delete(mesh_t* mesh) {
	free(mesh->vertices);
	free(mesh->uvs);
	free(mesh->normals);
	free(mesh->indices);
	free(mesh);
}
