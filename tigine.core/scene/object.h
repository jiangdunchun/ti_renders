#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "../component/component.h"

namespace ti_engine {
	class object {
	private:
		std::string m_name;
		std::vector<std::shared_ptr<component>> m_components;

	public:
		object(const std::string& name);
		virtual ~object() = 0;
		std::string& get_name() {
			return m_name;
		}
		template<class TComponent>
		std::shared_ptr<TComponent> get_component_(const std::string& cpt_name); // std::static_pointer_cast<TComponent>()
#define get_component(COMPONENT_TYPE) get_component_<COMPONENT_TYPE>(#COMPONENT_TYPE)
		bool add_component(const std::string& cpt_name);
		void remove_component(const std::string& cpt_name);
		void tick(float delta_time);
	};
}

#endif // !__OBJECT_H__
