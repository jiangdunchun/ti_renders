#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "../component/component.h"

namespace tigine {
	class object : public std::enable_shared_from_this<object> {
	private:
		std::string m_name;
		std::vector<std::shared_ptr<component>> m_components;

	public:
		object(const std::string& name) : m_name(name) {}
		virtual ~object() {}
		std::string& get_name() {
			return m_name;
		}
		template<class TComponent>
		std::shared_ptr<TComponent> get_component_(const type_info& cpt_info) {
			for (auto& cpt : m_components)
				if (typeid(*cpt) == cpt_info)
					return std::static_pointer_cast<TComponent>(cpt);

			return nullptr;
		}
#define get_component(COMPONENT_TYPE) get_component_<COMPONENT_TYPE>(typeid(COMPONENT_TYPE))
		template<class TComponent>
		bool add_component_() {
			if (get_component(TComponent))
				return false;

			std::shared_ptr<component> cpt(new TComponent());
			cpt->set_parent(weak_from_this());
			m_components.push_back(cpt);
			return true;
		}
#define add_component(COMPONENT_TYPE) add_component_<COMPONENT_TYPE>()
		template<class TComponent>
		void remove_component_(const type_info& cpt_info) {
			for (auto& iter = m_components.begin(); iter != m_components.end(); iter++) {
				if (typeid(*cpt) == cpt_info) {
					m_components.erase(iter);
					return;
				}
			}
		}
#define remove_component(COMPONENT_TYPE) remove_component_<COMPONENT_TYPE>(typeid(COMPONENT_TYPE))
		void tick(float delta_time);
	};
}

#endif // !__OBJECT_H__
