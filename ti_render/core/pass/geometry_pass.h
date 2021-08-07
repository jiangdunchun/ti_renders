#ifndef __GEOMETRY_PASS_H__
#define __GEOMETRY_PASS_H__

#include "../object/camera_object.h"
#include "../object/mesh_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class geometry_pass {
	private:
		texture_2d* m_position;
		texture_2d* m_base_color;
		texture_2d* m_normal;
		texture_2d* m_material;
		texture_2d* m_emissive;
		frame_buffer* m_frame_buffer;

	public:
		geometry_pass(unsigned int width, unsigned int height, ds_render_buffer* dbo);
		~geometry_pass();
		texture_2d* get_position(void) {
			return this->m_position;
		}
		texture_2d* get_base_color(void) {
			return this->m_base_color;
		}
		texture_2d* get_normal(void) {
			return this->m_normal;
		}
		texture_2d* get_material(void) {
			return this->m_material;
		}
		texture_2d* get_emissive(void) {
			return this->m_emissive;
		}
		void rend(render_system* render, camera_object* camera, std::vector<mesh_object*> meshes);
	};
}

#endif // !__GEOMETRY_PASS_H__
