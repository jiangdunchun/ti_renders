#include "render.h"

#include <time.h>

#include "core/file/file_common.h"

using namespace std;

namespace ti_render {
	render_system* render::m_render_system = nullptr;
	pass_management* render::m_pass_management = nullptr;
	float render::m_tick = 0.0f;
	vector<void(*)(void)> render::m_pre_update_funcs = {};
	vector<void(*)(void)> render::m_post_update_funcs = {};

	void render::invoke_pre_update_funcs(void) {
		for (vector<void(*)(void)>::iterator iter = m_pre_update_funcs.begin();
			iter != m_pre_update_funcs.end();
			++iter) {
			(*iter)();
		}
	}

	void render::invoke_post_update_funcs(void) {
		for (vector<void(*)(void)>::iterator iter = m_post_update_funcs.begin();
			iter != m_post_update_funcs.end();
			++iter) {
			(*iter)();
		}
	}

	void render::add_pre_update_func(void(*func_ptr)(void)) {
		for (vector<void(*)(void)>::iterator iter = m_pre_update_funcs.begin();
			iter != m_pre_update_funcs.end();
			++iter) {
			if (func_ptr == (*iter)) return;
		}
		m_pre_update_funcs.push_back(func_ptr);
	}

	void render::remove_pre_update_func(void(*func_ptr)(void)) {
		for (vector<void(*)(void)>::iterator iter = m_pre_update_funcs.begin();
			iter != m_pre_update_funcs.end();
			++iter) {
			if (func_ptr == (*iter)) {
				m_pre_update_funcs.erase(iter);
				return;
			}
		}
	}

	void render::add_post_update_func(void(*func_ptr)(void)) {
		for (vector<void(*)(void)>::iterator iter = m_post_update_funcs.begin();
			iter != m_post_update_funcs.end();
			++iter) {
			if (func_ptr == (*iter)) return;
		}
		m_post_update_funcs.push_back(func_ptr);
	}

	void render::remove_post_update_func(void(*func_ptr)(void)) {
		for (vector<void(*)(void)>::iterator iter = m_post_update_funcs.begin();
			iter != m_post_update_funcs.end();
			++iter) {
			if (func_ptr == (*iter)) {
				m_post_update_funcs.erase(iter);
				return;
			}
		}
	}

	void render::init(unsigned int width, unsigned int height, const string& name, const std::string& resource_path) {
		file_common::set_resource_path(resource_path);

		m_render_system = new render_system();
		m_render_system->init(width, height, name);

		m_pass_management = new pass_management(width, height);
	}

	void render::run(scene* scene_ptr) {
		clock_t start, end;
		while (m_render_system->is_active()) {
			start = clock();
			invoke_pre_update_funcs();
			m_render_system->pre_rend_one_frame();

			m_pass_management->rend(m_render_system, scene_ptr);

			m_render_system->post_rend_one_frame();
			invoke_post_update_funcs();
			end = clock();
			m_tick = float(end - start) / 1000.0f;
		}

		m_render_system->shutdown();
	}
}