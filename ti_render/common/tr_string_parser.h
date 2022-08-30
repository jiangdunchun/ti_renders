#ifndef __TR_STRING_PARSER_H__
#define __TR_STRING_PARSER_H__

#include <string>
#include <glm/glm.hpp>

namespace ti_render {
	class tr_string_parser {
	public:
		static std::string to_string(const glm::vec2& value);
		static std::string to_string(const glm::vec3& value);
		static std::string to_string(const glm::vec4& value);
		static std::string to_string(const glm::mat2& value);
		static std::string to_string(const glm::mat3& value);
		static std::string to_string(const glm::mat4& value);

		static glm::vec2 to_vec2(const std::string& value);
		static glm::vec3 to_vec3(const std::string& value);
		static glm::vec4 to_vec4(const std::string& value);
		static glm::mat2 to_mat2(const std::string& value);
		static glm::mat3 to_mat3(const std::string& value);
		static glm::mat4 to_mat4(const std::string& value);
	};
}

#endif // !__TR_STRING_PARSER_H__
