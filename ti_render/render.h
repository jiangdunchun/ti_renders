#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "./core/scene/scene.h"
#include "./core/pass/pass_management.h"

namespace ti_render {
	class render {
	private:
		static scene* m_scene;
		static render_system* m_render_system;
		static pass_management* m_pass_management;
		static float m_tick;
		static std::vector<void(*)(void)> m_pre_update_funcs;
		static std::vector<void(*)(void)> m_post_update_funcs;

		static void invoke_pre_update_funcs(void);
		static void invoke_post_update_funcs(void);

	public:
		static scene* get_scene(void) {
			return m_scene;
		}
		static void set_scene(scene* scene_ptr) {
			 m_scene = scene_ptr;
		}
		static float get_tick(void) {
			return m_tick;
		}

		static void add_pre_update_func(void(*func_ptr)(void));
		static void remove_pre_update_func(void(*func_ptr)(void));
		static void add_post_update_func(void(*func_ptr)(void));
		static void remove_post_update_func(void(*func_ptr)(void));

		static void init(unsigned int width, unsigned int height, const std::string& name);
		static void run(void);
	};
}

#endif // !__ENGINE_H__
