#ifndef __PASS_MANAGEMENT_H__
#define __PASS_MANAGEMENT_H__

#include "../scene/scene.h"

#include "pre_pass.h"
#include "geometry_pass.h"
#include "sky_pass.h"
#include "shadowmap_pass.h"
#include "emissive_pass.h"

namespace ti_render {
	class pass_management {
	private:
		pre_pass* m_pre_pass;
		geometry_pass* m_geomtry_pass;
		sky_pass* m_sky_pass;
		shadowmap_pass* m_shadowmap_pass;
		emissive_pass* m_emissive_pass;

	public:
		pass_management(unsigned int width, unsigned int height);
		~pass_management();
		void rend(render_system* render_system, scene* scene);
	};
}

#endif // !__PASS_MANAGEMENT_H__

