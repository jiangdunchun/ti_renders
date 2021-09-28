#include "emissive_pass.h"

#include "../file/shader_file.h"

using namespace std;
using namespace glm;

namespace ti_render {
	emissive_pass::emissive_pass(unsigned int width, unsigned int height, texture_2d* emissive) {
		shader_file s_file(m_shader_path);
		m_shader = new compute_shader(s_file.get_compute_code());

		m_emissive_in = emissive;

		m_emissive_h = new texture_2d(width, height, color_format::RGBA16F);
		m_emissive_v = new texture_2d(width, height, color_format::RGBA16F);
	}

	emissive_pass::~emissive_pass() {
		delete m_shader;
		delete m_emissive_h;
		delete m_emissive_v;
	}

	void emissive_pass::rend(render_system* render) {
		m_shader->use();
		m_shader->bind_texture(0, m_emissive_in, (int)access_type::READ);
		m_shader->bind_texture(1, m_emissive_h, (int)access_type::WRITE);
		m_shader->set_int("u_Direction", 0);
		m_shader->compute(m_emissive_h->get_width(), m_emissive_h->get_height(), 1);

		m_shader->bind_texture(0, m_emissive_h, (int)access_type::READ);
		m_shader->bind_texture(1, m_emissive_v, (int)access_type::WRITE);
		m_shader->set_int("u_Direction", 1);
		m_shader->compute(m_emissive_h->get_width(), m_emissive_h->get_height(), 1);

		for (int i = 0; i < 2; i++) {
			m_shader->bind_texture(0, m_emissive_v, (int)access_type::READ);
			m_shader->bind_texture(1, m_emissive_h, (int)access_type::WRITE);
			m_shader->set_int("u_Direction", 0);
			m_shader->compute(m_emissive_h->get_width(), m_emissive_h->get_height(), 1);

			m_shader->bind_texture(0, m_emissive_h, (int)access_type::READ);
			m_shader->bind_texture(1, m_emissive_v, (int)access_type::WRITE);
			m_shader->set_int("u_Direction", 1);
			m_shader->compute(m_emissive_h->get_width(), m_emissive_h->get_height(), 1);
		}
	}
}