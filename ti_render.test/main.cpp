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
	StarSparrow->set_material(material_factory::create(material_type::METALLIC_ROUGHNESS), 0);
	StarSparrow->set_local_position(vec3(0.0f, 0.0f, -10.0f));

	scene.set_sky_hdr("./texture/Alexs_Apt_2k.hdr");

	scene.get_camera()->set_local_rotation(vec3(0.0f, 15.0f, 0.0f));

	render::set_scene(&scene);

	render::run();
}