#ifndef __WATER_PASS_H__
#define __WATER_PASS_H__

#include "../object/camera_object.h"
#include "../object/sky_object.h"
#include "../object/water_object.h"
#include "../graphic_interface/graphic_interface.h"

namespace ti_render {
	class water_pass {
	private:
		const std::string m_shader_path = "shader/water_pass.shader";

		shader* m_shader;
		texture_2d* m_position_in;
		texture_2d* m_base_color_in;
		texture_2d* m_color;
		frame_buffer* m_frame_buffer;

	public:
		water_pass(
			unsigned int width,
			unsigned int height,
			texture_2d* position,
			texture_2d* base_color,
			ds_render_buffer* ds_buffer);
		~water_pass();
		texture_2d* get_color(void) {
			return m_color;
		}
		void rend(
			render_system* render,
			camera_object* camera,
			sky_object* sky,
			std::vector<water_object*> waters);
	};
}

#endif // !__WATER_PASS_H__

