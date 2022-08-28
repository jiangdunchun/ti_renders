#include "object.h"

using namespace std;

namespace ti_engine {
	object::object(const string& name) : m_name(name) { }

	object::~object() {}

	void object::tick(float delta_time) {
		for (auto& cpt : m_components)
			if (cpt->need_tick()) cpt->tick(delta_time);
	}
}