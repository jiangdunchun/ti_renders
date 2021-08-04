#ifndef __PASS_MANAGEMENT_H__
#define __PASS_MANAGEMENT_H__

#include "../scene/scene.h"

#include "pre_pass.h"

namespace ti_render {
	class pass_management {
	private:
		pre_pass* m_pre_pass;

	public:
		pass_management(unsigned int width, unsigned int height);
		~pass_management();
		void rend(render_system* render_system, scene* scene);
	};
}

#endif // !__PASS_MANAGEMENT_H__

