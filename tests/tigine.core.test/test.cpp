#include <iostream>
#include <tigine.core/common/logger_mgr.h>
#include <tigine.core/asset/image_asset.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

using namespace tigine;
using namespace std;

class my_logger : public i_logger {
public:
	void log(log_tag tag, string msg) {
		cout << "[";
		if (tag == log_tag::DEBUG)
			cout << GREEN << "DEBUG" << RESET << "] ";
		else if (tag == log_tag::WARN)
			cout << YELLOW << "WARN" << RESET << "] ";
		else if (tag == log_tag::ERROR)
			cout << RED << "ERROR" << RESET << "] ";
		cout << msg << endl;
	}
};

void image_asset_test() {
	image_asset img("./assets/GGX_E_IS_LUT.png", image_format::RGB8B);
	string img_info = "GGX_E_IS_LUT.png---> \n";
	img_info += ("width:" + to_string(img.get_width()) + ", height:" + to_string(img.get_height()) + "\n");
	LOG_DEBUG(img_info);
}

int main() {
	i_logger* logger = new my_logger();
	logger_mgr::attach_logger(logger);
	LOG_DEBUG("init logger");

	image_asset_test();

	delete logger;
}