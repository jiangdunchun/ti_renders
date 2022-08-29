#include <iostream>
#include <tigine.core/common/logger_mgr.h>
#include <tigine.core/asset/image_asset.h>
#include <tigine.core/asset/material_asset.h>
#include <tigine.core/asset/mesh_asset.h>
#include <tigine.core/scene/object.h>
#include <tigine.core/component/transform_component.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

using namespace tigine;
using namespace std;
using namespace glm;

class my_logger : public i_logger {
public:
	void log(log_tag tag, string msg) {
		cout << "[";
		if (tag == log_tag::DEBUG)
			cout << GREEN << "DEBUG" << RESET << "] ";
		else if (tag == log_tag::WARN)
			cout << YELLOW << "WARN" << RESET << "] ";
		else if (tag == log_tag::ERROR)
			cout << RED << "ERROR" << RESET << "] ";
		cout << msg << endl;
	}
};

void image_asset_test() {
	const string img_path = "GGX_E_IS_LUT.png";
	LOG_DEBUG("load image %s --->", img_path.c_str());
	unique_ptr<image_asset> img = image_asset::load(TEST_ASSET_DIR + img_path, image_format::RGB8B);
	if (!img) return;

	LOG_DEBUG("	width: %i, height: %i", img->get_width(), img->get_height());
	vec4 p_color = img->sample_liner(vec2(0.1, 0.23));
	LOG_DEBUG("	sample liner from (0.1, 0.23): %f, %f, %f, %f", p_color.x, p_color.y, p_color.z, p_color.w);
	img->save_png(TEST_ASSET_DIR + img_path + ".png");
	LOG_DEBUG("	save image to %s.png", img_path.c_str());
}

void material_asset_test() {
	const string mat_path = "StarSparrow.mat";
	LOG_DEBUG("load mat %s --->", mat_path.c_str());
	unique_ptr<material_asset> mat = material_asset::load(TEST_ASSET_DIR + mat_path);
	if (!mat) return;

	LOG_DEBUG("	type: %s", mat->get_type().c_str());
	std::vector<std::string> parameters = mat->get_parameters();
	LOG_DEBUG("	parameters:");
	for (auto& para : parameters) {
		LOG_DEBUG("		%s:%s", para.c_str(), mat->get_value(para).c_str());
	}
	mat->save(TEST_ASSET_DIR + mat_path + ".mat");
	LOG_DEBUG("	save mat to %s.mat", mat_path.c_str());
}

void mesh_asset_test() {
}

void component_test() {
	object obj("root");
	LOG_DEBUG("test transform_component--->");
	obj.add_component(transform_component);
	shared_ptr<transform_component> t_cpt = obj.get_component(transform_component);
	t_cpt->get_position() = vec3(10.f, 0.f, 5.f);
	t_cpt->get_rotation() = vec3(90.f, 0.f, 0.f);
	t_cpt->get_scale() = vec3(2.f, 1.f, 2.f);
	mat4 m = t_cpt->get_matrix();
	LOG_DEBUG("	matrix:\n		%f, %f, %f, %f;\n		%f, %f, %f, %f;\n		%f, %f, %f, %f;\n		%f, %f, %f, %f;", 
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}

int main() {
	i_logger* logger = new my_logger();
	logger_mgr::attach_logger(logger);
	LOG_DEBUG("init logger");

	image_asset_test();
	material_asset_test();
	mesh_asset_test();

	component_test();
	

	delete logger;
}