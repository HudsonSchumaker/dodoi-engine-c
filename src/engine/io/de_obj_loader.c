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

	list_t positions, normals, uvs, vertices, faces;
	list_init(&positions, sizeof(vec3_t));
	list_init(&normals, sizeof(vec3_t));
	list_init(&uvs, sizeof(tex2_t));
	list_init(&vertices, sizeof(vertex_t));
	list_init(&faces, sizeof(face_t));

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "v ", 2) == 0) {
			vec3_t position;
			if (sscanf_s(line, "v %f %f %f", &position.x, &position.y, &position.z) == 3) {
				list_add(&positions, &position);
			}
		}
		else if (strncmp(line, "vt ", 3) == 0) {
			tex2_t uv;
			if (sscanf_s(line, "vt %f %f", &uv.u, &uv.v) == 2) {
				list_add(&uvs, &uv);
			}
		}
		else if (strncmp(line, "vn ", 3) == 0) {
			vec3_t normal;
			if (sscanf_s(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z) == 3) {
				list_add(&normals, &normal);
			}
		}
		else if (strncmp(line, "f ", 2) == 0) {
			face_t face;
			if (sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.vertex[0], &face.uv[0], &face.normal[0],
				&face.vertex[1], &face.uv[1], &face.normal[1],
				&face.vertex[2], &face.uv[2], &face.normal[2]) == 9) {
				for (int i = 0; i < 3; i++) {
					face.vertex[i] -= 1;  // Adjust for 1-based indexing
					face.uv[i] -= 1;
					face.normal[i] -= 1;

					// Create a vertex_t for each face vertex
					vertex_t vertex;
					vertex.position = *(vec3_t*)list_get(&positions, face.vertex[i]);
					vertex.normal = *(vec3_t*)list_get(&normals, face.normal[i]);
					vertex.uv = *(tex2_t*)list_get(&uvs, face.uv[i]);
					list_add(&vertices, &vertex);
				}
				list_add(&faces, &face);
			}
		}
	}
	fclose(file);

	int vertex_count = (int)list_size(&vertices);
	int normal_count = (int)list_size(&normals);
	int uv_count     = (int)list_size(&uvs);
	int face_count   = (int)list_size(&faces);

	// Transfer data to mesh
	mesh->vertex_count = vertex_count;
	mesh->face_count   = face_count;

	mesh->vertices = (vertex_t*)malloc(sizeof(vertex_t) * mesh->vertex_count);
	mesh->faces = (face_t*)malloc(sizeof(face_t) * mesh->face_count);
	if (mesh->vertices == NULL || mesh->faces == NULL) {
		fprintf(stderr, "failed to allocate memory for mesh vertices or faces.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < mesh->vertex_count; i++) {
		mesh->vertices[i] = *(vertex_t*)list_get(&vertices, i);
	}
	for (int i = 0; i < mesh->face_count; i++) {
		mesh->faces[i] = *(face_t*)list_get(&faces, i);
	}

	list_free(&positions);
	list_free(&normals);
	list_free(&uvs);
	list_free(&vertices);
	list_free(&faces);
}
