#include <iostream>
#include <common/tr_algorithm.h>
#include <core/file/image_file.h>
#include <core/file/mesh_file.h>

using namespace ti_render;
using namespace std;
using namespace glm;

string get_image_dir(const string& path) {
    string dir = path;
    for (int i = dir.size() - 1; i > 0; i--) {
        if (dir[i] == '/' || dir[i] == '\\') {
            dir = dir.substr(0, i);
            break;
        }
    }

    return dir;
}

string get_image_name(const string& path) {
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

int main(unsigned int argc, char** argv) {
    float x = 1.0f, y = 1.0f; 
    float height = 0.1f;
    int x_num = 100, y_num = 100;
    string image_path = "../../resource/model/terrain.jpg";

    string image_dir = get_image_dir(image_path);
    string image_name = get_image_name(image_path);

    surface face;
    AABB aabb;
    tr_algorithm::generate_plane(x, y, x_num, y_num, face, aabb);
    image_file i_file(image_path, color_format::R8B);

    aabb = { vec3(FLT_MAX, FLT_MAX, FLT_MAX), vec3(FLT_MIN, FLT_MIN, FLT_MIN) };
    for (unsigned int i = 0; i < face.vertices.size(); i++) {
        float delta = i_file.sample_liner(face.vertices[i].tex_coord).r;
        face.vertices[i].position += height * delta * face.vertices[i].normal;

        aabb.min.x = aabb.min.x < face.vertices[i].position.x ? aabb.min.x : face.vertices[i].position.x;
        aabb.min.y = aabb.min.y < face.vertices[i].position.y ? aabb.min.y : face.vertices[i].position.y;
        aabb.min.z = aabb.min.z < face.vertices[i].position.z ? aabb.min.z : face.vertices[i].position.z;
        aabb.max.x = aabb.max.x > face.vertices[i].position.x ? aabb.max.x : face.vertices[i].position.x;
        aabb.max.y = aabb.max.y > face.vertices[i].position.y ? aabb.max.y : face.vertices[i].position.y;
        aabb.max.z = aabb.max.z > face.vertices[i].position.z ? aabb.max.z : face.vertices[i].position.z;
    }

    vector<triangle*> ts;
    vector<edge*> es;
    vector<point*> ps;
    tr_algorithm::build_triagnles(face, ts, es, ps);
    for (unsigned int i = 0; i < ps.size(); i++) {
        vec3 normal = vec3(0.0f, 0.0f, 0.0f);
        for (unsigned int j = 0; j < ps[i]->ts.size(); j++) {
            normal += normalize(cross(ps[i]->ts[j]->p1->v->position - ps[i]->ts[j]->p0->v->position, ps[i]->ts[j]->p2->v->position - ps[i]->ts[j]->p1->v->position));
        }
        ps[i]->v->normal = normalize(normal);

        //@TODO: calculate tangent and bi_tangent
    }

    mesh_file m_file({ face }, aabb);
    m_file.save(image_dir + "/" + image_name + ".mesh");
}