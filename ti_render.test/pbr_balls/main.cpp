#include <common\logger_management.cpp>
#include <render.h>
#include "console_logger.hpp"

using namespace ti_render;
using namespace glm;

#define PI 3.1415926f

point_light_object* point_light_obj = nullptr;
float light_angle = 0.0f;
camera_object* camera_obj = nullptr;
float camera_angle = 0.0f;

void update() {
	camera_angle += render::get_tick() / 20.0f;
	camera_angle = camera_angle > 1.0f ? camera_angle - 1.0f : camera_angle;
	glm::vec3 camera_pos = 20.0f * glm::vec3(sin(2.0f * PI * camera_angle), 0.0f, cos(2.0f * PI * camera_angle));
	camera_obj->set_local_position(camera_pos);
	camera_obj->set_local_rotation(glm::vec3(0.0f, 360.0f * camera_angle, 0.0f));
}

int main(int, char**) {
	console_logger c_logger;
	logger_management::attach_logger(&c_logger);
	
	render::init(1000, 1000, "ti render", "../assert");

	scene scene;

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			mesh_object* ball = scene.create_mesh("mesh/ball.mesh");
			material* mat = material_factory::create(material_type::METALLIC_ROUGHNESS);
			mat->set_value({ "uBase_color_val",  value_type::VEC3 }, "1.0f, 0.0f, 0.0f");
			mat->set_value({ "uMetallic_val",  value_type::FLOAT }, to_string(i / 10.0f));
			mat->set_value({ "uRoughness_val",  value_type::FLOAT }, to_string(j / 10.0f));
			ball->set_material(mat, 0);
			ball->set_local_position(vec3((i - 6) * 2.0f, (j - 6) * 2.0f, 0.0f));
		}
	}

	point_light_obj = scene.create_point_light(glm::vec3(3.0f, 3.0f, 3.0f));
	point_light_obj->get_radius() = 0.1f;

	scene.set_sky_hdr("./texture/Alexs_Apt_2k.hdr");

	camera_obj = scene.get_camera();

	render::add_post_update_func(update);

	render::run(&scene);
}