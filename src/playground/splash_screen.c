/**
* @file splash_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "splash_screen.h"
#include "../include/de_gfx.h"
#include "../include/de_util.h"
#include "../include/de_buffer.h"
#include "../include/de_camera.h"
#include "../include/de_matrix.h"
#include "../include/de_vector.h"
#include "../include/de_program.h"

static bool running = false;
static scene_t* splash_screen = NULL;

static vao_t vao;
static vbo_t vbo;
static tbo_t tbo;
static program_t program;

static vec3_t position;
static vec3_t target;
static fps_camera_t* camera;

static float angle = 45.0f;

GLfloat TEX_COORDS[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

GLfloat VERTEX[] = {
	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

	// back face
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

	 // left face
	 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	 -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	 -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	 -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

	 // right face
	 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

	 // top face
	 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	 -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

	 // bottom face
	 -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
	 -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
	 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
};

void splash_screen_init(void) {
    splash_screen = (scene_t*)malloc(sizeof(scene_t));
    if (splash_screen == NULL) {
        fprintf(stderr, "failed to allocate memory for splashscreen.\n");
        exit(EXIT_FAILURE);
    }

    splash_screen->load   = splash_screen_load;
    splash_screen->input  = splash_screen_input;
    splash_screen->update = splash_screen_update;
    splash_screen->render = splash_screen_render;
    splash_screen->run    = splash_screen_run;
    splash_screen->unload = splash_screen_unload;

    printf("Splash Screen: Init\n");
}

void splash_screen_load(void) {
	if (!program_compile(&program, SHADER_FOLDER"basic.vert", SHADER_FOLDER"basic.frag")) {
		fprintf(stderr, "Failed to compile shaders.\n");
		exit(EXIT_FAILURE);
	}

	tbo_init(&tbo, IMAGE_FOLDER"cube.png");
	if (!tbo_load(&tbo)) {
		fprintf(stderr, "Failed to load texture.\n");
		exit(EXIT_FAILURE);
	}
	
	vbo_init(&vbo, (GLfloat*)VERTEX, sizeof(VERTEX));
	vao_link_vbo_3f2f(&vao, &vbo);

    position = vec3_new(0.0f, 1.0f, 10.0f);
    target = vec3_new(0.0f, 0.0f, 0.0f);

    camera = fps_camera_new(position, target);

    running = true;
    printf("Splash Screen: Load\n");
    // Load logic here
}

void splash_screen_input(void) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}

void splash_screen_update(void) {

}

void splash_screen_render(void) {
	glClearColor(0.0f, 0.555f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4_t world_matrix = mat4_identity();
	mat4_t view = mat4_identity();
	mat4_t projection = mat4_identity();

	mat4_t translation_matrix = mat4_make_translation(position.x, position.y, position.z);
	mat4_t rotation_matrix_x = mat4_make_rotation_x(angle);
	mat4_t rotation_matrix_y = mat4_make_rotation_y(angle);
	mat4_t rotation_matrix_z = mat4_make_rotation_z(angle);

	world_matrix = mat4_mul_mat4_sse(&rotation_matrix_z, &world_matrix);
	world_matrix = mat4_mul_mat4_sse(&rotation_matrix_y, &world_matrix);
	world_matrix = mat4_mul_mat4_sse(&rotation_matrix_x, &world_matrix);
	world_matrix = mat4_mul_mat4_sse(&translation_matrix, &world_matrix);

	view = mat4_look_at(&camera->coords.eye, &camera->coords.target, &camera->coords.up);
	const float fov = deg_to_rad(60.0f);
	projection = mat4_perspective(fov, 800.0f / 600.0f, 0.1f, 100.0f);
	
	GLint uniform_texture = program_get_uniform_location(&program, "myTexture");
	GLint uniform_model = program_get_uniform_location(&program, "model");
	GLint uniform_view = program_get_uniform_location(&program, "view");
	GLint uniform_projection = program_get_uniform_location(&program, "projection");

	program_set(&program);

	vao_bind(&vao);
	tbo_bind(&tbo);

	program_set_uniform1i(uniform_texture, 0);
	program_set_uniform_mat4f(uniform_model, &world_matrix);
	program_set_uniform_mat4f(uniform_view, &view);
	program_set_uniform_mat4f(uniform_projection, &projection);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	vao_unbind();
	program_unset();
	SDL_GL_SwapWindow(gfx_get_window());
}

short splash_screen_run(void) {
    while (running) {
        splash_screen_input();
        splash_screen_update();
        splash_screen_render();
        scene_manager_calculate_delta_time();
    }
    return 1;
}

void splash_screen_unload(void) {
    program_destroy(&program);
    printf("Splash Screen: Unload\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}
