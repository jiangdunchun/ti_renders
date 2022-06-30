#include "image_asset.h"

#include <functional>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "../common/logger_mgr.h"

using namespace std;
using namespace glm;

namespace tigine {
	image_asset::image_asset(
		const string& path,
		image_format format,
		bool flip_y) : m_format(format) {
		stbi_set_flip_vertically_on_load(flip_y);

		function<void*(char const*, int*, int*, int*, int)> image_loader = nullptr;
		switch (m_format) {
		case image_format::R8B:
		case image_format::RGB8B:
		case image_format::RGBA8B:
			image_loader = stbi_load;
			break;
		case image_format::R16F:
		case image_format::RGB16F:
		case image_format::RGBA16F:
			image_loader = stbi_loadf;
			break;
		default:
			break;
		}

		int component, width, height;
		m_data = image_loader(path.c_str(), &width, &height, &component, get_component(m_format));
		
		if (m_data != nullptr) {
			m_width = width;
			m_height = height;
		}
		else LOG_ERROR("load image failed from " + path);
	}

	image_asset::image_asset(
		int width,
		int height,
		image_format format) : m_width(width), m_height(height), m_format(format) {
		int data_len = get_data_len();
		m_data = malloc(data_len);
	}

	image_asset::image_asset(const image_asset& img) {
		m_width = img.m_width;
		m_height = img.m_height;
		m_format = img.m_format;
		int data_len = get_data_len();
		m_data = malloc(data_len);
		memcpy(m_data, img.m_data, data_len);
	}

	image_asset& image_asset::operator=(const image_asset& img) {
		if (this != &img) {
			if (!m_data) stbi_image_free(m_data);

			m_width = img.m_width;
			m_height = img.m_height;
			m_format = img.m_format;
			int data_len = get_data_len();
			m_data = malloc(data_len);
			memcpy(m_data, img.m_data, data_len);
		}
		return *this;
	}

	image_asset::~image_asset() {
		stbi_image_free(m_data);
	}

	int image_asset::get_component(image_format format) const {
		int component = 0;
		switch (format) {
		case image_format::R8B:
		case image_format::R16F:
			component = 1;
			break;
		case image_format::RGB8B:
		case image_format::RGB16F:
			component = 3;
			break;
		case image_format::RGBA8B:
		case image_format::RGBA16F:
			component = 4;
			break;
		default:
			break;
		}
		return component;
	}

	int image_asset::get_data_len() const {
		int data_len = 0;
		switch (m_format) {
		case image_format::R8B:
		case image_format::RGB8B:
		case image_format::RGBA8B:
			data_len = sizeof(char) * m_width * m_height * get_component(m_format);

			break;
		case image_format::R16F:
		case image_format::RGB16F:
		case image_format::RGBA16F:
			data_len = sizeof(float) * m_width * m_height * get_component(m_format);
			break;
		default:
			break;
		}
		return data_len;
	}

	int image_asset::get_data_index(int x, int y) const {
		if (x < 0 || x >= m_width || y < 0 || y >= m_height) return -1;

		return (y * m_width + x) * get_component(m_format);
	}

	void image_asset::save(const string& path) const {
		throw "not impl!";
	}

	void image_asset::set_data(const void* data) {
		int data_len = get_data_len();
		memcpy(m_data, data, data_len);
	}

	vec4 image_asset::sample_liner(vec2 uv) const {
		vec4 color = vec4(0.0, 0.0f, 0.0f, 0.0f);
		if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f) return color;

		float x = uv.x * (m_width - 1);
		float y = uv.y * (m_height - 1);
		float x_weight = x - int(x);
		float y_weight = y - int(y);
		int ld = get_data_index(int(x), int(y));
		int lu = get_data_index(int(x), int(y) + 1);
		int rd = get_data_index(int(x) + 1, int(y));
		int ru = get_data_index(int(x) + 1, int(y) + 1);

		if (m_format == image_format::R8B || m_format == image_format::RGB8B || m_format == image_format::RGBA8B) {
			float r_ld = ld < 0 ? 0.0f : *((unsigned char*)m_data + ld);
			float r_lu = lu < 0 ? 0.0f : *((unsigned char*)m_data + lu);
			float r_rd = rd < 0 ? 0.0f : *((unsigned char*)m_data + rd);
			float r_ru = ru < 0 ? 0.0f : *((unsigned char*)m_data + ru);
			color.r = (1.0f - y_weight) * ((1.0f - x_weight) * r_ld + x_weight * r_rd) + y_weight * ((1.0f - x_weight) * r_lu + x_weight * r_ru);
			if (get_component(m_format) >= 3) {
				float g_ld = ld < 0 ? 0.0f : *((unsigned char*)m_data + ld + 1);
				float g_lu = lu < 0 ? 0.0f : *((unsigned char*)m_data + lu + 1);
				float g_rd = rd < 0 ? 0.0f : *((unsigned char*)m_data + rd + 1);
				float g_ru = ru < 0 ? 0.0f : *((unsigned char*)m_data + ru + 1);
				color.g = (1.0f - y_weight) * ((1.0f - x_weight) * g_ld + x_weight * g_rd) + y_weight * ((1.0f - x_weight) * g_lu + x_weight * g_ru);

				float b_ld = ld < 0 ? 0.0f : *((unsigned char*)m_data + ld + 2);
				float b_lu = lu < 0 ? 0.0f : *((unsigned char*)m_data + lu + 2);
				float b_rd = rd < 0 ? 0.0f : *((unsigned char*)m_data + rd + 2);
				float b_ru = ru < 0 ? 0.0f : *((unsigned char*)m_data + ru + 2);
				color.b = (1.0f - y_weight) * ((1.0f - x_weight) * b_ld + x_weight * b_rd) + y_weight * ((1.0f - x_weight) * b_lu + x_weight * b_ru);
			}
			if (get_component(m_format) == 4) {
				float a_ld = ld < 0 ? 0.0f : *((unsigned char*)m_data + ld + 3);
				float a_lu = lu < 0 ? 0.0f : *((unsigned char*)m_data + lu + 3);
				float a_rd = rd < 0 ? 0.0f : *((unsigned char*)m_data + rd + 3);
				float a_ru = ru < 0 ? 0.0f : *((unsigned char*)m_data + ru + 3);
				color.a = (1.0f - y_weight) * ((1.0f - x_weight) * a_ld + x_weight * a_rd) + y_weight * ((1.0f - x_weight) * a_lu + x_weight * a_ru);
			}
			color = color / 255.0f;
		}

		if (m_format == image_format::R16F || m_format == image_format::RGB16F || m_format == image_format::RGBA16F) {
			float r_ld = ld < 0 ? 0.0f : *((float*)m_data + ld);
			float r_lu = lu < 0 ? 0.0f : *((float*)m_data + lu);
			float r_rd = rd < 0 ? 0.0f : *((float*)m_data + rd);
			float r_ru = ru < 0 ? 0.0f : *((float*)m_data + ru);
			color.r = (1.0f - y_weight) * ((1.0f - x_weight) * r_ld + x_weight * r_rd) + y_weight * ((1.0f - x_weight) * r_lu + x_weight * r_ru);
			if (get_component(m_format) >= 3) {
				float g_ld = ld < 0 ? 0.0f : *((float*)m_data + ld + 1);
				float g_lu = lu < 0 ? 0.0f : *((float*)m_data + lu + 1);
				float g_rd = rd < 0 ? 0.0f : *((float*)m_data + rd + 1);
				float g_ru = ru < 0 ? 0.0f : *((float*)m_data + ru + 1);
				color.g = (1.0f - y_weight) * ((1.0f - x_weight) * g_ld + x_weight * g_rd) + y_weight * ((1.0f - x_weight) * g_lu + x_weight * g_ru);

				float b_ld = ld < 0 ? 0.0f : *((float*)m_data + ld + 2);
				float b_lu = lu < 0 ? 0.0f : *((float*)m_data + lu + 2);
				float b_rd = rd < 0 ? 0.0f : *((float*)m_data + rd + 2);
				float b_ru = ru < 0 ? 0.0f : *((float*)m_data + ru + 2);
				color.b = (1.0f - y_weight) * ((1.0f - x_weight) * b_ld + x_weight * b_rd) + y_weight * ((1.0f - x_weight) * b_lu + x_weight * b_ru);
			}
			if (get_component(m_format) == 4) {
				float a_ld = ld < 0 ? 0.0f : *((float*)m_data + ld + 3);
				float a_lu = lu < 0 ? 0.0f : *((float*)m_data + lu + 3);
				float a_rd = rd < 0 ? 0.0f : *((float*)m_data + rd + 3);
				float a_ru = ru < 0 ? 0.0f : *((float*)m_data + ru + 3);
				color.a = (1.0f - y_weight) * ((1.0f - x_weight) * a_ld + x_weight * a_rd) + y_weight * ((1.0f - x_weight) * a_lu + x_weight * a_ru);
			}
		}

		return color;
	}
}