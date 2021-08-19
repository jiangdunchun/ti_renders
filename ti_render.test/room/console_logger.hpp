#ifndef __CONSOLE_LOGGER_HPP__
#define __CONSOLE_LOGGER_HPP__

#include <iostream>
#include <time.h>

#include <common/i_logger.h>

class console_logger : public ti_render::i_logger {
public:
	void log(ti_render::log_tag tag, std::string msg) {
		// @TODO: https://blog.csdn.net/qq_41972382/article/details/90311102
		std::string tag_str = "";
		switch (tag) {
		case ti_render::log_tag::LOG_DEBUG:
			tag_str = "DEBUG";
			break;
		case ti_render::log_tag::LOG_WARNING:
			tag_str = "WARNING";
			break;
		case ti_render::log_tag::LOG_ERROR:
			tag_str = "ERROR";
			break;
		}
		std::cout << clock() << ":[" << tag_str << "]" << msg << std::endl;
	}
};

#endif // !__CONSOLE_LOGGER_HPP__
