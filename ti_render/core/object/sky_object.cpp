#include "sky_object.h"

#include "../file/image_file.h"

using namespace std;

namespace ti_render {
	sky_object::sky_object(const string& sky_hdr) {
		m_type = object_type::SKY_OBJECT;

		image_file sky_hdr_image(sky_hdr, color_format::RGBA16F, true);
		m_environment = new gl3plus_texture_2d(sky_hdr_image.get_width(), sky_hdr_image.get_height(), color_format::RGBA16F);
		m_environment->push_data(sky_hdr_image.get_color_format(), sky_hdr_image.get_data());
	}

	sky_object::~sky_object() {
		delete m_environment;
		delete m_diffuse_cube;
		delete m_specular_cube;
	}
}