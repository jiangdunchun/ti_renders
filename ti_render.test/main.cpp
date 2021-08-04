#include <common\logger_management.cpp>
#include <render.h>
#include "console_logger.hpp"

using namespace ti_render;

int main(int, char**) {
	console_logger c_logger;
	logger_management::attach_logger(&c_logger);
	
	render::init(800, 600, "ti render");

	scene scene;
	scene.create_mesh("./mesh/StarSparrow.mesh");

	render::set_scene(&scene);

	render::run();
}