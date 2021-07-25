#include "material_file.h"

#include <fstream>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

#include "../../common/logger_management.h"


using namespace std;
using namespace rapidjson;

namespace ti_render {
	material_file::material_file(const std::string& path) {
		ifstream file;
		try {
			file.open(path, ios::binary);

			istreambuf_iterator<char> beg(file), end;
			string mat_str(beg, end);

			Document m_json;
			Document::AllocatorType allocator;

			if (!m_json.Parse(mat_str.c_str()).HasParseError()) {
				this->m_format = m_json[MATERIAL_TYPE_ELEM].GetString();

				Value& parameters = m_json[MATERIAL_PARAMETERS_ELEM];
				Value::MemberIterator iter = parameters.MemberBegin();
				Value name;
				Value val;
				while (iter != parameters.MemberEnd()) {
					name.CopyFrom(iter->name, allocator);
					val.CopyFrom(iter->value, allocator);

					this->_parameters.push_back(name.GetString());
					this->_values.push_back(val.GetString());

					iter++;
				}
			}
		}
		catch (std::ifstream::failure e) {
			if (file.is_open()) file.close();
			logger_management::log(log_tag::LOG_ERROR,
				"file::mesh_file:load file \"" + path + "\" failed");
		}
	}

	material_file::material_file(const std::string& type, const std::vector<std::string>& parameters) {
		this->m_format = type;
		this->_parameters = parameters;
		this->_values.resize(parameters.size(), "");
	}

	material_file::~material_file() {
	}

	void material_file::save(const std::string& path) const {
		Document mat_doc(kObjectType);

		Value type_json(kStringType);
		type_json.SetString(this->m_format.c_str(), mat_doc.GetAllocator());
		mat_doc.AddMember(MATERIAL_TYPE_ELEM, type_json, mat_doc.GetAllocator());

		Value parameters_json(kObjectType);
		for (unsigned int i = 0; i < this->_parameters.size(); i++) {
			Value parameter_json(kStringType);
			parameter_json.SetString(this->_values[i].c_str(), mat_doc.GetAllocator());
			parameters_json.AddMember(StringRef(this->_parameters[i].c_str()), parameter_json, mat_doc.GetAllocator());
		}
		mat_doc.AddMember(MATERIAL_PARAMETERS_ELEM, parameters_json, mat_doc.GetAllocator());

		StringBuffer mat_buffer;
		Writer<StringBuffer> mat_writer(mat_buffer);
		mat_doc.Accept(mat_writer);
		ofstream mat_file(path);
		mat_file << mat_buffer.GetString();
		mat_file.close();
	}
}