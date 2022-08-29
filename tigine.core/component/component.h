#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <memory>

namespace tigine {
	class object;
	class component {
	private:
		std::weak_ptr<object> m_parent;

	public:
		component() = default;
		virtual ~component() = 0 {};

		void set_parent(std::weak_ptr<object> parent) {
			m_parent = parent;
		}
		virtual void tick(float delta_time) {};
		virtual void set_tick(bool flag) {};
		virtual bool need_tick() { return false; };
	};
}

#endif // !__COMPONENT_H__
