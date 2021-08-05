#include "image_file.h"

#include <functional>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "../../common/logger_management.h"

using namespace std;

namespace ti_render {
	image_file::image_file(
		const string& path,
		color_format format,
		bool flip_y) : m_format(format) {
		stbi_set_flip_vertically_on_load(flip_y);

		function<void*(char const*, int*, int*, int*, int)> image_loader = nullptr;
		switch (m_format) {
		case color_format::R8B:
		case color_format::RGB8B:
		case color_format::RGBA8B:
			image_loader = stbi_load;
			break;
		case color_format::R16F:
		case color_format::RGB16F:
		case color_format::RGBA16F:
			image_loader = stbi_loadf;
			break;
		default:
			break;
		}

		int req_component = 0;
		switch (m_format) {
		case color_format::R8B:
		case color_format::R16F:
			req_component = 1;
			break;
		case color_format::RGB8B:
		case color_format::RGB16F:
			req_component = 3;
			break;
		case color_format::RGBA8B:
		case color_format::RGBA16F:
			req_component = 4;
			break;
		default:
			break;
		}

		int component, width, height;
		m_data = image_loader(path.c_str(), &width, &height, &component, req_component);
		
		if (m_data != nullptr) {
			m_width = width;
			m_height = height;
		}
		else {
			logger_management::log(log_tag::LOG_ERROR,
				"file::image_file:load file \"" + path + "\" failed");
		}
	}

	image_file::image_file(
		unsigned int width,
		unsigned int height,
		color_format format) : m_width(width), m_height(height), m_format(format) {
		switch (m_format) {
		case color_format::R8B:
			m_data = new char[m_width * m_height * 1];
			break;
		case color_format::RGB8B:
			m_data = new char[m_width * m_height * 3];
			break;
		case color_format::RGBA8B:
			m_data = new char[m_width * m_height * 4];
			break;
		case color_format::R16F:
			m_data = new float[m_width * m_height * 1];
			break;
		case color_format::RGB16F:
			m_data = new float[m_width * m_height * 3];
			break;
		case color_format::RGBA16F:
			m_data = new float[m_width * m_height * 4];
			break;
		default:
			break;
		}
	}

	image_file::~image_file() {
		stbi_image_free(m_data);
	}

	void image_file::save(const string& path) const {
		throw "not impl!";
	}

	void image_file::set_data(const void* data) {
		if (!m_data) delete[] m_data;

		switch (m_format) {
		case color_format::R8B:
			memcpy(m_data, data, sizeof(char) * m_width * m_height * 1);
			break;
		case color_format::RGB8B:
			memcpy(m_data, data, sizeof(char) * m_width * m_height * 3);
			break;
		case color_format::RGBA8B:
			memcpy(m_data, data, sizeof(char) * m_width * m_height * 4);
			break;
		case color_format::R16F:
			memcpy(m_data, data, sizeof(float) * m_width * m_height * 1);
			break;
		case color_format::RGB16F:
			memcpy(m_data, data, sizeof(float) * m_width * m_height * 3);
			break;
		case color_format::RGBA16F:
			memcpy(m_data, data, sizeof(float) * m_width * m_height * 4);
			break;
		default:
			break;
		}
	}
}