#ifndef __SKY_PASS_H__
#define __SKY_PASS_H__

#include "../object/sky_object.h"
#include "../object/camera_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class sky_pass {
	private:
		const std::string m_env2diffuse_shader_path = "./shader/env2diffuse_sky_pass.shader";
		const std::string m_env2specular_shader_path = "./shader/env2specular_sky_pass.shader";
		const std::string m_env2background_shader_path = "./shader/env2background_sky_pass.shader";

		shader* m_env2diffuse_shader;
		shader* m_env2specular_shader;
		shader* m_env2background_shader;

		texture_2d* m_backgroud;
		frame_buffer* m_backgroud_frame_buffer;

		vertex_buffer* m_cube_mesh;
		glm::mat4 m_projection;
		std::vector<glm::mat4> m_cube_views;

		void rend_diffuse(render_system* render, texture_2d* environment, texture_cube*& diffuse);
		void rend_specular(render_system* render, texture_2d* environment, texture_cube*& specular);

	public:
		sky_pass(unsigned int width, unsigned int height);
		~sky_pass();
		texture_2d* get_backgroud(void) {
			return this->m_backgroud;
		}
		void rend(render_system* render, camera_object* camera, sky_object* sky);
	};
}

#endif // !__SKY_PASS_H__

