#include "scene.h"

#include <time.h>

using namespace std;

namespace ti_render {
	// 0-16 are reserved
	unsigned int scene::generate_id(void) {
		unsigned int id = rand() % 0xfffffff0;
		while (find_object(id)) {
			return generate_id();
		}
		return id;
	}

	object* scene::find_object(unsigned int id) {
		map<unsigned int, object*>::iterator id_iter = m_id_pool.find(id);

		if (id_iter == m_id_pool.end()) return nullptr;
		else return id_iter->second;
	}

	void scene::set_id(object* object_ptr, unsigned int id) {
		if (find_object(id)) {
			id = generate_id();
		}
		object_ptr->m_id = id;
		m_id_pool[id] = object_ptr;
	}

	scene::scene() {
		m_root = new dummy_object();
		set_id(m_root, m_root_id);

		m_camera = new camera_object(45.0f, 1.0f);
		m_camera->set_parent(m_root);
		set_id(m_root, m_camera_id);
	}

	scene::~scene() {
		dispose(m_root);
	}

	void scene::set_sky_hdr(const std::string& sky_hdr) {
		const dummy_object* parent = m_root;
		if (m_sky) {
			parent = m_sky->get_parent();
			dispose(m_sky);
		}
		else {
			m_sky = new sky_object(sky_hdr);
			m_sky->set_parent(const_cast<dummy_object*>(parent));
			set_id(m_sky, m_sky_id);
		}
	}

	dummy_object* scene::create_dummy(void) {
		dummy_object* n_obj = new dummy_object();
		n_obj->set_parent(m_root);
		set_id(n_obj);
		return n_obj;
	}

	void scene::dispose(object* obj) {
		if (obj->m_parent) {
			for (vector<object*>::iterator iter = obj->m_parent->m_children.begin();
				iter != obj->m_parent->m_children.end();
				++iter) {
				obj->m_parent->m_children.erase(iter);
				break;
			}
		}
		vector<object*> obj_buffer;
		obj_buffer.push_back(obj);
		if (obj->get_type() == object_type::DUMMY_OBJECT) {
			(dynamic_cast<dummy_object*>(obj))->tranverse_children(obj_buffer);
		}

		for (vector<object*>::iterator iter = obj_buffer.begin();
			iter != obj_buffer.end();
			++iter) {
			m_id_pool.erase((*iter)->get_id());
		}

		delete obj;
	}
}