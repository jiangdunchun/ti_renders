#include <iostream>
#include <tigine.core/common/logger_mgr.h>
#include <tigine.core/asset/image_asset.h>
#include <tigine.core/asset/material_asset.h>
#include <tigine.core/asset/mesh_asset.h>

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
	string img_info = img_path + "---> \n";
	image_asset* img = image_asset::load(TEST_ASSET_DIR + img_path, image_format::RGB8B);
	if (!img) return;

	img_info += ("width:" + to_string(img->get_width()) + ", height:" + to_string(img->get_height()) + "\n");
	vec4 p_color = img->sample_liner(vec2(0.1, 0.23));
	img_info += ("sample liner from (0.1, 0.23):" 
		+ to_string(p_color.x) + ", "
		+ to_string(p_color.y) + ", "
		+ to_string(p_color.z) + ", " 
		+ to_string(p_color.w) + "\n");
	LOG_DEBUG(img_info);
	img->save(TEST_ASSET_DIR + img_path + ".png");
	delete img;
}

void material_asset_test() {
	const string mat_path = "StarSparrow.mat";
	string mat_info = mat_path + "---> \n";
	material_asset* mat = material_asset::load(TEST_ASSET_DIR + mat_path);
	if (!mat) return;

	mat_info += ("type:" + mat->get_type() + "\n");
	std::vector<std::string> parameters = mat->get_parameters();
	mat_info += ("parameters:\n");
	for (auto& para : parameters) {
		mat_info += ("	" + para + ":" + mat->get_value(para) + "\n");
	}
	LOG_DEBUG(mat_info);
	mat->save(TEST_ASSET_DIR + mat_path + ".mat");
	delete mat;
}

void mesh_asset_test() {
	const string mesh_path = "rp_nathan_animated_003_walking.fbx";
	string mesh_info = mesh_path + "---> \n";
	vector<mesh_asset*> meshes = mesh_asset::load_scene(TEST_ASSET_DIR + mesh_path);
	if (meshes.size() == 0) return;

	LOG_DEBUG(mesh_info);
	for (auto& mesh : meshes) delete mesh;
}

int main() {
	i_logger* logger = new my_logger();
	logger_mgr::attach_logger(logger);
	LOG_DEBUG("init logger\n");

	image_asset_test();
	material_asset_test();
	mesh_asset_test();

	delete logger;
}