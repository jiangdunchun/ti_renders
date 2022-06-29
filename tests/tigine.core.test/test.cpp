#include <iostream>
#include <tigine.core/common/logger_mgr.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

class my_logger : public tigine::i_logger {
public:
	void log(tigine::log_tag tag, std::string msg) {
		std::cout << "[";
		if (tag == tigine::log_tag::DEBUG)
			std::cout << GREEN << "DEBUG" << RESET << "] ";
		else if (tag == tigine::log_tag::WARN)
			std::cout << YELLOW << "WARN" << RESET << "] ";
		else if (tag == tigine::log_tag::ERROR)
			std::cout << RED << "ERROR" << RESET << "] ";
		std::cout << msg << std::endl;
	}
};

int main() {
	tigine::i_logger* logger = new my_logger();
	tigine::logger_mgr::attach_logger(logger);
	LOG_DEBUG("init logger");

	delete logger;
}