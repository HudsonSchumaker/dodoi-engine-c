/**
* @file main.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "include/pch.h"
#include "include/de_gfx.h"
#include "include/de_scene.h"
#include "playground/title_screen.h"
#include "playground/splash_screen.h"

int main(int argc, char* argv[]) {	
	gfx_init(false, true);
	
	splash_screen_init();
	title_screen_init();

	scene_t* splash_screen = splash_screen_get_scene();
	scene_t* title_screen = title_screen_get_scene();

	short r = scene_manager_set_scene(splash_screen);
	scene_manager_set_scene(title_screen);

	return 0;
}
