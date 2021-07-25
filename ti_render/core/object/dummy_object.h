#ifndef __DUMMY_OBJECT_H__
#define __DUMMY_OBJECT_H__

#include <vector>

#include "object.h"

namespace ti_render {
	class dummy_object : public object {
	friend class scene;
	friend class object;

	private:
		std::vector<object*> m_children;

		dummy_object();
		~dummy_object();

	public:
		const std::vector<object*>& get_children(void) const {
			return m_children;
		}
	};
}

#endif // !__DUMMY_OBJECT_H__

