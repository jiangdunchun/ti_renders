#include "dummy_object.h"

using namespace std;

namespace ti_render {
	dummy_object::dummy_object() : object() {
		m_type = object_type::DUMMY_OBJECT;
	}

	dummy_object::~dummy_object() {
		for (vector<object*>::iterator iter = m_children.begin();
			iter != m_children.end();
			++iter) {
			delete *iter;
		}
	}
	void dummy_object::tranverse_children(std::vector<object*>& buffer) {
		for (vector<object*>::iterator iter = m_children.begin();
			iter != m_children.end();
			++iter) {
			buffer.push_back(*iter);
			if ((*iter)->get_type() == object_type::DUMMY_OBJECT) {
				(dynamic_cast<dummy_object*>(*iter))->tranverse_children(buffer);
			}
		}
	}
}