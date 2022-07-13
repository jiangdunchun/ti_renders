#include "mesh_asset.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <tigine.core/common/logger_mgr.h>
#include <fstream>

using namespace std;
using namespace glm;

namespace tigine {
	vector<mesh_asset*> mesh_asset::load_scene(const string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LOG_ERROR("load meshes failed from " + path);
			return {};
		}

		vector<mesh_asset*> ret;
		for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
			aiMesh* ai_mesh = scene->mMeshes[i];
			vector<vertex> vertices;
			vector<bone> bones;
			vector<unsigned> indices;
			for (unsigned j = 0; j < ai_mesh->mNumVertices; ++j) {
				//vec3 position = vec3(ai_mesh->mVertices[j].x, ai_mesh->mVertices[j].y, ai_mesh->mVertices[j].z);
				//vec2 uv = vec2(ai_mesh->mTextureCoords[0][j].x, ai_mesh->mTextureCoords[0][j].y);
				//vec3 normal = vec3(ai_mesh->mNormals[j].x, ai_mesh->mNormals[j].y, ai_mesh->mNormals[j].z);
				//vec3 tangent = vec3(ai_mesh->mTangents[j].x, ai_mesh->mTangents[j].y, ai_mesh->mTangents[j].z);
				//vertices.push_back({ position, uv, normal, tangent });
			}
			mesh_asset* mesh = new mesh_asset();
			mesh->set_vertices(vertices);
			mesh->set_bones(bones);
			mesh->set_indices(indices);
			ret.push_back(mesh);
		}
			
		return ret;
	}
	
	mesh_asset* mesh_asset::load(const std::string& path) {
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

			mesh_asset* mesh = new mesh_asset();
			mesh->set_vertices(vertices);
			mesh->set_bones(bones);
			mesh->set_indices(indices);
			return mesh;
		}
		catch (ifstream::failure e) {
			if (file.is_open()) file.close();
			LOG_ERROR("load mesh failed from " + path);
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