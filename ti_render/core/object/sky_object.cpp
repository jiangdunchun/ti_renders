#include "sky_object.h"

#include "../file/image_file.h"

using namespace std;

namespace ti_render {
	sky_object::sky_object(const string& sky_hdr) {
		image_file sky_hdr_image(sky_hdr, color_format::RGBA16F);
		m_sky_hdr = new gl3plus_texture_2d(sky_hdr_image.get_width(), sky_hdr_image.get_height(), color_format::RGBA16F);
		m_sky_hdr->push_data(sky_hdr_image.get_color_format(), sky_hdr_image.get_data());
	}

	sky_object::~sky_object() {
		delete m_sky_hdr;
		delete m_sky_cube;
		delete m_diffuse_cube;
		delete m_specular_cube;
	}
}