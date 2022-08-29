#include "object.h"

using namespace std;

namespace tigine {
	void object::tick(float delta_time) {
		for (auto& cpt : m_components)
			if (cpt->need_tick()) cpt->tick(delta_time);
	}
}