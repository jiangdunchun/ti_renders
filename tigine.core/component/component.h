#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace tigine {
	class object;
	class component {
	private:
		object* m_parent = nullptr;

	public:
		virtual ~component() = 0 {};

		void set_parent(object* parent) {
			m_parent = parent;
		}
		virtual void tick(float delta_time) {};
		virtual void set_tick(bool flag) {};
		virtual bool need_tick() { return false; };
	};
}

#endif // !__COMPONENT_H__
