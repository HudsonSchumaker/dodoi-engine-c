/**
* @file de_obj_loader.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2025, Dodoi-Lab
*/
#include "../../include/de_obj_loader.h"
#include "../../include/de_collection.h"

void obj_load(mesh_t* mesh, const char* path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		fprintf(stderr, "failed to open file: %s.\n", path);
		return;
	}

	list_t* vertices = NULL;
	list_init(&vertices, sizeof(vec3_t));

	list_t* normals = NULL;
	list_init(&normals, sizeof(vec3_t));

	list_t* uvs = NULL;
	list_init(&uvs, sizeof(tex2_t));

	list_t* faces = NULL;
	list_init(&faces, sizeof(face_t));

	char line[256];
	fseek(file, 0, SEEK_SET);
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "v ", 2) == 0) {
			vec3_t vertex;
			sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			list_add(&vertices, &vertex);
		}
		else if (strncmp(line, "vt ", 3) == 0) {
			tex2_t uv;
			sscanf_s(line, "vt %f %f", &uv.u, &uv.v);
			list_add(&uvs, &uv);
		}
		else if (strncmp(line, "vn ", 3) == 0) {
			vec3_t normal;
			sscanf_s(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			list_add(&normals, &normal);
		}

		else if (strncmp(line, "f ", 2) == 0) {
			face_t face;
			sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.vertex[0], &face.uv[0], &face.normal[0],
				&face.vertex[1], &face.uv[1], &face.normal[1],
				&face.vertex[2], &face.uv[2], &face.normal[2]);

			// Adjust for 1-based indexing
			for (byte i = 0; i < 3; i++) {
				face.vertex[i] -= 1;
				face.uv[i] -= 1;
				face.normal[i] -= 1;
			}
			list_add(&faces, &face);
		}
	}
	fclose(file);

	int vertex_count = list_size(&vertices);
	int normal_count = list_size(&normals);
	int uv_count     = list_size(&uvs);
	int face_count   = list_size(&faces);

	mesh->vertex_count = vertex_count;
	mesh->normal_count = normal_count;
	mesh->uv_count     = uv_count;
	mesh->face_count   = face_count;

	mesh->vertices = (vec3_t*)malloc(sizeof(vec3_t) * vertex_count);
	if (mesh->vertices == NULL) {
		fprintf(stderr, "Memory allocation failed for vertices.\n");
		return;
	}

	mesh->normals = (vec3_t*)malloc(sizeof(vec3_t) * normal_count);
	if (mesh->normals == NULL) {
		fprintf(stderr, "Memory allocation failed for normals.\n");
		return;
	}

	mesh->uvs = (tex2_t*)malloc(sizeof(tex2_t) * uv_count);
	if (mesh->uvs == NULL) {
		fprintf(stderr, "Memory allocation failed for uvs.\n");
		return;
	}

	mesh->faces = (face_t*)malloc(sizeof(face_t) * face_count);
	if (mesh->faces == NULL) {
		fprintf(stderr, "Memory allocation failed for faces.\n");
		return;
	}

	for (int i = 0; i < vertex_count; i++) {
		mesh->vertices[i] = *(vec3_t*)list_get(&vertices, i);
	}

	for (int i = 0; i < normal_count; i++) {
		mesh->normals[i] = *(vec3_t*)list_get(&normals, i);
	}

	for (int i = 0; i < uv_count; i++) {
		mesh->uvs[i] = *(tex2_t*)list_get(&uvs, i);
	}

	for (int i = 0; i < face_count; i++) {
		mesh->faces[i] = *(face_t*)list_get(&faces, i);
	}

	list_free(&vertices);
	list_free(&normals);
	list_free(&uvs);
	list_free(&faces);
}
