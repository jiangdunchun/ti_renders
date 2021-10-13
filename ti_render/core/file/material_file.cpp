#include "material_file.h"

#include <fstream>
#include <stringbuffer.h>
#include <document.h>
#include <writer.h>

#include "../../common/logger_management.h"
#include "file_common.h"


using namespace std;
using namespace rapidjson;

namespace ti_render {
	material_file::material_file(const string& path) {
		string file_path = file_common::get_file_path(path);
		ifstream file;
		try {
			file.open(file_path, ios::binary);

			istreambuf_iterator<char> beg(file), end;
			string mat_str(beg, end);

			Document m_json;
			Document::AllocatorType allocator;

			if (!m_json.Parse(mat_str.c_str()).HasParseError()) {
				m_type = m_json[MATERIAL_TYPE_ELEM].GetString();

				Value& parameters = m_json[MATERIAL_PARAMETERS_ELEM];
				Value::MemberIterator iter = parameters.MemberBegin();
				Value name;
				Value val;
				while (iter != parameters.MemberEnd()) {
					name.CopyFrom(iter->name, allocator);
					val.CopyFrom(iter->value, allocator);

					m_parameters.push_back(name.GetString());
					m_values.push_back(val.GetString());

					iter++;
				}
			}
		}
		catch (ifstream::failure e) {
			if (file.is_open()) file.close();
			logger_management::log(log_tag::LOG_ERROR,
				"file::mesh_file:load file \"" + path + "\" failed");
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
		Document mat_doc(kObjectType);

		Value type_json(kStringType);
		type_json.SetString(m_type.c_str(), mat_doc.GetAllocator());
		mat_doc.AddMember(MATERIAL_TYPE_ELEM, type_json, mat_doc.GetAllocator());

		Value parameters_json(kObjectType);
		for (unsigned int i = 0; i < m_parameters.size(); i++) {
			Value parameter_json(kStringType);
			parameter_json.SetString(m_values[i].c_str(), mat_doc.GetAllocator());
			parameters_json.AddMember(StringRef(m_parameters[i].c_str()), parameter_json, mat_doc.GetAllocator());
		}
		mat_doc.AddMember(MATERIAL_PARAMETERS_ELEM, parameters_json, mat_doc.GetAllocator());

		StringBuffer mat_buffer;
		Writer<StringBuffer> mat_writer(mat_buffer);
		mat_doc.Accept(mat_writer);
		ofstream mat_file(path);
		mat_file << mat_buffer.GetString();
		mat_file.close();
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