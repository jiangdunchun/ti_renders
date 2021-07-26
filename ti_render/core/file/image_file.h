#ifndef __IMAGE_FILE_H__
#define __IMAGE_FILE_H__

#include <string>
#include <map>

#include "../../common/tr_enum.h"

namespace ti_render {
	class image_file {
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		color_format m_format;
		void* m_data = nullptr;

	public:
		image_file(const std::string& path, color_format format);
		image_file(unsigned int width, unsigned int height, color_format format);
		~image_file();

		void save(const std::string& path) const;
		const unsigned int& get_width(void) const {
			return m_width;
		}
		const unsigned int& get_height(void) const {
			return m_height;
		}
		const color_format& get_color_format(void) {
			return m_format;
		}
		void set_data(const void* data);
		const void* get_data(void) {
			return m_data;
		}
	};
}

#endif // !__IMAGE_FILE_H__

