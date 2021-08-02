#include "point_light_object.h"

using namespace glm;
using namespace std;

namespace ti_render {
	point_light_object::point_light_object(
		const vec3& intensity,
		float radius,
		float bias,
		unsigned int shadow_map_size) : light_object(intensity), m_radius(radius), m_bias(bias), m_shadow_map_size(shadow_map_size) {
		m_type = object_type::POINT_LIGHT;

		m_shadow_map = new gl3plus_texture_cube(m_shadow_map_size, m_shadow_map_size, color_format::RGBA16F);
		m_frame_buffer = new gl3plus_frame_buffer(m_shadow_map_size, m_shadow_map_size);
	}

	point_light_object::~point_light_object() {
		delete m_shadow_map;
		delete m_frame_buffer;
	}

	void point_light_object::set_shadow_map_size(unsigned int size) {
		delete m_shadow_map;
		delete m_frame_buffer;

		m_shadow_map_size = size;
		m_shadow_map = new gl3plus_texture_cube(m_shadow_map_size, m_shadow_map_size, color_format::RGBA16F);
		m_frame_buffer = new gl3plus_frame_buffer(m_shadow_map_size, m_shadow_map_size);
	}
}