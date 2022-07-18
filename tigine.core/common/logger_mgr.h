#ifndef __LOGGER_MGR_H__
#define __LOGGER_MGR_H__

#include <string>
#include <vector>
#include <cstdarg>

namespace tigine{
    enum class log_tag {
		DEBUG,
		WARN,
		ERROR
	};

	class i_logger {
	public:
		virtual ~i_logger() {};
		virtual void log(log_tag tag, std::string msg) = 0;
	};

    class logger_mgr {
	private:
		static std::vector<i_logger*> sm_logger_pool;

	public:
		static void attach_logger(i_logger* logger);
		static void detach_logger(i_logger* logger);
		static void log(log_tag tag, std::string msg);
		static std::string format_string(const char* format, ...);
		static std::string format_string(std::string& log_info);
	};
}

#define MAX_LOG_CONTENT_LEN 2048

;


#define LOG_HELPER(LOG_TAG, LOG_INFO) \
    tigine::logger_mgr::log(LOG_TAG, "[" + std::string(__FUNCTION__) + "] " + LOG_INFO);

#define LOG_DEBUG(...) LOG_HELPER(tigine::log_tag::DEBUG, logger_mgr::format_string(__VA_ARGS__));

#define LOG_WARN(...) LOG_HELPER(tigine::log_tag::WARN, logger_mgr::format_string(__VA_ARGS__));

#define LOG_ERROR(...) LOG_HELPER(tigine::log_tag::ERROR, logger_mgr::format_string(__VA_ARGS__));

#endif