#include "scene.h"

#include <time.h>

using namespace std;

namespace ti_render {
	scene::scene() {
		m_root = new dummy_object();

		m_camera = new camera_object(45.0f, 1.0f);
		m_camera->set_parent(m_root);
	}

	scene::~scene() {
		delete m_root;
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
		}
	}

	dummy_object* scene::create_dummy(void) {
		dummy_object* n_obj = new dummy_object();
		n_obj->set_parent(m_root);
		return n_obj;
	}

	void scene::dispose(object* obj) {
		if (obj->m_parent) {
			for (
				vector<object*>::iterator iter = obj->m_parent->m_children.begin();
				iter != obj->m_parent->m_children.end();
				++iter) {
				obj->m_parent->m_children.erase(iter);
				break;
			}
		}
		delete obj;
	}
}