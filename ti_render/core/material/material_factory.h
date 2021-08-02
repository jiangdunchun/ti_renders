#ifndef __MATERIAL_FACTORY_H__
#define __MATERIAL_FACTORY_H__

#include "material.h"

namespace ti_render {
	class material_factory {
	private:
		static std::map<std::string, std::tuple<material*, unsigned int>> sm_material_pool;
	public:
		static material* create(const std::string& path);
		static material* create(material_type m_type);
		static void dispose(material* material_ptr);
	};
}

#endif // !__MATERIAL_FACTORY_H__
