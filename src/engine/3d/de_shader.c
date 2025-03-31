/**
* @file de_shader.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_shader.h"

shader_t* shader_new(void) {
	shader_t* shader = (shader_t*)malloc(sizeof(shader_t));
	if (shader == NULL) {
		fprintf(stderr, "failed to allocate memory for shader.\n");
		exit(EXIT_FAILURE);
	}
	return shader;
}

void shader_init_frag_shader(shader_t* shader) {
	shader->id = glCreateShader(GL_FRAGMENT_SHADER);
}

void shader_init_vert_shader(shader_t* shader) {
	shader->id = glCreateShader(GL_VERTEX_SHADER);
}

bool shader_compile(shader_t* shader, const GLchar* path) {
    const GLchar* source = shader_load_file(path);
    if (source == NULL) {
        fprintf(stderr, "failed to load shader: %s.\n", path);
        return false;
    }

    glShaderSource(shader->id, 1, &source, NULL);
    glCompileShader(shader->id);

    GLint result;
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        GLint info_log_length;
        glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &info_log_length);

        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader->id, info_log_length, NULL, info_log);

        fprintf(stderr, "failed to compile shader: %s.\n", info_log);
        free(info_log);
        return false;
    }

    return true;
}

void shader_delete(shader_t* shader) {
	glDeleteShader(shader->id);
}

void shader_destroy(shader_t* shader) {
	shader_delete(shader);
	free(shader);
}

char* shader_load_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "failed to open file: %s.\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "failed to allocate memory for file: %s.\n", path);
        fclose(file);
        return NULL;
    }

    size_t read_length = fread(buffer, 1, length + 1, file);
    buffer[read_length] = '\0';
    
    fclose(file);
    return buffer;
}
