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
		unsigned int m_component;
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		image_format m_format;
		void* m_data = nullptr;

	public:
		image_asset(const std::string& path, image_format format, bool flip_y = true);
		image_asset(unsigned int width, unsigned int height, image_format format);
    	image_asset(const image_asset& img) = delete;
		image_asset& operator=(const image_asset& img) = delete;
		~image_asset();

		static unsigned int get_component(image_format format);
		int get_data_index(unsigned int x, unsigned int y) const;
		void save(const std::string& path) const;
		unsigned int get_width(void) const {
			return m_width;
		}
		unsigned int get_height(void) const {
			return m_height;
		}
		image_format get_format(void) {
			return m_format;
		}
		void set_data(void* const data);
		void* const get_data(void) {
			return m_data;
		}
		glm::vec4 sample_liner(glm::vec2 uv) const;
	};
}

#endif