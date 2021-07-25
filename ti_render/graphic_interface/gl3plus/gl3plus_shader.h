#ifndef __GL3PLUS_SHADER_H__
#define __GL3PLUS_SHADER_H__

#include <string>

#include "gl3plus_texture_2d.h"
#include "gl3plus_texture_cube.h"

namespace ti_render {
	class gl3plus_shader {
    private:
        static unsigned int sm_texture_index;

        unsigned int m_id;

    public:
        gl3plus_shader(const std::string& vertex_code, const std::string& fragment_code, const std::string& geometry_code = "");
        ~gl3plus_shader();

        void use(void) const;
        void set_bool(const std::string& name, const bool value) const;
        void set_int(const std::string& name, const int value) const;
        void set_float(const std::string& name, const float value) const;
        void set_vec2(const std::string& name, const glm::vec2& value) const;
        void set_vec3(const std::string& name, const glm::vec3& value) const;
        void set_vec4(const std::string& name, const glm::vec4& value) const;
        void set_mat2(const std::string& name, const glm::mat2& value) const;
        void set_mat3(const std::string& name, const glm::mat3& value) const;
        void set_mat4(const std::string& name, const glm::mat4& value) const;
        void set_texture_2d(const std::string& name, const gl3plus_texture_2d* value) const;
        void set_texture_cube(const std::string& name, const gl3plus_texture_cube* value) const;
	};
}

#endif // !__GL3PLUS_SHADER_H__

