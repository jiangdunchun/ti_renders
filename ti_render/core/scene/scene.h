#ifndef __SCENE_H__
#define __SCENE_H__

#include <map>

#include "../object/dummy_object.h"
#include "../object/camera_object.h"
#include "../object/sky_object.h"
#include "../object/mesh_object.h"
#include "../object/point_light_object.h"

namespace ti_render {
	class scene {
	friend class object;
	friend class pass_management;

	private:
		std::map<unsigned int, object*> m_id_pool;

		unsigned int generate_id(void);
		object* find_object(unsigned int id);
		void set_id(object* obj, unsigned int id = 0);

	protected:
		unsigned int m_root_id = 0;
		dummy_object* m_root;
		unsigned int m_camera_id = 1;
		camera_object* m_camera;
		unsigned int m_sky_id = 2;
		sky_object* m_sky = nullptr;
		std::vector<mesh_object*> m_mesh_objects;

	public:
		scene();
		virtual ~scene();

		const dummy_object* get_root(void) const {
			return m_root;
		}
		camera_object* get_camera(void) const {
			return m_camera;
		}
		void set_sky_hdr(const std::string& sky_hdr);
		dummy_object* create_dummy(void);
		mesh_object* create_mesh(const std::string& mesh_path);
		point_light_object* create_point_light(const glm::vec3& intensity);
		void dispose(object* obj);
	};
}

#endif

