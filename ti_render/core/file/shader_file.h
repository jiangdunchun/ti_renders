#ifndef __SHADER_FILE_H__
#define __SHADER_FILE_H__

#include <vector>
#include <string>
#include <map>

#define VERTEX_SHADER_ELEM		"#__VERTEX_SHADER__"
#define FRAGMENT_SHADER_ELEM    "#__FRAGMENT_SHADER__"
#define GEOMTRY_SHADER_ELEM     "#__GEOMTRY_SHADER__"
#define COMPUTE_SHADER_ELEM     "#__COMPUTE_SHADER__"

namespace ti_render {
	class shader_file {
	private:
		std::string m_vertex_code = "";
		std::string m_geometry_code = "";
		std::string m_fragment_code = "";
		std::string m_compute_code = "";

	public:
		shader_file(const std::string& path);
		~shader_file();

		void save(const std::string& path) const;
		std::string& get_vertex_code(void) {
			return m_vertex_code;
		}
		std::string& get_geometry_code(void) {
			return m_geometry_code;
		}
		std::string& get_fragment_code(void) {
			return m_fragment_code;
		}
		std::string& get_compute_code(void) {
			return m_compute_code;
		}
	};
}


#endif // !__SHADER_FILE_H__

