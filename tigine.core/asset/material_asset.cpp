#include "material_asset.h"

#include <fstream>
#include <json11/json11.hpp>
#include <tigine.core/common/logger_mgr.h>

using namespace std;
using namespace json11;

namespace tigine {
	const string material_asset::TYPE_ELEM = "type";
	const string material_asset::PARA_ELEM = "parameters";

	material_asset::material_asset(const string& type, const vector<string>& parameters) {
		m_type = type;
		m_parameters = parameters;
		m_values.resize(parameters.size(), "");
	}

	unique_ptr<material_asset> material_asset::load(const std::string& path) {
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
			LOG_ERROR("load material failed from %s", path.c_str());
			return nullptr;
		}

		string err;
		Json mat_json = Json::parse(mat_str, err);
		if (err != "") {
			LOG_ERROR("material content damage of %s", path.c_str());
			return nullptr;
		}
		string type = mat_json[TYPE_ELEM].string_value();
		vector<string> parameters;
		vector<string> values;
		for (auto& para : mat_json[PARA_ELEM].object_items()) {
			parameters.push_back(para.first);
			values.push_back(para.second.string_value());
		}

		unique_ptr<material_asset> ret(new material_asset(type, parameters));
		for (int i = 0; i < parameters.size(); i++)
			ret->set_value(parameters[i], values[i]);
		return ret;
	}

	void material_asset::save(const string& path) const {
		Json::object para_json;
		for (int i = 0; i < m_parameters.size(); i++) {
			para_json[m_parameters[i]] = Json(m_values[i]);
		}
		Json mat_json = Json::object { 
			{TYPE_ELEM, m_type},
			{PARA_ELEM, para_json} };

		ofstream mat_file(path);
		mat_file << mat_json.dump();
		mat_file.close();
	}

	const string& material_asset::get_value(const string& parameter) const {
		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			if (parameter == m_parameters[i]) return m_values[i];
		}
		return "";
	}

	void material_asset::set_value(const string& parameter, const string& value) {
		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			if (parameter == m_parameters[i]) {
				m_values[i] = value;
				return;
			}
		}
	}
}
