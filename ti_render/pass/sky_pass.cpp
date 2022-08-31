#include "sky_pass.h"

#include "../file/shader_file.h"

using namespace std;
using namespace glm;

namespace ti_render {
    void sky_pass::rend_env_cube(render_system* render, texture_2d* environment, texture_cube*& environment_cube) {
        unsigned int resolution = environment->get_height() / 2;
        environment_cube = new texture_cube(resolution, resolution, color_format::RGB16F);
        frame_buffer fbo(resolution, resolution);

        fbo.bind();
        render->set_clear_color(vec4(0.0f, 0.0f, 0.0f, 0.0f));
        render->set(graphic_capability::DEPTH_TEST, true);
        render->set(graphic_func::DEPTH_MASK, true);
        render->set_depth_func(depth_func::LESS);

        m_env2envcube_shader->use();
        m_env2envcube_shader->set_mat4("uProjection", m_projection);
        m_env2envcube_shader->set_texture_2d("uEnvironment", *(environment));
        for (unsigned int i = 0; i < m_cube_views.size(); ++i) {
            m_env2envcube_shader->set_mat4("uView", m_cube_views[i]);
            fbo.attach_color_buffer(0, environment_cube, cubemap_face(int(cubemap_face::POSITIVE_X) + i));
            render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

            m_cube_mesh->draw();
        }

        environment_cube->generate_mipmap();
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

        m_env2diffuse_shader->use();
        m_env2diffuse_shader->set_mat4("uProjection", m_projection);
        m_env2diffuse_shader->set_texture_cube("uEnvironment", *(environment));
        for (unsigned int i = 0; i < m_cube_views.size(); ++i) {
            m_env2diffuse_shader->set_mat4("uView", m_cube_views[i]);
            fbo.attach_color_buffer(0, diffuse, cubemap_face(int(cubemap_face::POSITIVE_X) + i));
            render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

            m_cube_mesh->draw();
        }
    }

    void sky_pass::rend_specular(render_system* render, texture_cube* environment, texture_cube*& specular) {
        unsigned int resolution = 512;
        specular = new texture_cube(resolution, resolution, color_format::RGB16F);
        specular->generate_mipmap();

        m_env2specular_shader->use();
        m_env2specular_shader->set_mat4("uProjection", m_projection);
        m_env2specular_shader->set_texture_cube("uEnvironment", *(environment));

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
                m_env2specular_shader->set_mat4("uView", m_cube_views[i]);
                fbo.attach_color_buffer(0, specular, cubemap_face(int(cubemap_face::POSITIVE_X) + i), level);
                render->clear_frame_buffer(frame_buffer_type::COLOR | frame_buffer_type::DEPTH | frame_buffer_type::STENCIL);

                m_cube_mesh->draw();
            }
        }
    }

    sky_pass::sky_pass(unsigned int width, unsigned int height) {
        shader_file env2envcube_file(m_env2envcube_shader_path);
        m_env2envcube_shader = new shader(env2envcube_file.get_vertex_code(), env2envcube_file.get_fragment_code());

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

        m_projection = perspective(90.0f, 1.0f, 0.1f, 10.0f);

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
        delete m_env2envcube_shader;
		delete m_env2diffuse_shader;
		delete m_env2specular_shader;
        delete m_backgroud;
        delete m_backgroud_frame_buffer;
        delete m_cube_mesh;
	}

	void sky_pass::rend(render_system* render, camera_object* camera, sky_object* sky) {
        if (sky == nullptr) return;

        render->set(graphic_capability::TEXTURE_CUBE_MAP_SEAMLESS, true);
        if (!sky->m_environment_cube) {
            rend_env_cube(render, sky->m_environment, sky->m_environment_cube);
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
        view = rotate(view, rotation.x, vec3(1.0f, 0.0f, 0.0f));
        view = rotate(view, rotation.y, vec3(0.0f, 1.0f, 0.0f));
        view = rotate(view, rotation.z, vec3(0.0f, 0.0f, 1.0f));
        view = inverse(view);
        m_env2background_shader->set_mat4("uView", view);
        m_env2background_shader->set_texture_cube("uEnvironment", *(sky->m_environment_cube));

        m_cube_mesh->draw();
	}
}


