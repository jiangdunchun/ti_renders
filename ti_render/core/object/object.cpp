#include "object.h" 

#include "dummy_object.h"
#include "../../common/tr_algorithm.h"

using namespace std;
using namespace glm;

namespace ti_render {
	void object::update_transform(void) {
		m_transform = mat4(1.0f);
		m_transform = translate(m_transform, m_postion);
		m_transform = rotate(m_transform, radians(m_rotation.x), vec3(1.0f, 0.0f, 0.0f));
		m_transform = rotate(m_transform, radians(m_rotation.y), vec3(0.0f, 1.0f, 0.0f));
		m_transform = rotate(m_transform, radians(m_rotation.z), vec3(0.0f, 0.0f, 1.0f));
		m_transform = scale(m_transform, m_scale);
	}

	object::object() {
		m_postion = vec3(0.0f, 0.0f, 0.0f);
		m_rotation = vec3(0.0f, 0.0f, 0.0f);
		m_scale = vec3(1.0f, 1.0f, 1.0f);
		update_transform();
	}
	object::~object() {
	}

	const dummy_object* object::get_parent(void) const {
		return m_parent;
	}
	void object::set_parent(dummy_object* parent) {
		if (parent == m_parent) return;

		if (m_parent) {
			for (vector<object*>::iterator iter = m_parent->m_children.begin();
				iter != m_parent->m_children.end();
				++iter) {
				if ((*iter) == this) {
					m_parent->m_children.erase(iter);
					break;
				}
			}
		}
		parent->m_children.push_back(this);

		m_parent = parent;
	}
	vec3 object::get_world_position(void) const {
		mat4 w_transform = get_world_transform();
		vec3 position; 
		vec3 rotation; 
		vec3 scale;
		decompose_mat4(w_transform, position, rotation, scale);

		return position;
	}
	vec3 object::get_world_rotation(void) const {
		mat4 w_transform = get_world_transform();
		vec3 position;
		vec3 rotation;
		vec3 scale;
		decompose_mat4(w_transform, position, rotation, scale);

		return rotation;
	}
	vec3 object::get_world_scale(void) const {
		mat4 w_transform = get_world_transform();
		vec3 position;
		vec3 rotation;
		vec3 scale;
		decompose_mat4(w_transform, position, rotation, scale);

		return scale;
	}
	mat4 object::get_world_transform(void) const {
		if (m_parent) return m_parent->get_world_transform() * get_local_transform();
		else return get_local_transform();
	}
	void object::set_local_position(const vec3& position) {
		m_postion = position;
		update_transform();
	}
	void object::set_local_rotation(const vec3& rotation) {
		m_rotation = rotation;
		vec3 r = (1.0f / 360.0f) * rotation;
		m_rotation -= 360.0f * vec3(int(r.x), int(r.y), int(r.z));
		update_transform();
	}
	void object::set_local_scale(const vec3& scale) {
		m_scale = scale;
		update_transform();
	}
}