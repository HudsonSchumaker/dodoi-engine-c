#include "include/de_gfx.h"
#include "include/de_program.h"

int main(int argc, const char* argv[]) {
	
	// Initialize SDL
	gfx_init(false, true);
	program_t* program = program_new();

	program_compile(program, SHADER_FOLDER"basic.vert", SHADER_FOLDER"basic.frag");


	return 0;
}
