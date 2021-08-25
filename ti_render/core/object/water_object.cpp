#include "water_object.h"

#include "../mesh/mesh_factory.h"

using namespace glm;

namespace ti_render {
	water_object::water_object(
		float x, float z,
		unsigned int x_num, unsigned int z_num) :m_x(x), m_z(z), m_x_num(x_num), m_z_num(z_num) {
		m_type = object_type::WATER_OBJECT;

		m_mesh = mesh_factory::create_plane(x, z, x_num, z_num);
	}

	water_object::~water_object() {
		mesh_factory::dispose(m_mesh);
	}
}