#ifndef __CAMERA_OBJECT_H__
#define __CAMERA_OBJECT_H__

#include <vector>

#include "object.h"

namespace ti_render {
	class camera_object : public object {
	friend class scene;
	private:
		float m_zoom;
		float m_aspect;
		float m_near;
		float m_far;

		camera_object(
			float zoom,
			float aspect,
			float near = 0.001f,
			float far = 1000.0f);
		~camera_object();

	public:
		float& get_zoom(void) {
			return m_zoom;
		}
		float& get_aspect(void) {
			return m_aspect;
		}
		float& get_near(void) {
			return m_near;
		}
		float& get_far(void) {
			return m_far;
		}
		glm::vec3 get_direction(void) const;
		glm::vec3 get_up(void) const;
		glm::vec3 get_right(void) const;
		glm::mat4 get_view(void) const;
		glm::mat4 get_projection(void) const;
	};
}

#endif // !__CAMERA_OBJECT_H__
