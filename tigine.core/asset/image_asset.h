#ifndef __IMAGE_ASSET_H__
#define __IMAGE_ASSET_H__

#include <string>
#include <glm/glm.hpp>

namespace tigine {
	enum class image_format {
		R8B,
		RGB8B,
		RGBA8B,
		R16F,
		RGB16F,
		RGBA16F
	};

    class image_asset {
	private:
		uint32_t m_component;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		image_format m_format;
		void* m_data = nullptr;

	public:
		image_asset(const std::string& path, image_format format, bool flip_y = true);
		image_asset(uint32_t width, uint32_t height, image_format format);
    	image_asset(const image_asset& img) = delete;
		image_asset& operator=(const image_asset& img) = delete;
		~image_asset();

		static uint32_t get_component(image_format format);
		size_t get_data_index(uint32_t x, uint32_t y) const;
		void save(const std::string& path) const;
		uint32_t get_width(void) const {
			return m_width;
		}
		uint32_t get_height(void) const {
			return m_height;
		}
		image_format get_format(void) {
			return m_format;
		}
		void set_data(const void* data);
		const void* const get_data(void) {
			return m_data;
		}
		glm::vec4 sample_liner(glm::vec2 uv) const;
	};
}

#endif