/**
* @file gfx.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_gfx.h"
#include "../../include/de_model.h"

static SDL_Window* window = NULL;
static SDL_GLContext* context = NULL;
static int GFX_WINDOW_WIDTH = 0;
static int GFX_WINDOW_HEIGHT = 0;
static color_t color;

void gfx_init(bool fullscreen, bool vsync) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "failed to init SDL2: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

	// Set clear color
	color.r = 0.0f; color.g = 0.0f; color.b = 0.0f; color.a = 1.0f;

    // Request at 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    // Request a double-buffered, OpenGL 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    unsigned long flags = SDL_WINDOW_OPENGL;
    flags |= SDL_WINDOW_RESIZABLE;
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    // Create SDL2 window
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        flags
    );

    if (window == NULL) {
        fprintf(stderr, "failed to create SDL2 window: %s.\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    GFX_WINDOW_WIDTH = WINDOW_WIDTH;
    GFX_WINDOW_HEIGHT = WINDOW_HEIGHT;

    // Set window icon
    char* icon = "./data/icon.png";
    SDL_Surface* iconSurface = IMG_Load(icon);
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);

    // SDL_GLContext is an alias for "void*"
    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        fprintf(stderr, "failed to create open_gl context: %s.\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "failed to initialize GLAD.\n");
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Enable v-sync (set 1 to enable, 0 to disable)
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
    glViewport(0, 0, GFX_WINDOW_WIDTH, GFX_WINDOW_HEIGHT);
}

SDL_Window* gfx_get_window(void) {
    return window;
}

SDL_GLContext* gfx_get_context(void) {
    return context;
}

float gfx_get_aspect_ratio(void) {
    return (float)GFX_WINDOW_WIDTH / GFX_WINDOW_HEIGHT;
}

ipair_t gfx_get_window_size(void) {
	ipair_t window_size = { GFX_WINDOW_WIDTH, GFX_WINDOW_HEIGHT };
    return window_size;
}

void gfx_show_mouse_cursor(bool value) {
	SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
}

void gfx_set_mouse_position(const int x, const int y) {
	SDL_WarpMouseInWindow(window, x, y);
}

void gfx_set_clear_color(const float r, const float g, const float b, const float a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

void gfx_clear_screen(void) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx_swap_screen(void) {
	SDL_GL_SwapWindow(window);
}

void gfx_set_2d_mode(void) {
	glDisable(GL_DEPTH_TEST);
}

void gfx_set_3d_mode(void) {
	glEnable(GL_DEPTH_TEST);
}

SDL_Surface* gfx_load_texture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        fprintf(stderr, "failed to load texture: %s.\n", path);
        return NULL;
    }
    return surface;
}

void gfx_on_window_resized(SDL_Window* window, const int new_width, const int new_height) {
    printf("Window resized to %dx%d\n", new_width, new_height);
    // Perform any updates needed for your application, e.g., adjust viewport.
    GFX_WINDOW_WIDTH = new_width;
    GFX_WINDOW_HEIGHT = new_height;

    SDL_SetWindowSize(window, GFX_WINDOW_WIDTH, GFX_WINDOW_HEIGHT);
    glViewport(0, 0, GFX_WINDOW_WIDTH, GFX_WINDOW_HEIGHT);
}

void gfx_close(void) {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void gfx_open_gl_info(void) {
    printf("Platform:         %s\n",    SDL_GetPlatform());
    printf("CPU Count:        %d\n",    SDL_GetCPUCount());
    printf("System RAM:       %d MB\n", SDL_GetSystemRAM());
    printf("Supports SSE:     %s\n", SDL_HasSSE()     ? "true" : "false");
    printf("Supports SSE2:    %s\n", SDL_HasSSE2()    ? "true" : "false");
    printf("Supports SSE3:    %s\n", SDL_HasSSE3()    ? "true" : "false");
    printf("Supports SSE4.1:  %s\n", SDL_HasSSE41()   ? "true" : "false");
    printf("Supports SSE4.2:  %s\n", SDL_HasSSE42()   ? "true" : "false");
    printf("Supports AVX:     %s\n", SDL_HasAVX()     ? "true" : "false");
    printf("Supports AVX2:    %s\n", SDL_HasAVX2()    ? "true" : "false");
    printf("Supports AVX512F: %s\n", SDL_HasAVX512F() ? "true" : "false");
    printf("Supports NEON:    %s\n", SDL_HasNEON()    ? "true" : "false");
    printf("Supports AltiVec: %s\n", SDL_HasAltiVec() ? "true" : "false");
    printf("Supports MMX:     %s\n", SDL_HasMMX()     ? "true" : "false");
    printf("Supports 3DNow:   %s\n", SDL_Has3DNow()   ? "true" : "false");
    printf("Supports RDTSC:   %s\n", SDL_HasRDTSC()   ? "true" : "false");

    printf("OpenGL Vendor:    %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer:  %s\n", glGetString(GL_RENDERER));
    printf("OpenGL Version:   %s\n", glGetString(GL_VERSION));
    printf("GLSL Version:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Get the number of extensions
    GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    // Print each extension
    for (GLint i = 0; i < numExtensions; i++) {
        const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
        printf("OpenGL Extension #%d: %s.\n", i, extension);
    }
}
