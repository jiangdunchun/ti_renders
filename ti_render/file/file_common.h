#ifndef __FILE_COMMON_H__
#define __FILE_COMMON_H__

#include <string>

namespace ti_render {
	class file_common {
	private:
		static std::string ms_resource_path;
	public:
		static void set_resource_path(const std::string& path);
		static std::string get_file_path(const std::string& path);
	};
}

#endif // !__FILE_COMMON_H__

