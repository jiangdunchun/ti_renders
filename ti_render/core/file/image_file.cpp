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
		color_format format) : m_format(format) {
		stbi_set_flip_vertically_on_load(true);

		function<void*(char const*, int*, int*, int*, int)> image_loader = nullptr;
		switch (format) {
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
		switch (format) {
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
		const void* data,
		color_format format) : m_data(const_cast<void*>(data)), m_format(format) {
	}

	image_file::~image_file() {
		stbi_image_free(m_data);
	}

	void image_file::save(const std::string& path) const {
		throw "not impl!";
	}
}