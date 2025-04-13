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
	vertex_t* vertices; 
	face_t* faces;
	
	int vertex_count;
	int face_count;
} mesh_t;

mesh_t* mesh_new(void);
void mesh_load_obj(mesh_t* mesh, const char* path);
unsigned int* mesh_index_to_gl_buffer(mesh_t* mesh);
float* mesh_vertex_to_gl_buffer(mesh_t* mesh);
void mesh_delete(mesh_t* mesh);
