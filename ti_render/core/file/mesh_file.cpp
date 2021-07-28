#include "mesh_file.h"

#include <fstream>

#include "../../common/logger_management.h"

using namespace std;
using namespace glm;

namespace ti_render {
    mesh_file::mesh_file(const string& path) {
        ifstream file;

        vector<face> faces;
        AABB aabb;
        try {
            file.open(path, ios::binary);

            unsigned int faces_num;
            file.read((char*)&faces_num, sizeof(unsigned int));

            for (unsigned int i = 0; i < faces_num; i++) {
                vector<vertex> vertices;
                vector<unsigned int> indices;
                AABB f_aabb;

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
                file.read((char*)&f_aabb.min.x, sizeof(vec3));
                file.read((char*)&f_aabb.max.x, sizeof(vec3));

                faces.push_back({ vertices , indices, f_aabb });
            }
            file.read((char*)&aabb.min.x, sizeof(vec3));
            file.read((char*)&aabb.max.x, sizeof(vec3));

            file.close();
        }
        catch (ifstream::failure e) {
            if (file.is_open()) file.close();
            logger_management::log(log_tag::LOG_ERROR,
                "file::mesh_file:load file \"" + path + "\" failed");
        }

        new (this)mesh_file(faces, aabb);
    }

    mesh_file::mesh_file(
        vector<face> faces,
        AABB aabb): m_faces(faces) , m_aabb(aabb) {
        // @TODO: check the aabb 
    }

    mesh_file::~mesh_file() {
    }

    void mesh_file::save(const string& path) {
        ofstream mesh_stream(path, ios::binary);

        unsigned int faces_num =m_faces.size();
        mesh_stream.write((char*)&(faces_num), sizeof(unsigned int));
        for (vector<face>::iterator iter = m_faces.begin();
            iter != m_faces.end();
            ++iter) {
            unsigned int vertices_num = iter->vertices.size();
            mesh_stream.write((char*)&(vertices_num), sizeof(unsigned int));
            mesh_stream.write((char*)&(iter->vertices[0]), sizeof(vertex) * vertices_num);

            unsigned int indices_num = iter->indices.size();
            mesh_stream.write((char*)&(indices_num), sizeof(unsigned int));
            mesh_stream.write((char*)&(iter->indices[0]), sizeof(unsigned int) * indices_num);

            mesh_stream.write((char*)&iter->aabb.min.x, sizeof(float) * 3);
            mesh_stream.write((char*)&iter->aabb.max.x, sizeof(float) * 3);
        }
        mesh_stream.write((char*)&m_aabb.min.x, sizeof(float) * 3);
        mesh_stream.write((char*)&m_aabb.max.x, sizeof(float) * 3);

        mesh_stream.close();
    }
}
