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

unsigned int* mesh_index_to_gl_buffer(mesh_t* mesh) {
	int face_count = mesh->face_count;
	unsigned int* buffer = (int*)malloc(sizeof(int) * face_count * 3);
	if (buffer == NULL) {
		fprintf(stderr, "failed to allocate memory for buffer.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < face_count; i++) {
		face_t* face = &mesh->faces[i];
		buffer[i * 3 + 0] = face->vertex[0];
		buffer[i * 3 + 1] = face->vertex[1];
		buffer[i * 3 + 2] = face->vertex[2];
	}
	return buffer;
}

float* mesh_vertex_to_gl_buffer(mesh_t* mesh) {
	int vertex_count = mesh->vertex_count;
	float* buffer = (float*)malloc(sizeof(float) * vertex_count * 8);
	if (buffer == NULL) {
		fprintf(stderr, "Failed to allocate memory for buffer.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < vertex_count; i++) {
		vertex_t* vertex = &mesh->vertices[i];
		buffer[i * 8 + 0] = vertex->position.x;
		buffer[i * 8 + 1] = vertex->position.y;
		buffer[i * 8 + 2] = vertex->position.z;
		buffer[i * 8 + 3] = vertex->normal.x;
		buffer[i * 8 + 4] = vertex->normal.y;
		buffer[i * 8 + 5] = vertex->normal.z;
		buffer[i * 8 + 6] = vertex->uv.u;
		buffer[i * 8 + 7] = vertex->uv.v;
	}
	return buffer;
}

void mesh_delete(mesh_t* mesh) {
	free(mesh->vertices);
	free(mesh->faces);
	free(mesh);
}
