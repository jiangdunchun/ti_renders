#include "mesh_file.h"

#include <fstream>

#include "../../common/logger_management.h"

using namespace std;

namespace ti_render {
    mesh_file::mesh_file(const string& path) {
        ifstream file;
        vector<vertex> vertices;
        vector<unsigned int> indices;
        glm::vec3 AABB_min = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 AABB_max = glm::vec3(0.0f, 0.0f, 0.0f);

        try {
            file.open(path, ios::binary);

            unsigned int vertices_num;
            file.read((char*)&vertices_num, sizeof(unsigned int));
            for (unsigned int i = 0; i < vertices_num; i++) {
                vertex now_vertex;
                file.read((char*)&now_vertex, sizeof(vertex));
                vertices.push_back(now_vertex);
            }
            unsigned int indices_num;
            file.read((char*)&indices_num, sizeof(unsigned int));
            for (unsigned int i = 0; i < indices_num; i++) {
                unsigned int index;
                file.read((char*)&index, sizeof(unsigned int));
                indices.push_back(index);
            }
            file.read((char*)&AABB_min, sizeof(glm::vec3));
            file.read((char*)&AABB_max, sizeof(glm::vec3));

            file.close();
        }
        catch (ifstream::failure e) {
            if (file.is_open()) file.close();
            logger_management::log(log_tag::LOG_ERROR,
                "file::mesh_file:load file \"" + path + "\" failed");
        }

        new (this)mesh_file(vertices, indices, AABB_min, AABB_max);
    }

    mesh_file::mesh_file(
        const vector<vertex>& vertices, 
        const vector<unsigned int>& indices, 
        glm::vec3 AABB_min, 
        glm::vec3 AABB_max) : m_vertices(vertices), m_indices(indices) {
        this->m_vertices = vertices;
        this->m_indices = indices;
        if (AABB_min != AABB_max) {
            m_AABB.min = AABB_min;
            m_AABB.max = AABB_max;
        }
        else {
            m_AABB.min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
            m_AABB.max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);

            for (unsigned int i = 0; i < m_vertices.size(); i++) {
                m_AABB.min.x = m_AABB.min.x < m_vertices[i].position.x ? m_AABB.min.x : m_vertices[i].position.x;
                m_AABB.min.y = m_AABB.min.y < m_vertices[i].position.y ? m_AABB.min.y : m_vertices[i].position.y;
                m_AABB.min.z = m_AABB.min.z < m_vertices[i].position.z ? m_AABB.min.z : m_vertices[i].position.z;

                m_AABB.max.x = m_AABB.max.x > m_vertices[i].position.x ? m_AABB.max.x : m_vertices[i].position.x;
                m_AABB.max.y = m_AABB.max.y > m_vertices[i].position.y ? m_AABB.max.y : m_vertices[i].position.y;
                m_AABB.max.z = m_AABB.max.z > m_vertices[i].position.z ? m_AABB.max.z : m_vertices[i].position.z;
            }
        }
    }

    mesh_file::~mesh_file() {
    }

    void mesh_file::save(const string& path) const {
        ofstream mesh_stream(path, ios::binary);

        unsigned int vertices_num = this->m_vertices.size();
        mesh_stream.write((char*)&(vertices_num), sizeof(unsigned int));
        mesh_stream.write((char*)&(this->m_vertices[0]), sizeof(vertex) * vertices_num);

        unsigned int indices_num = this->m_indices.size();
        mesh_stream.write((char*)&(indices_num), sizeof(unsigned int));
        mesh_stream.write((char*)&(this->m_indices[0]), sizeof(unsigned int) * indices_num);

        mesh_stream.write((char*)&m_AABB.min.x, sizeof(float) * 3);
        mesh_stream.write((char*)&m_AABB.max.x, sizeof(float) * 3);

        mesh_stream.close();
    }
}
