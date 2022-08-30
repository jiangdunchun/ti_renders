#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include <glm/glm.hpp>
#include "component.h"

namespace tigine {
	class transform_component : public component {
	private:
		glm::vec3 m_position{0.f ,0.f ,0.f};
		glm::vec3 m_rotation{0.f, 0.f, 0.f};
		glm::vec3 m_scale{1.f, 1.f, 1.f};

	public:
		virtual ~transform_component() {}
		glm::vec3& get_position() {
			return m_position;
		}
		glm::vec3& get_rotation() {
			return m_rotation;
		}
		glm::vec3& get_scale() {
			return m_scale;
		}
		glm::mat4 get_matrix();
	};
}

#endif // !__TRANSFORM_COMPONENT_H__
