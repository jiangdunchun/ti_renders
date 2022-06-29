#include "logger_mgr.h"

using namespace std;

namespace tigine {
	vector<i_logger*> logger_mgr::sm_logger_pool = {};

	void logger_mgr::attach_logger(i_logger* logger) {
        auto iter = find(sm_logger_pool.begin(), sm_logger_pool.end(), logger);
        if (iter == sm_logger_pool.end()) sm_logger_pool.push_back(logger);
	}

	void logger_mgr::detach_logger(i_logger* logger) {
		auto iter = find(sm_logger_pool.begin(), sm_logger_pool.end(), logger);
        if (iter != sm_logger_pool.end()) sm_logger_pool.erase(iter);
	}

	void logger_mgr::log(log_tag tag, string msg) {
        for (auto& logger : sm_logger_pool) logger->log(tag, msg);
	}
}