#include "mesh_file.h"

#include <fstream>

#include "../common/logger_management.h"
#include "file_common.h"

using namespace std;
using namespace glm;

namespace ti_render {
    mesh_file::mesh_file(const string& path) {
        string file_path = file_common::get_file_path(path);
        ifstream file;

        vector<surface> faces;
        AABB aabb;
        try {
            file.open(file_path, ios::binary);

            unsigned int faces_num;
            file.read((char*)&faces_num, sizeof(unsigned int));

            for (unsigned int i = 0; i < faces_num; i++) {
                unsigned int vertices_num;
                file.read((char*)&vertices_num, sizeof(unsigned int));
                vector<vertex> vertices(vertices_num);
                file.read((char*)&vertices[0], sizeof(vertex) * vertices_num);

                unsigned int indices_num;
                file.read((char*)&indices_num, sizeof(unsigned int));
                vector<unsigned int> indices(indices_num);
                file.read((char*)&indices[0], sizeof(unsigned int) * indices_num);

                AABB f_aabb;
                file.read((char*)&f_aabb, sizeof(AABB));

                faces.push_back({ vertices , indices, f_aabb });
            }
            file.read((char*)&aabb, sizeof(AABB));

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
        vector<surface> faces,
        AABB aabb): m_faces(faces) , m_aabb(aabb) {
        // @TODO: check the aabb 
    }

    mesh_file::~mesh_file() {
    }

    void mesh_file::save(const string& path) {
        ofstream mesh_stream(path, ios::binary);

        unsigned int faces_num =m_faces.size();
        mesh_stream.write((char*)&(faces_num), sizeof(unsigned int));
        for (vector<surface>::iterator iter = m_faces.begin();
            iter != m_faces.end();
            ++iter) {
            unsigned int vertices_num = iter->vertices.size();
            mesh_stream.write((char*)&vertices_num, sizeof(unsigned int));
            mesh_stream.write((char*)&iter->vertices[0], sizeof(vertex) * vertices_num);

            unsigned int indices_num = iter->indices.size();
            mesh_stream.write((char*)&indices_num, sizeof(unsigned int));
            mesh_stream.write((char*)&iter->indices[0], sizeof(unsigned int) * indices_num);

            mesh_stream.write((char*)&iter->aabb, sizeof(AABB));
        }
        mesh_stream.write((char*)&m_aabb, sizeof(AABB));

        mesh_stream.close();
    }
}
