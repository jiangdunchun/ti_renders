#include "logger_management.h"

using namespace std;

namespace ti_render {
	std::vector<i_logger*> logger_management::sm_logger_pool = {};

	void logger_management::attach_logger(i_logger* logger) {
		for (vector<i_logger*>::iterator iter = sm_logger_pool.begin();
			iter != sm_logger_pool.end();
			++iter) {
			if ((*iter) == logger) return;
		}
		sm_logger_pool.push_back(logger);
	}

	void logger_management::detach_logger(i_logger* logger) {
		for (vector<i_logger*>::iterator iter = sm_logger_pool.begin();
			iter != sm_logger_pool.end();
			++iter) {
			if ((*iter) == logger) {
				sm_logger_pool.erase(iter);
				return;
			}
		}
	}

	void logger_management::log(log_tag tag, std::string msg) {
		for (vector<i_logger*>::iterator iter = sm_logger_pool.begin();
			iter != sm_logger_pool.end();
			++iter) {
			(*iter)->log(tag, msg);
		}
	}
}