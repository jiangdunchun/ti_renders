#include <iostream>
#include <common/tr_algorithm.h>
#include <common/tr_string_parser.h>
#include <core/file/image_file.h>
#include <core/file/mesh_file.h>

using namespace ti_render;
using namespace std;
using namespace glm;

string get_image_dir(const string& path) {
    string dir = "";
    for (int i = path.size() - 1; i > 0; i--) {
        if (path[i] == '/' || path[i] == '\\') {
            dir = path.substr(0, i);
            break;
        }
    }

    if (dir == "") dir = "./";
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
    float x = 0.0f, z = 0.0f; 
    int x_num = 0, z_num = 0;
    float height = 0.0f;
    string image_path = "";

    for (int i = 1; i < argc; i++) {
        string paramter_name = argv[i];
        if (paramter_name[0] == '-') {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                cout << "missing value of parameter " + paramter_name << endl;
                continue;
            }
            string paramter_value = argv[i + 1];
            i++;

            if (paramter_name == "-size") {
                glm::vec2 size = tr_string_parser::to_vec2(paramter_value);
                x = size.x;
                z = size.y;
            }
            else if (paramter_name == "-num") {
                glm::vec2 num = tr_string_parser::to_vec2(paramter_value);
                x_num = num.x;
                z_num = num.y;
            }
            else if (paramter_name == "-height") {
                height = atof(paramter_value.c_str());
            }
            else if (paramter_name == "-image") {
                image_path = paramter_value;
            }
            else {
                cout << "unrecognizeed parameter name " + paramter_name << endl;
                continue;
            }
        }
        else {
            cout << "missing name of parameter " + paramter_name << endl;
            continue;
        }
    }

    if (x == 0.0f || z == 0.0f || x_num == 0 || z_num == 0 || height == 0.0f || image_path == "") {
        cout << "missing parameter or error format, here is the exaple:" << endl;
        cout << "   -size 1.0,1.0 -num 100,100 -height 0.1 -image terrain.jpg" << endl;
        return 0;
    }

    string image_dir = get_image_dir(image_path);
    string image_name = get_image_name(image_path);

    surface face;
    AABB aabb;
    tr_algorithm::generate_plane(x, z, x_num, z_num, face, aabb);
    image_file i_file(image_path, color_format::R8B);

    if (i_file.get_width() == 0 || i_file.get_height() == 0) {
        cout << "error image path " << image_path << endl;
        return 0;
    }

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
    string mesh_path = image_dir + "/" + image_name + ".mesh";
    m_file.save(mesh_path);
    cout << "generate terrain mesh to " << mesh_path << endl;
    return 1;
}