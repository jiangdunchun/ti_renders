#include <render.h>
#include <iostream>
#include <time.h>
#include <common/i_logger.h>
#include <common\logger_management.cpp>

using namespace ti_render;
using namespace glm;

class console_logger : public ti_render::i_logger {
public:
	void log(ti_render::log_tag tag, std::string msg) {
		// @TODO: https://blog.csdn.net/qq_41972382/article/details/90311102
		std::string tag_str = "";
		switch (tag) {
		case ti_render::log_tag::LOG_DEBUG:
			tag_str = "DEBUG";
			break;
		case ti_render::log_tag::LOG_WARNING:
			tag_str = "WARNING";
			break;
		case ti_render::log_tag::LOG_ERROR:
			tag_str = "ERROR";
			break;
		}
		std::cout << clock() << ":[" << tag_str << "]" << msg << std::endl;
	}
};

#define PI 3.1415926f

point_light_object* point_light_obj = nullptr;
float light_angle = 0.0f;
camera_object* camera_obj = nullptr;
float camera_angle = 0.0f;

void update() {
	light_angle += render::get_tick() / 10.0f;
	light_angle = light_angle > 1.0f ? light_angle - 1.0f : light_angle;
	glm::vec3 light_pos = glm::vec3(0.0f, -3.0f, 0.0f) + 6.0f * glm::vec3(cos(2.0f * PI * light_angle), abs(sin(2.0f * PI * light_angle)), 0.0f);
	point_light_obj->set_local_position(light_pos);

	camera_angle += render::get_tick() / 20.0f;
	camera_angle = camera_angle > 1.0f ? camera_angle - 1.0f : camera_angle;
	glm::vec3 camera_pos = 10.0f * glm::vec3(sin(2.0f * PI * camera_angle), 0.5f, cos(2.0f * PI * camera_angle));
	camera_obj->set_local_position(camera_pos);
	camera_obj->set_local_rotation(glm::vec3(0.0f, 360.0f * camera_angle, 0.0f));
}

int main(int, char**) {
	console_logger c_logger;
	logger_management::attach_logger(&c_logger);

	render::init(1000, 1000, "ti render", "../../resource");

	scene scene;

	mesh_object* StarSparrow = scene.create_mesh("mesh/StarSparrow.mesh");
	StarSparrow->set_material(material_factory::create("material/StarSparrow.material"), 0);

	point_light_obj = scene.create_point_light(glm::vec3(3.0f, 3.0f, 3.0f));

	scene.set_sky_hdr("texture/Alexs_Apt_2k.hdr");

	camera_obj = scene.get_camera();

	render::add_post_update_func(update);

	render::run(&scene);
}