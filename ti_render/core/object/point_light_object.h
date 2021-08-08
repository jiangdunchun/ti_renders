#ifndef __POINT_LIGHT_OBJECT_H__
#define __POINT_LIGHT_OBJECT_H__

#include "light_object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class point_light_object : public light_object {
		friend class scene;
		friend class shadowmap_pass;

	private:
		float m_radius;
		float m_bias;
		unsigned int m_shadow_map_size;
		gl3plus_texture_cube* m_shadow_map;
		gl3plus_frame_buffer* m_frame_buffer;

		point_light_object(
			const glm::vec3& intensity, 
			float radius = 10.0f,
			float bias = 0.05f,
			unsigned int shadow_map_size = 2048);
		~point_light_object();

	public:
		float& get_radius(void) {
			return m_radius;
		}
		float& get_bias() {
			return m_bias;
		}
		unsigned int get_shadow_map_size(void) {
			return m_shadow_map_size;
		}
		void set_shadow_map_size(unsigned int size);
	};
}

#endif // !__POINT_LIGHT_OBJECT_H__

