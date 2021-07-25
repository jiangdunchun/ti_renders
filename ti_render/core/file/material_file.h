#ifndef __MATERIAL_FILE_H__
#define __MATERIAL_FILE_H__

#include <vector>
#include <string>

#define MATERIAL_TYPE_ELEM			"type"
#define MATERIAL_PARAMETERS_ELEM    "parameters"

namespace ti_render {
	class material_file {
	private:
		std::string m_format;
		std::vector<std::string> _parameters;
		std::vector<std::string> _values;

	public:
		material_file(const std::string& path);
		material_file(const std::string& type, const std::vector<std::string>& parameters);
		~material_file();

		void save(const std::string& path) const;
		const std::string& get_type(void) const {
			return this->m_format;
		}
		const std::vector<std::string>& get_parameters(void) const {
			return this->_parameters;
		}
		const std::string& get_value(const std::string& parameter) const {
			for (unsigned int i = 0; i < this->_parameters.size(); i++) {
				if (parameter == this->_parameters[i]) return this->_values[i];
			}
		}
		void set_value(const std::string& parameter, const std::string& value) {
			for (unsigned int i = 0; i < this->_parameters.size(); i++) {
				if (parameter == this->_parameters[i]) {
					this->_values[i] = value;
					return;
				}
			}
		}
	};
}

#endif // !__MATERIAL_FILE_H__

