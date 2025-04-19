/**
* @file title_screen.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "title_screen.h"
#include "../include/de_gfx.h"
#include "../include/de_cube.h"
#include "../include/de_util.h"
#include "../include/de_math.h"
#include "../include/de_mouse.h"
#include "../include/de_camera.h"

static bool running = false;
static scene_t* title_screen = NULL;
static fps_camera_t* camera = NULL;

static mat4_t projection;
static mat4_t view;

static cube_t cube;
static cube_t cube2;
static cube_t cube3;
static cube_t _floor;

static vec3_t target = { 0.0f, 0.0f, 0.0f };
static vec3_t position = { 0.0f, 1.0f, -5.0f };

static vec3_t cube_pos = { 0.0f, 2.0f, 10.0f };
static vec3_t cube2_pos = { 10.0f, 2.0f, 10.0f };
static vec3_t cube3_pos = { -10.0f, 3.0f, 10.0f };
static vec3_t floor_pos = { 0.0f, .0f, 0.0f };
static float angle = 15.0f;

void title_screen_init(void) {
    title_screen = (scene_t*)malloc(sizeof(scene_t));
    if (title_screen == NULL) {
        fprintf(stderr, "failed to allocate memory for title.\n");
        exit(EXIT_FAILURE);
    }

    title_screen->load   = title_screen_load;
    title_screen->input  = title_screen_input;
    title_screen->update = title_screen_update;
    title_screen->render = title_screen_render;
    title_screen->run    = title_screen_run;
    title_screen->unload = title_screen_unload;

    printf("Title Screen: Init\n");
    running = true;
}

void title_screen_load(void) {
    cube_init(&cube, "directional-light.vert", "directional-light.frag", "icon.png", "cube.obj");
    cube_init(&cube2, "directional-light.vert", "directional-light.frag", "icon.png", "cube.obj");
    cube_init(&cube3, "directional-light.vert", "directional-light.frag", "crate.jpg", "crate.obj");
    cube_init(&_floor, "directional-light.vert", "directional-light.frag", "grid.jpg", "floor.obj");

    cube2.material = material_chrome();
    cube3.material = material_red_rubber();

    cube_set_position(&cube, &cube_pos);
    cube_set_position(&cube2, &cube2_pos);
    cube_set_position(&cube3, &cube3_pos);
    cube_set_position(&_floor, &floor_pos);

    vec3_t scale = vec3_new(20.0f, 0.1f, 20.0f);
    cube_set_scale(&_floor, &scale);

    camera = fps_camera_new(position, target);
    gfx_set_clear_color(0.5f, 0.5f, 0.0f, 1.0f);

    running = true;
    printf("Title Screen: Load\n");
}

void title_screen_input(void) {
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

		case SDL_MOUSEBUTTONDOWN:
			if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

                game_object_t objects[] = { cube.go, cube2.go, cube3.go };
                handle_mouse_click(mouseX, mouseY, &view, &projection, &camera->coords.eye, objects, 3);
			}
			break;

        case SDL_MOUSEMOTION:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            float deltaX = (float)lastMouseX - (float)mouseX;
            float deltaY = (float)lastMouseY - (float)mouseY;

            float yaw = -deltaX / 4 + sdlEvent.motion.xrel * MOUSE_SENSITIVITY * scene_manager_get_delta_time();
            float pitch = deltaY / 4 + sdlEvent.motion.yrel * MOUSE_SENSITIVITY * scene_manager_get_delta_time();

            //fps_camera_set_rotation(camera, yaw, pitch);
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
                direction.x = 1.0f;
            }

            if (key == SDLK_d || key == SDLK_RIGHT) {
                direction.x = -1.0f;
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

void title_screen_update(void) {
    fps_camera_update(camera);

    projection = mat4_identity();
    projection = camera_perspective(0.1f, 100.0f);

    view = mat4_identity();
    view = camera_look_at(&camera->coords);

    vec3_t rotation = { angle, angle, angle };
    vec3_t rotation2 = { -angle, -angle, -angle };
    cube_set_rotation(&cube, &rotation);
    cube_update(&cube);

    cube_set_rotation(&cube2, &rotation2);
    cube_update(&cube2);

    cube_set_rotation(&cube3, &rotation);
    cube_update(&cube3);

    //cube_set_rotation(&_floor, &rotation);
    cube_update(&_floor);

    angle += 25.0f * scene_manager_get_delta_time();
    angle = normalize_anglef(angle);
}

void title_screen_render(void) {
    gfx_set_3d_mode();
    gfx_clear_screen();

    cube_render(&cube, &view, &projection);
    cube_render(&cube2, &view, &projection);
    cube_render(&cube3, &view, &projection);
    cube_render(&_floor, &view, &projection);

    gfx_swap_screen();
}

short title_screen_run(void) {
    while (running) {
        title_screen_input();
        title_screen_update();
        title_screen_render();
        scene_manager_calculate_delta_time();
    }
    return 1;
}

void title_screen_unload(void) {
    cube_delete(&cube);
    cube_delete(&cube2);
    cube_delete(&cube3);
    cube_delete(&_floor);
    printf("Title Screen: Unload\n");
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}
