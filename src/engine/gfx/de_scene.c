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
    static Uint64 previous_ticks = 0;
    Uint64 current_ticks = SDL_GetTicks64();

    if (previous_ticks == 0) {
        previous_ticks = current_ticks;
        return 0.0f;
    }

    Uint64 frame_ticks = current_ticks - previous_ticks;

    if (frame_ticks < (Uint64)FRAME_TARGET_TIME) {
        SDL_Delay((Uint32)(FRAME_TARGET_TIME - (float)frame_ticks));
        current_ticks = SDL_GetTicks64();
        frame_ticks = current_ticks - previous_ticks;
    }

    previous_ticks = current_ticks;
    delta_time = (float)frame_ticks * 0.001f;
    return delta_time;
}
