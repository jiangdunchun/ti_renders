#include "gl430plus_texture_2d.h"

#include <algorithm>

using namespace std;

namespace ti_render {
	gl430plus_texture_2d::gl430plus_texture_2d(
		unsigned int width, 
		unsigned int height, 
		color_format format) : m_width(width), m_height(height), m_format(format) {
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			map_color_internal_format(m_format), 
			m_width, 
			m_height, 
			0, 
			map_color_format(m_format),
			map_color_data_type(m_format),
			nullptr);


		m_mipmap_layer_max = 0;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	gl430plus_texture_2d::~gl430plus_texture_2d() {
		glDeleteTextures(1, &m_id);
	}

	void gl430plus_texture_2d::push_data(
		color_format format,
		const void* data, 
		unsigned int mipmap_layer) {
		if (mipmap_layer > m_mipmap_layer_max) return;

		unsigned int width = get_width(mipmap_layer);
		unsigned int height = get_height(mipmap_layer);

		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(
			GL_TEXTURE_2D,
			mipmap_layer,
			map_color_internal_format(m_format),
			width,
			height,
			0,
			map_color_format(format),
			map_color_data_type(format),
			data);
	}

	void gl430plus_texture_2d::generate_mipmap(void) {
		glBindTexture(GL_TEXTURE_2D, m_id);

		m_mipmap_layer_max = unsigned int(log2(max(m_width, m_height)));
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	unsigned int gl430plus_texture_2d::get_width(unsigned int mipmap_layer) const {
		if (mipmap_layer > m_mipmap_layer_max) return 0;
		unsigned int width = m_width / int(pow(2, mipmap_layer));
		if (width == 0) width = 1;
		return width;
	}

	unsigned int gl430plus_texture_2d::get_height(unsigned int mipmap_layer) const {
		if (mipmap_layer > m_mipmap_layer_max) return 0;
		unsigned int height = m_height / int(pow(2, mipmap_layer));
		if (height == 0) height = 1;
		return height;
	}
}