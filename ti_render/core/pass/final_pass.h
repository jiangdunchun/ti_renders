#ifndef __FINAL_PASS_H__
#define __FINAL_PASS_H__

#include "../material/material.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class final_pass {
	private:
		const std::string m_shader_path = "shader/final_pass.shader";

		unsigned int m_width;
		unsigned int m_height;
		shader* m_shader;
		texture_2d* m_color_in;
		texture_2d* m_water_in;
		texture_2d* m_background_in;
		texture_2d* m_emissive_in;
		vertex_buffer* m_mesh;

	public:
		final_pass(
			unsigned int width,
			unsigned int height, 
			texture_2d* color,
			texture_2d* water,
			texture_2d* background,
			texture_2d* emissive);
		~final_pass();
		void rend(render_system* render);
	};
}

#endif // !__FINAL_PASS_H__
