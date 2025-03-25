/**
* @file de_program.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_program.h"

program_t* program_new(void) {
	program_t* program = (program_t*)malloc(sizeof(program_t));
	if (program == NULL) {
		fprintf(stderr, "failed to allocate memory for program.\n");
		exit(EXIT_FAILURE);
	}
	return program;
}

void program_init(program_t* program) {
	program->id = glCreateProgram();
}

bool program_compile(program_t* program, const GLchar* vertex_path, const GLchar* fragment_path) {
	shader_t* vertex_shader = shader_new();
	shader_t* fragment_shader = shader_new();
	shader_init_vert_shader(vertex_shader);
	shader_init_frag_shader(fragment_shader);

	if (!shader_compile(vertex_shader, vertex_path)) {
		fprintf(stderr, "failed to compile vertex shader.\n");
		return false;
	}
	if (!shader_compile(fragment_shader, fragment_path)) {
		fprintf(stderr, "failed to compile fragment shader.\n");
		return false;
	}
	if (!program_link(program, vertex_shader, fragment_shader)) {
		fprintf(stderr, "failed to link program.\n");
		return false;
	}

	program_detach_shader(program, vertex_shader);
	program_detach_shader(program, fragment_shader);
	shader_delete(vertex_shader);
	shader_delete(fragment_shader);
	return true;
}

bool program_link(program_t* program, shader_t* vertex_shader, shader_t* fragment_shader) {
	glAttachShader(program->id, vertex_shader->id);
	glAttachShader(program->id, fragment_shader->id);
	glLinkProgram(program->id);
	
	GLint result;
	glGetProgramiv(program->id, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		GLint info_log_length;
		glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, &info_log_length);
		GLchar* info_log = malloc(info_log_length);
		glGetProgramInfoLog(program->id, info_log_length, NULL, info_log);
		fprintf(stderr, "failed to link program: %s.\n", info_log);
		free(info_log);
		return false;
	}
	return true;
}

void program_set(program_t* program) {
	glUseProgram(program->id);
}

void program_unset(void) {
	glUseProgram(0);
}

void program_delete(program_t* program) {
	glDeleteProgram(program->id);
}

void program_destroy(program_t* program) {
	program_delete(program);
	free(program);
}

void program_detach_shader(program_t* program, shader_t* shader) {
	glDetachShader(program->id, shader->id);
}

GLint program_get_uniform_location(program_t* program, const GLchar* name) {
	return glGetUniformLocation(program->id, name);
}

void program_set_uniform1i(GLint location, GLint value) {
	glUniform1i(location, value);
}

void program_set_uniform1f(GLint location, GLfloat value) {
	glUniform1f(location, value);
}

void program_set_uniform2f(GLint location, GLfloat x, GLfloat y) {
	glUniform2f(location, x, y);
}

void program_set_uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(location, x, y, z);
}

void program_set_uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(location, x, y, z, w);
}

void program_set_uniform_mat3f(GLint location, const mat3_t* matrix) {
	float mat3_array[MAT3];
	mat3_to_array(matrix, mat3_array);
	glUniformMatrix3fv(location, 1, GL_FALSE, mat3_array);
}

void program_set_uniform_mat4f(GLint location, const mat4_t* matrix) {
	float mat4_array[MAT4];
	mat4_to_array(matrix, mat4_array);
	glUniformMatrix3fv(location, 1, GL_FALSE, mat4_array);
}
