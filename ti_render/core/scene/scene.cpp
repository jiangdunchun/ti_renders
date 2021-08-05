#include "scene.h"

#include <time.h>

using namespace std;
using namespace glm;

namespace ti_render {
	// 0-16 are reserved
	unsigned int scene::generate_id(void) {
		unsigned int id = rand() & 0xfffffff0;
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
		set_id(m_camera, m_camera_id);
	}

	scene::~scene() {
		dispose(m_root);
	}

	void scene::set_sky_hdr(const string& sky_hdr) {
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
		dummy_object* d_obj = new dummy_object();
		d_obj->set_parent(m_root);
		set_id(d_obj);
		return d_obj;
	}

	mesh_object* scene::create_mesh(const string& mesh_path) {
		mesh_object* m_obj = new mesh_object(mesh_path);
		m_mesh_objects.push_back(m_obj);

		m_obj->set_parent(m_root);
		set_id(m_obj);
		return m_obj;
	}

	point_light_object* scene::create_point_light(const vec3& intensity) {
		point_light_object* pl_obj = new point_light_object(intensity);
		pl_obj->set_parent(m_root);
		set_id(pl_obj);
		return pl_obj;
	}

	void scene::dispose(object* obj) {
		if (!obj) return;

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
		obj = nullptr;
	}
}