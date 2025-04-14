/**
* @file de_program.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_program.h"
#include "../../include/de_collection.h"

program_t* program_new(void) {
	program_t* program = (program_t*)malloc(sizeof(program_t));
	if (program == NULL) {
		fprintf(stderr, "failed to allocate memory for program.\n");
		exit(EXIT_FAILURE);
	}
	program_init(program);
	return program;
}

void program_init(program_t* program) {
	program->id = glCreateProgram();
	if (program->id == 0) {
		fprintf(stderr, "failed to create program.\n");
	}
}

bool program_compile(program_t* program, const GLchar* vertex_path, const GLchar* fragment_path) {
	shader_t* vertex_shader = shader_new();
	shader_t* fragment_shader = shader_new();
	shader_init_vert_shader(vertex_shader);
	shader_init_frag_shader(fragment_shader);

	if (!shader_compile(vertex_shader, vertex_path)) {
		fprintf(stderr, "failed to compile vertex shader: %s\n", vertex_path);
		return false;
	}
	if (!shader_compile(fragment_shader, fragment_path)) {
		fprintf(stderr, "failed to compile fragment shader: %s\n", fragment_path);
		return false;
	}
	if (!program_link(program, vertex_shader, fragment_shader)) {
		fprintf(stderr, "failed to link program: %d\n", program->id);
		return false;
	}

	program_detach_shader(program, vertex_shader);
	program_detach_shader(program, fragment_shader);
	shader_delete(vertex_shader);
	shader_delete(fragment_shader);

	return true;
}

bool program_save_binary(program_t* program, const char* binary_path) {
	GLenum binary_format = program_get_supported_bin_formats();
	if (binary_format == 0) {
		fprintf(stderr, "no binary files supported by the driver\n");
		return false;
	}

	// Get the length of the binary
	GLint binary_length = 0;
	glGetProgramiv(program->id, GL_PROGRAM_BINARY_LENGTH, &binary_length);
	if (binary_length == 0) {
		fprintf(stderr, "failed to get program binary length.\n");
		return false;
	}

	// Allocate memory for the binary
	GLvoid* binary = malloc(binary_length);
	if (binary == NULL) {
		fprintf(stderr, "failed to allocate memory for program binary.\n");
		return false;
	}

	// Get the binary data
	glGetProgramBinary(program->id, binary_length, NULL, &binary_format, binary);

	// Open the file for writing
	FILE* file = fopen(binary_path, "wb");
	if (file == NULL) {
		fprintf(stderr, "failed to open file for writing: %s.\n", binary_path);
		free(binary);
		return false;
	}

	// Write the binary format and length to the file
	fwrite(&binary_format, sizeof(GLenum), 1, file);
	fwrite(&binary_length, sizeof(GLint), 1, file);

	// Write the binary data to the file
	fwrite(binary, 1, binary_length, file);

	// Clean up
	fclose(file);
	free(binary);

	return true;
}

program_t* program_load_binary(const char* binary_path) {
	GLenum binary_format = program_get_supported_bin_formats();
	if (binary_format == 0) {
		fprintf(stderr, "no binary files supported by the driver\n");
		return false;
	}

	// Open the file for reading
	FILE* file = fopen(binary_path, "rb");
	if (file == NULL) {
		fprintf(stderr, "failed to open file for reading: %s.\n", binary_path);
		return NULL;
	}

	// Read the binary format and length from the file
	GLint binary_length;
	fread(&binary_format, sizeof(GLenum), 1, file);
	fread(&binary_length, sizeof(GLint), 1, file);
	
	// Allocate memory for the binary
	GLvoid* binary = malloc(binary_length);
	if (binary == NULL) {
		fprintf(stderr, "failed to allocate memory for program binary.\n");
		fclose(file);
		return NULL;
	}

	// Read the binary data from the file
	fread(binary, 1, binary_length, file);

	// Create a new program
	program_t* program = program_new();
	program_init(program);
	
	// Load the binary data into the program
	glProgramBinary(program->id, binary_format, binary, binary_length);
	
	// Clean up
	fclose(file);
	free(binary);
	return program;
}

bool program_link(program_t* program, shader_t* vertex_shader, shader_t* fragment_shader) {
	glAttachShader(program->id, vertex_shader->id);
	glAttachShader(program->id, fragment_shader->id);
	glLinkProgram(program->id);
	
	// Check for linking errors
	GLint result;
	glGetProgramiv(program->id, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		GLint info_log_length;
		glGetShaderiv(program->id, GL_INFO_LOG_LENGTH, &info_log_length);

		GLchar* info_log = malloc(info_log_length);
		glGetShaderInfoLog(program->id, info_log_length, NULL, info_log);

		fprintf(stderr, "failed to compile shader: %s.\n", info_log);
		free(info_log);
		return false;
	}
	return true;
}

GLenum program_get_supported_bin_formats(void) {
	GLint num_formats;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &num_formats);
	if (num_formats == 0) {
		fprintf(stderr, "no binary files supported by the driver\n");
		return 0;
	}

	GLenum* formats = (GLenum*)malloc(num_formats * sizeof(GLenum));
	if (formats == NULL) {
		fprintf(stderr, "Failed to allocate memory for binary formats.\n");
		return 0;
	}

	glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, (GLenum*)formats);
	return formats[0]; // Return the first supported format
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
	glUniformMatrix4fv(location, 1, GL_FALSE, mat4_array);
}
