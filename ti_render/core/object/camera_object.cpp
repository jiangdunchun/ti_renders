#include "camera_object.h"

using namespace glm;

namespace ti_render {
	camera_object::camera_object(
		float zoom,
		float aspect,
		float near,
		float far) : m_zoom(zoom), m_aspect(aspect), m_near(near), m_far(far) {
		m_type = object_type::CAMERA_OBJECT;
	}

	camera_object::~camera_object() {}

	vec3 camera_object::get_direction(void) const {
		vec4 direct = get_world_transform() * vec4(0.0f, 0.0f, -1.0f, 0.0f);
		return normalize(vec3(direct.x, direct.y, direct.z));
	}

	vec3 camera_object::get_up(void) const {
		vec4 up = get_world_transform() * vec4(0.0f, 1.0f, 0.0f, 0.0f);
		return normalize(vec3(up.x, up.y, up.z));
	}

	vec3 camera_object::get_right(void) const {
		return cross(get_direction(), get_up());
	}

	mat4 camera_object::get_view(void) const {
		vec3 direct = get_direction();
		vec3 pos = get_world_position();
		vec3 up = get_up();

		return lookAt(pos, pos + direct, up);
	}

	mat4 camera_object::get_projection(void) const {
		return perspective(radians(m_zoom), m_aspect, m_near, m_far);
	}
}