#include "sky_pass.h"

using namespace std;
using namespace glm;

namespace ti_render {
    void sky_pass::rend_environment(render_system* render, texture_2d* hdr, texture_cube*& environment) {
        unsigned int resolution = hdr->get_width() / 2;
        environment = new texture_cube(resolution, resolution, color_format::RGB16F);
        frame_buffer fbo(resolution, resolution);

        fbo.bind();
        render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
        render->set(graphic_capability::DEPTH_TEST, true);
        render->set(graphic_func::DEPTH_MASK, true);
        render->set_depth_func(depth_func::LESS);

        m_hdr2env_shader->use();
        m_hdr2env_shader->set_mat4("uProjection", m_projection);
        m_hdr2env_shader->set_texture_2d("uHDR", *hdr);
        for (unsigned int i = 0; i < m_cube_views.size(); ++i) {
            m_hdr2env_shader->set_mat4("uView", m_cube_views[i]);
            fbo.attach_color_buffer(0, environment, cubemap_face(int(cubemap_face::POSITIVE_X) + i));
            render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

            m_cube_mesh->draw();
        }
    }

    void sky_pass::rend_diffuse(render_system* render, texture_cube* environment, texture_cube*& diffuse) {
        unsigned int resolution = 32;
        diffuse = new texture_cube(resolution, resolution, color_format::RGB16F);
        frame_buffer fbo(resolution, resolution);

        fbo.bind();
        render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
        render->set(graphic_capability::DEPTH_TEST, true);
        render->set(graphic_func::DEPTH_MASK, true);
        render->set_depth_func(depth_func::LESS);

        m_hdr2env_shader->use();
        m_hdr2env_shader->set_mat4("uProjection", m_projection);
        m_hdr2env_shader->set_texture_cube("uEnvironment", *environment);
        for (unsigned int i = 0; i < m_cube_views.size(); ++i) {
            m_hdr2env_shader->set_mat4("uView", m_cube_views[i]);
            fbo.attach_color_buffer(0, diffuse, cubemap_face(int(cubemap_face::NEGATIVE_X) + i));
            render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

            m_cube_mesh->draw();
        }
    }

    void sky_pass::rend_specular(render_system* render, texture_cube* environment, texture_cube*& specular) {
        unsigned int resolution = 512;
        specular = new texture_cube(resolution, resolution, color_format::RGB16F, true);

        m_env2specular_shader->use();
        m_env2specular_shader->set_mat4("uProjection", m_projection);
        m_env2specular_shader->set_texture_cube("uEnvironment", *environment);

        unsigned int maxMipLevels = 5;
        for (unsigned int level = 0; level < maxMipLevels; level++) {
            float roughness = (float)level / (float)(maxMipLevels - 1);
            m_env2specular_shader->set_float("uRoughness", roughness);

            unsigned int layer_resolution = specular->get_width(level);
            frame_buffer fbo(layer_resolution, layer_resolution);

            fbo.bind();
            render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
            render->set(graphic_capability::DEPTH_TEST, true);
            render->set(graphic_func::DEPTH_MASK, true);
            render->set_depth_func(depth_func::LESS);
            for (unsigned int i = 0; i < m_cube_views.size(); ++i) {
                m_hdr2env_shader->set_mat4("uView", m_cube_views[i]);
                fbo.attach_color_buffer(0, specular, cubemap_face(int(cubemap_face::NEGATIVE_X) + i), level);
                render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

                m_cube_mesh->draw();
            }
        }
    }

    sky_pass::sky_pass(unsigned int width, unsigned int height) {
        shader_file hdr2cube_file(m_hdr2env_shader_path);
        m_hdr2env_shader = new shader(hdr2cube_file.get_vertex_code(), hdr2cube_file.get_fragment_code());

        shader_file env2diffuse_file(m_env2diffuse_shader_path);
        m_env2diffuse_shader = new shader(env2diffuse_file.get_vertex_code(), env2diffuse_file.get_fragment_code());

        shader_file env2specular_file(m_env2specular_shader_path);
        m_env2specular_shader = new shader(env2specular_file.get_vertex_code(), env2specular_file.get_fragment_code());

        shader_file env2background_file(m_env2background_shader_path);
        m_env2background_shader = new shader(env2background_file.get_vertex_code(), env2background_file.get_fragment_code());

		m_backgroud = new texture_2d(width, height, color_format::RGBA16F);
		m_backgroud_frame_buffer = new frame_buffer(width, height);
        m_backgroud_frame_buffer->attach_color_buffer(0, m_backgroud);

        vector<vertex> vertices = {
            //front
            {vec3(-1.0f, -1.0f, -1.0f)},
            {vec3(1.0f, -1.0f, -1.0f)},
            {vec3(1.0f,  1.0f, -1.0f)},
            {vec3(-1.0f,  1.0f, -1.0f)},
            //back
            {vec3(1.0f, -1.0f,  1.0f)},
            {vec3(-1.0f, -1.0f,  1.0f)},
            {vec3(-1.0f,  1.0f,  1.0f)},
            {vec3(1.0f,  1.0f,  1.0f)},
            //left
            {vec3(-1.0f, -1.0f,  1.0f)},
            {vec3(-1.0f, -1.0f, -1.0f)},
            {vec3(-1.0f,  1.0f, -1.0f)},
            {vec3(-1.0f,  1.0f,  1.0f)},
            //right
            {vec3(1.0f, -1.0f, -1.0f)},
            {vec3(1.0f, -1.0f,  1.0f)},
            {vec3(1.0f,  1.0f,  1.0f)},
            {vec3(1.0f,  1.0f, -1.0f)},
            //up
            {vec3(-1.0f,  1.0f, -1.0f)},
            {vec3(1.0f,  1.0f, -1.0f)},
            {vec3(1.0f,  1.0f,  1.0f)},
            {vec3(-1.0f,  1.0f,  1.0f)},
            //down
            {vec3(-1.0f, -1.0f,  1.0f)},
            {vec3(1.0f, -1.0f,  1.0f)},
            {vec3(1.0f, -1.0f, -1.0f)},
            {vec3(-1.0f, -1.0f, -1.0f)}
        };
        vector<unsigned int> indices = {
            //front
            0, 1, 3,
            1, 2, 3,
            //back
            4, 5, 7,
            5, 6, 7,
            //left
            8, 9, 11,
            9, 10, 11,
            //right
            12, 13, 15,
            13, 14, 15,
            //up
            16, 17, 19,
            17, 18, 19,
            //down
            20, 21, 23,
            21, 22, 23
        };
        m_cube_mesh = new vertex_buffer(vertices, indices);

        m_projection = perspective(radians(90.0f), 1.0f, 0.1f, 10.0f);

        m_cube_views = {
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f,  0.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f,  0.0f,  0.0f), vec3(0.0f, -1.0f,  0.0f)),
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,  1.0f,  0.0f), vec3(0.0f,  0.0f,  1.0f)),
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f,  0.0f), vec3(0.0f,  0.0f, -1.0f)),
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,  0.0f,  1.0f), vec3(0.0f, -1.0f,  0.0f)),
            lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,  0.0f, -1.0f), vec3(0.0f, -1.0f,  0.0f))
        };
	}

	sky_pass::~sky_pass() {
		delete m_hdr2env_shader;
		delete m_env2diffuse_shader;
		delete m_env2specular_shader;
        delete m_backgroud;
        delete m_backgroud_frame_buffer;
        delete m_cube_mesh;
	}

	void sky_pass::rend(render_system* render, camera_object* camera, sky_object* sky) {
        if (sky == nullptr) return;

        if (sky->m_hdr && !sky->m_environment_cube) {
            rend_environment(render, sky->m_hdr, sky->m_environment_cube);
        }

        if (!sky->m_diffuse_cube) {
            rend_diffuse(render, sky->m_environment_cube, sky->m_diffuse_cube);
        }

        if (!sky->m_specular_cube) {
            rend_specular(render, sky->m_environment_cube, sky->m_specular_cube);
        }

        m_backgroud_frame_buffer->bind();
        render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
        render->set(graphic_capability::DEPTH_TEST, true);
        render->set(graphic_func::DEPTH_MASK, true);
        render->set_depth_func(depth_func::LESS);
        render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

        m_env2background_shader->use();
        m_env2background_shader->set_mat4("uProjection", camera->get_projection());
        vec3 rotation = camera->get_world_rotation();
        mat4 view = mat4(1.0f);
        view = rotate(view, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
        view = rotate(view, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
        view = rotate(view, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
        view = inverse(view);
        m_env2background_shader->set_mat4("uView", view);
        m_env2background_shader->set_texture_cube("uEnvironment", *(sky->m_environment_cube));

        m_cube_mesh->draw();
	}
}


