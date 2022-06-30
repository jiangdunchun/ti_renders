#ifndef __MATERIAL_ASSET_H__
#define __MATERIAL_ASSET_H__

#include <string>
#include <vector>

namespace tigine {
	class material_asset {
	private:
		std::string m_type;
		std::vector<std::string> m_parameters;
		std::vector<std::string> m_values;

	public:
		material_asset(const std::string& path);
		material_asset(const std::string& type, const std::vector<std::string>& parameters);
		~material_asset();

		void save(const std::string& path) const;
		const std::string& get_type(void) const {
			return m_type;
		}
		const std::vector<std::string>& get_parameters(void) const {
			return m_parameters;
		}
		const std::string& get_value(const std::string& parameter) const;
		void set_value(const std::string& parameter, const std::string& value);
	};
}

#endif 
