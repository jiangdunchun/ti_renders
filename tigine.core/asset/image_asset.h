#ifndef __IMAGE_ASSET_H__
#define __IMAGE_ASSET_H__

#include <string>
#include <glm/glm.hpp>
#include <memory>

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
		int m_width = 0;
		int m_height = 0;
		image_format m_format;
		void* m_data = nullptr;

		int get_data_len() const;
		int get_data_index(int x, int y) const;

	public:
		image_asset(int width, int height, image_format format);
    	image_asset(const image_asset& img);
		image_asset& operator=(const image_asset& img);
		~image_asset();

		static std::unique_ptr<image_asset> load(const std::string& path, image_format format, bool flip_y = true);
		// png && (R8B || RGB8B || RGBA8B)
		void save(const std::string& path, bool flip_y = true) const;
		int get_width(void) const {
			return m_width;
		}
		int get_height(void) const {
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