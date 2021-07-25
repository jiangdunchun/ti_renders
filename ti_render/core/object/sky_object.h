#ifndef __SKY_OBJECT_H__
#define __SKY_OBJECT_H__

#include <string>

#include "object.h"
#include "../../graphic_interface/graphic_interface.h"

namespace ti_render {
	class sky_object : public object {
		friend class scene;

	private:
		texture_2d* m_sky_hdr;
		texture_cube* m_sky_cube = nullptr;
		texture_cube* m_diffuse_cube = nullptr;
		texture_cube* m_specular_cube = nullptr;

		sky_object(const std::string& sky_hdr);
		~sky_object();
	};
}

#endif // !__SKY_OBJECT_H__

