/**
* @file collection.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    void* array;
    size_t size;
    size_t capacity;
    size_t type_size;
} list_t;

typedef struct {
    void* array;
    size_t size;
    size_t capacity;
    size_t type_size;
    int (*equals)(const void*, const void*); // Comparison function to detect duplicates
} set_t;

typedef struct {
    void* array;        
    size_t size;       
    size_t head;      
    size_t tail;       
    size_t capacity;   
    size_t type_size; 
} queue_t;

// List functions
void list_init(list_t* list, size_t type_size);
void list_init_size(list_t* list, size_t type_size, size_t reserve);
void list_add(list_t* list, void* value);
void* list_get(list_t* list, size_t index);
size_t list_size(list_t* list);
size_t list_capacity(list_t* list);
bool list_is_empty(list_t* list);
void list_clear(list_t* list);
void list_remove(list_t* list, size_t index);
void list_resize(list_t* list, size_t new_capacity);
void list_free(list_t* list);

// Set functions
void set_init(set_t* set, size_t type_size, int (*equals)(const void*, const void*));
void set_init_size(set_t* set, size_t type_size, size_t reserve, int (*equals)(const void*, const void*));
void set_add(set_t* set, void* value);
void* set_get(set_t* set, size_t index);
bool set_contains(set_t* set, void* value);

// Equality functions
int set_equals_int(const void* a, const void* b);
int set_equals_float(const void* a, const void* b);
int set_equals_double(const void* a, const void* b);
int set_equals_string(const void* a, const void* b);
int set_equals_vec2(const void* a, const void* b);
int set_equals_vec3(const void* a, const void* b);
int set_equals_vec4(const void* a, const void* b);
int set_equals_color(const void* a, const void* b);
int set_equals_tex2(const void* a, const void* b);
int set_equals_ipair(const void* a, const void* b);
int set_equals_fpair(const void* a, const void* b);
int set_equals_bpair(const void* a, const void* b);
int set_equals_itriple(const void* a, const void* b);
int set_equals_ftriple(const void* a, const void* b);
int set_equals_vertex(const void* a, const void* b);
void set_free(set_t* set);

// Queue functions
void queue_init(queue_t* queue, size_t type_size);
void queue_add(queue_t* queue, void* value);
void* queue_pool(queue_t* queue);
void* queue_peek(queue_t* queue);
size_t queue_size(queue_t* queue);
size_t queue_capacity(queue_t* queue);
bool queue_is_empty(queue_t* queue);
void queue_clear(queue_t* queue);
void queue_free(queue_t* queue);
