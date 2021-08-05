#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <io.h>
#include <direct.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <core/file/mesh_file.h>

using namespace ti_render;
using namespace std;
using namespace glm;

#define MESHES_DOC                          "meshes"
#define MATERIALS_DOC                       "materials"
#define TEXTUREs_DOC                        "textures"
#define MESH_FILE_EXTENTION                 ".mesh"

string get_obj_dir(const string& path) {
    string dir = path;
    for (int i = dir.size() - 1; i > 0; i--) {
        if (dir[i] == '/' || dir[i] == '\\') {
            dir = dir.substr(0, i);
            break;
        }
    }

    return dir;
}

string get_obj_name(const string& path) {
    string name = path;
    for (int i = name.size() - 1; i > 0; i--) {
        if (name[i] == '/' || name[i] == '\\') {
            name = name.substr(i + 1, name.length() - i - 1);
            break;
        }
    }

    for (int i = name.size() - 1; i > 0; i--) {
        if (name[i] == '.') {
            name = name.substr(0, i);
            break;
        }
    }

    return name;
}

surface process_mesh(aiMesh* ai_mesh) {
    vector<vertex> vertices;
    vector<unsigned int> indices;
    AABB aabb = { vec3(FLT_MAX, FLT_MAX, FLT_MAX), vec3(FLT_MIN, FLT_MIN, FLT_MIN)};

    if (ai_mesh->mNumUVComponents[0] != 2) return { vertices, indices, aabb };

    for (unsigned int i = 0; i < ai_mesh->mNumVertices; ++i) {
        vec3 position = vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
        vec2 uv = vec2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
        vec3 normal = vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);
        vec3 tangent = vec3(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y, ai_mesh->mTangents[i].z);
        vec3 bi_tangent = vec3(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y, ai_mesh->mBitangents[i].z);
        vertices.push_back({ position, uv, normal, tangent, bi_tangent});

        aabb.min.x = aabb.min.x < ai_mesh->mVertices[i].x ? aabb.min.x : ai_mesh->mVertices[i].x;
        aabb.min.y = aabb.min.y < ai_mesh->mVertices[i].y ? aabb.min.y : ai_mesh->mVertices[i].y;
        aabb.min.z = aabb.min.z < ai_mesh->mVertices[i].z ? aabb.min.z : ai_mesh->mVertices[i].z;
        aabb.max.x = aabb.max.x > ai_mesh->mVertices[i].x ? aabb.max.x : ai_mesh->mVertices[i].x;
        aabb.max.y = aabb.max.y > ai_mesh->mVertices[i].y ? aabb.max.y : ai_mesh->mVertices[i].y;
        aabb.max.z = aabb.max.z > ai_mesh->mVertices[i].z ? aabb.max.z : ai_mesh->mVertices[i].z;
    }

    for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i) {
        for (unsigned int j = 0; j < ai_mesh->mFaces[i].mNumIndices; ++j) {
            indices.push_back(ai_mesh->mFaces[i].mIndices[j]);
        }
    }

    return {vertices, indices, aabb};
}

void process_node(aiNode* node_ptr, const vector<aiMesh*>& mesh_buffer, const string& fold) {
    vector<surface> faces;
    AABB aabb = { vec3(FLT_MAX, FLT_MAX, FLT_MAX), vec3(FLT_MIN, FLT_MIN, FLT_MIN) };

    for (unsigned int i = 0; i < node_ptr->mNumMeshes; ++i) {
        surface n_face = process_mesh(mesh_buffer[node_ptr->mMeshes[i]]);
        if (n_face.vertices.size() != 0) faces.push_back(n_face);
    }
    
    for (unsigned int i = 0; i < faces.size(); ++i) {
        aabb.min.x = aabb.min.x < faces[i].aabb.min.x ? aabb.min.x : faces[i].aabb.min.x;
        aabb.min.y = aabb.min.y < faces[i].aabb.min.y ? aabb.min.y : faces[i].aabb.min.y;
        aabb.min.z = aabb.min.z < faces[i].aabb.min.z ? aabb.min.z : faces[i].aabb.min.z;
        aabb.max.x = aabb.max.x > faces[i].aabb.max.x ? aabb.max.x : faces[i].aabb.max.x;
        aabb.max.y = aabb.max.y > faces[i].aabb.max.y ? aabb.max.y : faces[i].aabb.max.y;
        aabb.max.z = aabb.max.z > faces[i].aabb.max.z ? aabb.max.z : faces[i].aabb.max.z;
    }

    mesh_file m_file(faces, aabb);
    m_file.save(fold + "/" + node_ptr->mName.C_Str() + MESH_FILE_EXTENTION);

    for (unsigned int i = 0; i < node_ptr->mNumChildren; ++i) {
        process_node(node_ptr->mChildren[i], mesh_buffer, fold);
    }
}

int main(unsigned int argc, char** argv) {
    if (argc < 1) cout << "Error: missing model path" << endl;

    for (int i = 1; i < argc; i++) {
        string obj_path = argv[i];
        string obj_dir = get_obj_dir(obj_path);
        string obj_name = get_obj_name(obj_path);

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(obj_path, aiProcessPreset_TargetRealtime_MaxQuality);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            cout << "Error: " << importer.GetErrorString() << endl;
            return 0;
        }

        string scene_dir = obj_dir + "/" + obj_name;
        if (_access(scene_dir.c_str(), 0) != 0) _mkdir(scene_dir.c_str());

        string meshes_dir = scene_dir + "/" + MESHES_DOC;
        if (_access(meshes_dir.c_str(), 0) != 0) _mkdir(meshes_dir.c_str());
        vector<string> mesh_names;

        vector<aiMesh*> mesh_buffer;
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            mesh_buffer.push_back(scene->mMeshes[i]);
        }

        for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i) {
            process_node(scene->mRootNode->mChildren[i], mesh_buffer, meshes_dir);
        }
    }

    return 1;
}
