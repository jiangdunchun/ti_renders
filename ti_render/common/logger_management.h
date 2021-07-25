#ifndef __LOGGER_MANAGEMENT_H__
#define __LOGGER_MANAGEMENT_H__

#include <vector>

#include "i_logger.h"

namespace ti_render {
	class logger_management {
	private:
		static std::vector<i_logger*> sm_logger_pool;

	public:
		static void attach_logger(i_logger* logger);
		static void detach_logger(i_logger* logger);
		static void log(log_tag tag, std::string msg);
	};
}

#endif // !__LOGGER_MANAGEMENT_H__
