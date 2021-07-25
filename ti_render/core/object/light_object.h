#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__

#include "object.h"

namespace ti_render {
	class light_object : public object {
	protected:
		glm::vec3 m_intensity;

		light_object(glm::vec3 intensity);
		virtual ~light_object() {}
	public:
		glm::vec3& get_intensity(void) {
			return this->m_intensity;
		}
	};
}

#endif // !__LIGHT_OBJECT_H__

