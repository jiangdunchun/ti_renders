#include <common\logger_management.cpp>
#include <render.h>
#include "console_logger.hpp"

using namespace ti_render;
using namespace glm;

int main(int, char**) {
	console_logger c_logger;
	logger_management::attach_logger(&c_logger);
	
	render::init(800, 600, "ti render");

	scene scene;

	mesh_object* StarSparrow = scene.create_mesh("./mesh/StarSparrow.mesh");
	StarSparrow->set_material(material_factory::create("./material/StarSparrow.material"), 0);
	StarSparrow->set_local_position(vec3(0.0f, 0.0f, -10.0f));

	point_light_object* point_light = scene.create_point_light(vec3(10.0f, 10.0f, 10.0f));
	point_light->set_local_position(vec3(0.0f, 2.0f, -10.0f));

	scene.set_sky_hdr("./texture/Alexs_Apt_2k.hdr");

	scene.get_camera()->set_local_rotation(vec3(0.0f, 15.0f, 0.0f));

	render::set_scene(&scene);

	render::run();
}