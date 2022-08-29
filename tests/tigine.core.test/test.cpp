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

int main() {
	i_logger* logger = new my_logger();
	logger_mgr::attach_logger(logger);
	LOG_DEBUG("init logger");

	image_asset_test();
	material_asset_test();
	mesh_asset_test();

	object obj("root");
	obj.add_component(transform_component);
	obj.add_component(transform_component);

	delete logger;
}