#include "material_file.h"

#include <fstream>
#include <json11/json11.hpp>

#include "../common/logger_management.h"
#include "file_common.h"

using namespace std;
using namespace json11;

namespace ti_render {
	material_file::material_file(const string& path) {
		string file_path = file_common::get_file_path(path);

		string mat_str;
		ifstream file;
		try {
			file.open(path, ios::binary);
			istreambuf_iterator<char> beg(file), end;
			mat_str = string(beg, end);
			file.close();
		}
		catch (ifstream::failure e) {
			if (file.is_open()) file.close();
			logger_management::log(log_tag::LOG_ERROR,
				"file::mesh_file:load file \"" + path + "\" failed");
		}

		string err;
		Json mat_json = Json::parse(mat_str, err);
		if (err != "") {
			logger_management::log(log_tag::LOG_ERROR,
				"file::mesh_file:load file \"" + path + "\" failed");
			return;
		}
		m_type = mat_json[MATERIAL_TYPE_ELEM].string_value();
		vector<string> parameters;
		vector<string> values;
		for (auto& para : mat_json[MATERIAL_PARAMETERS_ELEM].object_items()) {
			m_parameters.push_back(para.first);
			m_values.push_back(para.second.string_value());
		}
	}

	material_file::material_file(const string& type, const vector<string>& parameters) {
		m_type = type;
		m_parameters = parameters;
		m_values.resize(parameters.size(), "");
	}

	material_file::~material_file() {
	}

	void material_file::save(const string& path) const {
		
	}

	const string& material_file::get_value(const string& parameter) const {
		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			if (parameter == m_parameters[i]) return m_values[i];
		}
		return "";
	}

	void material_file::set_value(const string& parameter, const string& value) {
		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			if (parameter == m_parameters[i]) {
				m_values[i] = value;
				return;
			}
		}
	}
}