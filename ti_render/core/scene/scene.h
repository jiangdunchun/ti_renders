#ifndef __SCENE_H__
#define __SCENE_H__

#include <map>

#include "../object/dummy_object.h"
#include "../object/camera_object.h"
#include "../object/sky_object.h"

namespace ti_render {
	class scene {
	friend class object;

	private:
		std::map<unsigned int, object*> m_id_pool;

		unsigned int generate_id(void);
		object* find_object(unsigned int id);
		void set_id(object* obj, unsigned int id = 0);

	protected:
		dummy_object* m_root;
		camera_object* m_camera;
		sky_object* m_sky = nullptr;

	public:
		scene();
		virtual ~scene();

		const dummy_object* get_root(void) const {
			return m_root;
		}
		const camera_object* get_camera(void) const {
			return m_camera;
		}
		void set_sky_hdr(const std::string& sky_hdr);
		dummy_object* create_dummy(void);
		void dispose(object* obj);
	};
}

#endif

