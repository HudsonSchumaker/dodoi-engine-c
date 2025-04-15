/**
* @file queue.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_collection.h"

#define Q_INIT_CAPACITY 64
#define Q_RESIZE_FACTOR 2

void queue_init(queue_t* queue, size_t type_size) {
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->capacity = Q_INIT_CAPACITY;
    queue->type_size = type_size;
    queue->array = malloc(queue->capacity * queue->type_size);
    if (!queue->array) {
        fprintf(stderr, "ERROR: queue_t, memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void queue_resize(queue_t* queue) {
    void* new_array = malloc(queue->capacity * Q_RESIZE_FACTOR * queue->type_size);
    if (new_array) {
        memcpy(new_array, queue->array, queue->size * queue->type_size);
        free(queue->array);
        queue->array = new_array;
        queue->capacity *= Q_RESIZE_FACTOR; // Update capacity after successful allocation
    }
    else {
        fprintf(stderr, "ERROR: queue_t, memory reallocation failed\n");
        return;
    }
}

void queue_add(queue_t* queue, void* value) {
    if (queue->size == queue->capacity) {
        queue_resize(queue);
    }
    memcpy((char*)queue->array + (queue->tail * queue->type_size), value, queue->type_size);
    queue->tail = (queue->tail + 1) % queue->capacity;  // Circular increment
    queue->size++;
}

void* queue_pool(queue_t* queue) {
    if (queue->size == 0) return NULL;
    void* value = (char*)queue->array + (queue->head * queue->type_size);
    queue->head = (queue->head + 1) % queue->capacity;  // Circular increment
    queue->size--;
    return value;
}

void* queue_peek(queue_t* queue) {
    if (queue->size == 0) return NULL;
    return (char*)queue->array + (queue->head * queue->type_size);
}

size_t queue_size(queue_t* queue) {
	return queue->size;
}

size_t queue_capacity(queue_t* queue) {
	return queue->capacity;
}

bool queue_is_empty(queue_t* queue) {
	return queue->size == 0;
}

void queue_clear(queue_t* queue) {
	queue->size = 0;
	queue->head = 0;
	queue->tail = 0;
}

void queue_free(queue_t* queue) {
    free(queue->array);
    queue->array = NULL;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->capacity = 0;
}
