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
#include "../include/de_cube.h"
#include "../include/de_util.h"
#include "../include/de_camera.h"

static bool running = false;
static fps_camera_t* camera = NULL;
static scene_t* splash_screen = NULL;

static mat4_t projection;
static mat4_t view;

static cube_t cube;
static cube_t cube2;
static cube_t cube3;
static cube_t _floor;

static vec3_t target = { 0.0f, 0.0f, 0.0f };
static vec3_t position = { 0.0f, 1.0f, -5.0f };

static vec3_t cube_pos = { -10.0f, 2.0f, 10.0f };
static vec3_t cube_pos2 = { 0.0f, 2.0f, 10.0f };
static vec3_t cube_pos3 = { 10.0f, 2.0f, 10.0f };
static vec3_t floor_pos = { 0.0f, .0f, 0.0f };
float angle = 45.0f;

void check_gl_error(const char* function) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        const char* errorString;
        switch (error) {
        case GL_INVALID_ENUM:      errorString = "GL_INVALID_ENUM"; break;
        case GL_INVALID_VALUE:     errorString = "GL_INVALID_VALUE"; break;
        case GL_INVALID_OPERATION: errorString = "GL_INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:    errorString = "GL_STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:   errorString = "GL_STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:     errorString = "GL_OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: errorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        default:                   errorString = "Unknown Error"; break;
        }
        fprintf(stderr, "OpenGL error in %s: %s\n", function, errorString);
        error = glGetError();
    }
}

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
	cube_init(&cube, "cube.vert", "cube.frag", "icon.png");
    cube_init(&cube2, "cube.vert", "cube.frag", "cube.png");
    cube_init(&cube3, "cube.vert", "cube.frag", "crate.jpg");
	cube_init(&_floor, "cube.vert", "cube.frag", "grid.jpg");
	
    cube_set_position(&cube, &cube_pos);
    cube_set_position(&cube2, &cube_pos2);
    cube_set_position(&cube3, &cube_pos3);
	cube_set_position(&_floor, &floor_pos);

	vec3_t scale = vec3_new(20.0f, 0.1f, 20.0f);
	cube_set_scale(&_floor, &scale);

    camera = fps_camera_new(position, target);

	gfx_set_clear_color(0.0f, 0.2f, 0.0f, 1.0f);
    running = true;
    printf("Splash Screen: Load\n");
}

void splash_screen_input(void) {
    const float MOUSE_SENSITIVITY = 0.1f;
    const float MOVE_SPEED = 8.0f;
    static int lastMouseX;
    static int lastMouseY;
    static vec3_t direction;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        SDL_Keycode key = sdlEvent.key.keysym.sym;
        
        switch (sdlEvent.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_MOUSEMOTION:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            float deltaX = (float)lastMouseX - (float)mouseX;
            float deltaY = (float)lastMouseY - (float)mouseY;

            float yaw   = -deltaX / 4 + sdlEvent.motion.xrel * MOUSE_SENSITIVITY * scene_manager_get_delta_time();
            float pitch = deltaY  / 4 + sdlEvent.motion.yrel * MOUSE_SENSITIVITY * scene_manager_get_delta_time();

            fps_camera_set_rotation(camera, yaw, pitch);
            lastMouseX = mouseX;
            lastMouseY = mouseY;
			break;

		case SDL_KEYDOWN:
            if (key == SDLK_w || key == SDLK_UP) {
                direction.z = 1.0f;
            }

            if (key == SDLK_s || key == SDLK_DOWN) {
                direction.z = -1.0f;              
            }

			if (key == SDLK_a || key == SDLK_LEFT) {
				direction.x = -1.0f;
			}

			if (key == SDLK_d || key == SDLK_RIGHT) {
				direction.x = 1.0f;
			}
			break;

        case SDL_KEYUP:
            key = sdlEvent.key.keysym.sym;

            if (key == SDLK_w || key == SDLK_UP) {
                direction.z = 0.0f;
            }

            if (key == SDLK_s || key == SDLK_DOWN) {
                direction.z = 0.0f;
            }

            if (key == SDLK_a || key == SDLK_LEFT) {
                direction.x = 0.0f;
            }

            if (key == SDLK_d || key == SDLK_RIGHT) {
                direction.x = 0.0f;
            }
            break;
        
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
                gfx_on_window_resized(gfx_get_window(), sdlEvent.window.data1, sdlEvent.window.data2);
            }
			break;
		}
	}

	float speed = MOVE_SPEED * scene_manager_get_delta_time();
    vec3_t scaled_direction = vec3_mul(&direction, speed);
	fps_camera_move(camera, scaled_direction);
}

void splash_screen_update(void) {
	fps_camera_update(camera);
	
	projection = mat4_identity();
    float fov = deg_to_rad(FOV);
	projection = mat4_perspective(fov, gfx_get_aspect_ratio(), 0.1f, 100.0f);
	
	view = mat4_identity();
    view = mat4_look_at(&camera->coords.eye, &camera->coords.target, &camera->coords.up); 

	vec3_t rotation = { 0.0f, 0.0f, angle };
	cube_set_rotation(&cube, &rotation);
    cube_update(&cube);

    cube_set_rotation(&cube2, &rotation);
    cube_update(&cube2);

    cube_set_rotation(&cube3, &rotation);
    cube_update(&cube3);

	//cube_set_rotation(&_floor, &rotation);
	cube_update(&_floor);

    angle += deg_to_rad(5000.0f * scene_manager_get_delta_time());

    //if (angle > 2 * PI) angle -= 2 * PI;
}

void splash_screen_render(void) {
	gfx_clear_screen();

	cube_render(&cube, &view, &projection);
    cube_render(&cube2, &view, &projection);
    cube_render(&cube3, &view, &projection);
	cube_render(&_floor, &view, &projection);
	
	gfx_swap_screen();
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
	cube_delete(&cube);
    cube_delete(&cube2);
    cube_delete(&cube3);
    printf("Splash Screen: Unload\n");
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}
