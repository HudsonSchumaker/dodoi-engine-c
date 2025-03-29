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

static bool running = false;
static scene_t* title_screen = NULL;

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
    printf("Title Screen: Load\n");
    // Load logic here
}

void title_screen_input(void) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}

void title_screen_update(void) {
}

void title_screen_render(void) {
    glClearColor(0.555f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    SDL_GL_SwapWindow(gfx_get_window());
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
    printf("Title Screen: Unload\n");
}

scene_t* title_screen_get_scene(void) {
    return title_screen;
}
