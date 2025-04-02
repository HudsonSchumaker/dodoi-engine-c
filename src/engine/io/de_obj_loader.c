/**
* @file de_obj_loader.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2025, Dodoi-Lab
*/
#include "../../include/de_obj_loader.h"

void obj_load(mesh_t* mesh, const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "failed to open file: %s.\n", path);
        return;
    }

    char line[128];
    unsigned int vertex_count = 0, uv_count = 0, normal_count = 0, face_count = 0;

    // count the number of vertices, uvs, normals, and indices
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            vertex_count++;
        }
        else if (strncmp(line, "vt ", 3) == 0) {
            uv_count++;
        }
        else if (strncmp(line, "vn ", 3) == 0) {
            normal_count++;
        }
        else if (strncmp(line, "f ", 2) == 0) {
            face_count += 3; // triangles
        }
    }

    // allocate memory for mesh data
    mesh->vertices = (vec3_t*)malloc(vertex_count * sizeof(vec3_t));
    mesh->uvs     = (vec2_t*)malloc(uv_count * sizeof(vec2_t));
    mesh->normals = (vec3_t*)malloc(normal_count * sizeof(vec3_t));
    mesh->indices = (int*)malloc(face_count * sizeof(int));

    mesh->vertex_count = vertex_count;
    mesh->uv_count = uv_count;
    mesh->normal_count = normal_count;
    mesh->index_count = face_count;

	// reset counts for actual data
    vertex_count = 0;
    uv_count = 0;
    normal_count = 0;
    face_count = 0;

    // read the actual data
    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            sscanf_s(line, "v %f %f %f", &mesh->vertices[vertex_count].x, &mesh->vertices[vertex_count].y, &mesh->vertices[vertex_count].z);
            vertex_count++;
        }
        else if (strncmp(line, "vt ", 3) == 0) {
            sscanf_s(line, "vt %f %f", &mesh->uvs[uv_count].x, &mesh->uvs[uv_count].y);
            uv_count++;
        }
        else if (strncmp(line, "vn ", 3) == 0) {
            sscanf_s(line, "vn %f %f %f", &mesh->normals[normal_count].x, &mesh->normals[normal_count].y, &mesh->normals[normal_count].z);
            normal_count++;
        }
        else if (strncmp(line, "f ", 2) == 0) {
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            mesh->indices[face_count++] = vertexIndex[0] - 1;
            mesh->indices[face_count++] = vertexIndex[1] - 1;
            mesh->indices[face_count++] = vertexIndex[2] - 1;
        }
    }

    fclose(file);
}
