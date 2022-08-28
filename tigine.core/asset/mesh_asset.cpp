#include "mesh_asset.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <tigine.core/common/logger_mgr.h>
#include <fstream>

using namespace std;
using namespace glm;

namespace tigine {
	unique_ptr<mesh_asset> mesh_asset::load(const std::string& path) {
		ifstream file;
		try {
			file.open(path, ios::binary);

			unsigned vertices_num;
			file.read((char*)&vertices_num, sizeof(unsigned));
			vector<vertex> vertices(vertices_num);
			file.read((char*)&vertices[0], sizeof(vertex) * vertices_num);

			unsigned bones_num;
			file.read((char*)&bones_num, sizeof(unsigned));
			vector<bone> bones(bones_num);
			file.read((char*)&bones[0], sizeof(bone) * bones_num);

			unsigned indices_num;
			file.read((char*)&indices_num, sizeof(unsigned));
			vector<unsigned> indices(indices_num);
			file.read((char*)&indices[0], sizeof(bone) * indices_num);

			file.close();

			unique_ptr<mesh_asset> mesh(new mesh_asset());
			mesh->set_vertices(vertices);
			mesh->set_bones(bones);
			mesh->set_indices(indices);
			return mesh;
		}
		catch (ifstream::failure e) {
			if (file.is_open()) file.close();
			LOG_ERROR("load mesh failed from %s", path.c_str());
			return nullptr;
		}
	}

	void mesh_asset::save(const std::string& path) const {
		ofstream mesh_stream(path, ios::binary);

		unsigned vertices_num = m_vertices.size();
		mesh_stream.write((char*)&(vertices_num), sizeof(unsigned));
		mesh_stream.write((char*)&m_vertices[0], sizeof(vertex) * vertices_num);

		unsigned bones_num = m_bones.size();
		mesh_stream.write((char*)&(bones_num), sizeof(unsigned));
		mesh_stream.write((char*)&m_bones[0], sizeof(bone) * bones_num);

		unsigned indices_num = m_indices.size();
		mesh_stream.write((char*)&(indices_num), sizeof(unsigned));
		mesh_stream.write((char*)&m_indices[0], sizeof(unsigned) * indices_num);

		mesh_stream.close();
	}
}