#ifndef m__OBJECT_H__
#define m__OBJECT_H__

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace ti_render {
	enum class object_type {
		DUMMY_OBJECT,
		CAMERA_OBJECT,
		SKY_OBJECT,
		POINT_LIGHT,
		ENVIRONMENT_LIGHT,
		PARALLEL_LIGHT,
		MESH_OBJECT
	};

	class dummy_object;

	class object {
	friend class scene;
	friend class dummy_object;

	private:
		unsigned int m_id;
		dummy_object* m_parent;

	protected:
		glm::vec3 m_postion;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::mat4 m_transform;
		object_type m_type;

		void update_transform(void);

		object();
		virtual ~object();

	public:
		const object_type& get_type(void) const {
			return m_type;
		}
		const unsigned int& get_id(void) const {
			return m_id;
		}
		const dummy_object* get_parent(void) const;
		void set_parent(dummy_object* parent);
		glm::vec3 get_local_position(void) const {
			return m_postion;
		}
		glm::vec3 get_local_rotation(void) const {
			return m_rotation;
		}
		glm::vec3 get_local_scale(void) const {
			return m_scale;
		}
		glm::mat4 get_local_transform(void) const {
			return m_transform;
		}
		glm::vec3 get_world_position(void) const;
		glm::vec3 get_world_rotation(void) const;
		glm::vec3 get_world_scale(void) const;
		glm::mat4 get_world_transform(void) const;
		void set_local_position(const glm::vec3& position);
		void set_local_rotation(const glm::vec3& rotation);
		void set_local_scale(const glm::vec3& scale);
	};
}


#endif // !__OBJECT_H__

