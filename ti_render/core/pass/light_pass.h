#ifndef __LIGHT_PASS_H__
#define __LIGHT_PASS_H__

#include "../object/camera_object.h"
#include "../object/sky_object.h"
#include "../object/light_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class light_pass {
	private:
		const std::string m_shader_path = "./shader/light_pass.shader";
		const std::string m_lut_path = "./texture/GGX_E_IS_LUT.png";

		shader* m_shader;
		texture_2d* m_lut;
		texture_2d* m_position_in;
		texture_2d* m_base_color_in;
		texture_2d* m_normal_in;
		texture_2d* m_material_in;
		vertex_buffer* m_mesh;
		texture_2d* m_color;
		frame_buffer* m_frame_buffer;

	public:
		light_pass(
			unsigned int width,
			unsigned int height,
			texture_2d* position,
			texture_2d* base_color,
			texture_2d* normal,
			texture_2d* material);
		~light_pass();
		texture_2d* get_color(void) {
			return m_color;
		}
		void rend(
			render_system* render,
			camera_object* camera,
			sky_object* sky,
			std::vector<light_object*> lights);
	};
}

#endif // !__LIGHT_PASS_H__

