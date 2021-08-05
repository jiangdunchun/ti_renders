#ifndef __PRE_PASS_H__
#define __PRE_PASS_H__

#include <vector>
#include <string>

#include "../file/shader_file.h"
#include "../object/camera_object.h"
#include "../object/mesh_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class pre_pass {
	private:
		const std::string m_shader_path = "./shader/pre_pass.shader";

		shader* m_shader;
		texture_2d* m_id_texture;
		ds_render_buffer* m_ds_render_buffer;
		frame_buffer* m_frame_buffer;

		glm::vec4 get_color(unsigned int id);

	public:
		pre_pass(unsigned int width, unsigned int height);
		~pre_pass();
		ds_render_buffer* get_ds_render_buffer(void) const {
			return m_ds_render_buffer;
		}
		void rend(render_system* render_system, camera_object* camera, std::vector<mesh_object*>& meshes);
	};
}

#endif // !__PRE_PASS_H__
