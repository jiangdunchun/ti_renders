#include "object.h"

using namespace std;

namespace tigine {
	object::object(const std::string& name) : m_name(name) {
	}

	object::~object() {
		for(auto& cpt : m_components) delete cpt;
	}

	object::object(const object& obj) {
		// @TODO
	}

	object& object::operator=(const object& obj) {
		if (this != &obj) {
			// @TODO
		}
		return *this;
	}

	void object::tick(float delta_time) {
		for (auto& cpt : m_components)
			if (cpt->need_tick()) cpt->tick(delta_time);
	}
}