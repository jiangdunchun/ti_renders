#ifndef __EMISSIVE_PASS_H__
#define __EMISSIVE_PASS_H__

#include "../graphic_interface/graphic_interface.h"

namespace ti_render {
	class emissive_pass {
	private:
		const std::string m_shader_path = "shader/emissive_pass.shader";

		compute_shader* m_shader;
		texture_2d* m_emissive_in;
		texture_2d* m_emissive_h;
		texture_2d* m_emissive_v;

	public:
		emissive_pass(unsigned int width, unsigned int height, texture_2d* emissive);
		~emissive_pass();
		texture_2d* get_emissive(void) {
			return m_emissive_v;
		}
		void rend(render_system* render);
	};
}

#endif // !__EMISSIVE_PASS_H__
