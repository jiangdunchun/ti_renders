#include "file_common.h"

#include <fstream>

using namespace std;

namespace ti_render {
	string file_common::ms_resource_path = "";

	void file_common::set_resource_path(const std::string& path) {
		ms_resource_path = path;
	}

	std::string file_common::get_file_path(const std::string& path) {
		ifstream f(ms_resource_path + "/" + path);
		if (f.good()) return ms_resource_path + "/" + path;
		return path;
	}
}