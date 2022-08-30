#ifndef __I_LOGGER_H__
#define __I_LOGGER_H__

#include <string>

namespace ti_render {
	enum class log_tag {
		LOG_DEBUG = 1 << 0,
		LOG_WARNING = 2 << 1,
		LOG_ERROR = 3 << 1,
	};

	class i_logger {
	public:
		virtual void log(log_tag tag, std::string msg) = 0;
	};
}

#endif // !__I_LOGGER_H__

