/**
* @file scene.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_scene.h"

static float delta_time = 0.0f;
static scene_t* current_scene = NULL;

short scene_manager_set_scene(scene_t* scene) {
    short status = 0;
    if (current_scene && current_scene->unload) {
        current_scene->unload();       // unload the current scene
        //free(current_scene);
    }

    current_scene = scene;
    if (current_scene && current_scene->load) {
        current_scene->load();         // load the new scene
    }
    if (current_scene && current_scene->run) {
        status = current_scene->run(); // run the scene loop
    }
    return status;
}

float scene_manager_get_delta_time(void) {
    return delta_time;
}

float scene_manager_calculate_delta_time(void) {
    static Uint32 millisecs_previous_frame = 0;

    Uint32 current_ticks = SDL_GetTicks();
    Uint32 frame_time = current_ticks - millisecs_previous_frame;
    if (frame_time < FRAME_TARGET_TIME) {
        SDL_Delay(FRAME_TARGET_TIME - frame_time);
    }

    current_ticks = SDL_GetTicks();
    delta_time = (current_ticks - millisecs_previous_frame) / 1000.0f;
    millisecs_previous_frame = current_ticks;

    return delta_time;
}
