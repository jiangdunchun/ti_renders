#ifndef __WATER_OBJECT_H__
#define __WATER_OBJECT_H__

#include "object.h"

#include "../mesh/mesh_factory.h"

namespace ti_render {
	class water_object : public object {
	private:
		float m_x;
		float m_z;
		unsigned int m_x_num;
		unsigned int m_z_num;
		glm::vec2 m_wind_direction = glm::vec2(1.0f, 1.0f);
		float m_wind_speed = 0.0f;
		float m_wava_range = 0.0f;
		mesh* m_mesh;

		water_object(float x, float z, unsigned int x_num, unsigned int z_num);
		~water_object();

	public:
		glm::vec2& get_wind_direction(void) {
			return m_wind_direction;
		}
		float& get_wind_speed(void) {
			return m_wind_speed;
		}
		float get_wava_range(void) {
			return m_wava_range;
		}
	};
}

#endif // !__WATER_OBJECT_H__