/**
* @file mesh.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_model.h"
#include "de_vector.h"

typedef struct {
	vec3_t* vertices;
	vec3_t* normals;
	tex2_t* uvs;
	face_t* faces;
	
	int vertex_count;
	int normal_count;
	int uv_count;
	int face_count;
} mesh_t;

mesh_t* mesh_new(void);
void mesh_load_obj(mesh_t* mesh, const char* path);
void mesh_delete(mesh_t* mesh);
