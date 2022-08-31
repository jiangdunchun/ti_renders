#include "transform_component.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace tigine {
	mat4 transform_component::get_matrix() {
		mat4 ret(1.0f);
		ret = translate(ret, m_position);
		ret = rotate(ret, m_rotation.x, vec3(1.0f, 0.0f, 0.0f));
		ret = rotate(ret, m_rotation.y, vec3(0.0f, 1.0f, 0.0f));
		ret = rotate(ret, m_rotation.z, vec3(0.0f, 0.0f, 1.0f));
		ret = scale(ret, m_scale);
		return ret;
	}
}