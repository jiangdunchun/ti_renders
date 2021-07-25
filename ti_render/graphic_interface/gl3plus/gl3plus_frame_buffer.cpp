#include "gl3plus_frame_buffer.h"

using namespace std;

namespace ti_render {
	gl3plus_frame_buffer::gl3plus_frame_buffer(
		unsigned width,
		unsigned height) : m_width(width), m_height(height) {
		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		glGenRenderbuffers(1, &m_ds_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_ds_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ds_RBO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	gl3plus_frame_buffer::~gl3plus_frame_buffer() {
		glDeleteRenderbuffers(1, &m_ds_RBO);
		glDeleteFramebuffers(1, &m_id);
	}

	void gl3plus_frame_buffer::attach_color_buffer(
		unsigned int attachment,
		gl3plus_texture_2d* texture, 
		unsigned int mipmap_layer) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + attachment,
			GL_TEXTURE_2D,
			texture->m_id,
			mipmap_layer);

		bool is_exist = false;
		for (vector<GLuint>::iterator iter = m_attachments.begin();
			iter != m_attachments.end();
			iter++) {
			if (*iter == GL_COLOR_ATTACHMENT0 + attachment) {
				is_exist = true;
				break;
			}
		}

		if (!is_exist) {
			m_attachments.push_back(GL_COLOR_ATTACHMENT0 + attachment);
			glDrawBuffers(m_attachments.size(), &m_attachments[0]);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void gl3plus_frame_buffer::attach_color_buffer(
		unsigned int attachment, 
		gl3plus_texture_cube* texture, 
		cubemap_face face, 
		unsigned int mipmap_layer) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + attachment,
			map_cubemap_face(face),
			texture->m_id,
			mipmap_layer);

		bool is_exist = false;
		for (vector<GLuint>::iterator iter = m_attachments.begin();
			iter != m_attachments.end();
			iter++) {
			if (*iter == GL_COLOR_ATTACHMENT0 + attachment) {
				is_exist = true;
				break;
			}
		}

		if (!is_exist) {
			m_attachments.push_back(GL_COLOR_ATTACHMENT0 + attachment);
			glDrawBuffers(m_attachments.size(), &m_attachments[0]);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void gl3plus_frame_buffer::detach_color_buffer(unsigned int attachment) {
		bool is_exist = false;
		for (vector<GLuint>::iterator iter = m_attachments.begin();
			iter != m_attachments.end();
			iter++) {
			if (*iter == GL_COLOR_ATTACHMENT0 + attachment) {
				is_exist = true;
				m_attachments.erase(iter);
				break;
			}
		}

		if (is_exist) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0 + attachment,
				GL_TEXTURE_2D,
				0,
				0);
			glDrawBuffers(m_attachments.size(), &m_attachments[0]);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void gl3plus_frame_buffer::bind(void) const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}

	void gl3plus_frame_buffer::unbind(void) const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}


