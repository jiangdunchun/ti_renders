#ifndef __SHADOW_MAP_PASS_H_
#define __SHADOW_MAP_PASS_H_

#include "../file/shader_file.h"
#include "../object/light_object.h"
#include "../object/mesh_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class shadow_map_pass {
	private:
		const std::string m_shader_path = "./shader/shadow_map_pass.shader";

		shader* m_shader;

	public:
		shadow_map_pass();
		~shadow_map_pass();
		void rend(render_system* render, std::vector<light_object*> lights, std::vector<mesh_object*> meshes);
	};
}

#endif // !__SHADOW_MAP_PASS_H_

