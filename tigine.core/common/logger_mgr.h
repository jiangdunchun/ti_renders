#ifndef __LOGGER_MGR_H__
#define __LOGGER_MGR_H__

#include <string>

namespace tigine{
    enum class log_tag {
		DEBUG,
		WARN,
		ERROR
	};

	class i_logger {
	public:
		virtual void log(log_tag tag, std::string msg) = 0;
	};

    class logger_mgr {
	private:
		static std::vector<i_logger*> sm_logger_pool;

	public:
		static void attach_logger(i_logger* logger);
		static void detach_logger(i_logger* logger);
		static void log(log_tag tag, std::string msg);
	};
}

#define LOG_HELPER(LOG_LEVEL, ...) \
    tigine::logger_mgr::log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(tigine::log_tag::DEBUG, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(tigine::log_tag::WARN, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(tigine::log_tag::ERROR, __VA_ARGS__);

#endif