#ifndef __SHADOWMAP_PASS_H_
#define __SHADOWMAP_PASS_H_

#include "../object/light_object.h"
#include "../object/mesh_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class shadowmap_pass {
	private:
		const std::string m_point_light_shader_path = "./shader/point_light_shadowmap_pass.shader";

		shader* m_point_light_shader;

	public:
		shadowmap_pass();
		~shadowmap_pass();
		void rend(render_system* render, std::vector<light_object*>& lights, std::vector<mesh_object*>& meshes);
	};
}

#endif // !__SHADOWMAP_PASS_H_

