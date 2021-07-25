#include "shader_file.h"

#include <fstream>

#include "../../common/logger_management.h"

using namespace std;

namespace ti_render {
	shader_file::shader_file(const string& path) {
        string vertex_code = "";
        string fragment_code = "";
        string geometry_code = "";

        ifstream file;

        try {
            int flag = 0;
            file.open(path, ios::in);

            string line;
            while (getline(file, line)) {
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                if (line == "") continue;

                if (line.find(VERTEX_SHADER_ELEM) == 0) {
                    flag = 1;
                    continue;
                }
                if (line.find(FRAGMENT_SHADER_ELEM) == 0) {
                    flag = 2;
                    continue;
                }
                if (line.find(GEOMTRY_SHADER_ELEM) == 0) {
                    flag = 3;
                    continue;
                }

                switch (flag) {
                case 1:
                    vertex_code += line + "\n";
                    break;
                case 2:
                    fragment_code += line + "\n";
                    break;
                case 3:
                    geometry_code += line + "\n";
                    break;
                }
            }
            file.close();
        }
        catch (ifstream::failure e) {
            if (file.is_open()) file.close();
            logger_management::log(log_tag::LOG_ERROR,
                "file_management::shader_file:read file \"" + path + "\" failed");
        }

        new (this)shader_file(vertex_code, fragment_code, geometry_code);
	}

    shader_file::shader_file(
        const std::string& vertex_code, 
        const std::string& fragment_code,
        const std::string& geometry_code) : m_vertex_code(vertex_code), m_fragment_code(fragment_code), m_geometry_code(geometry_code) {
    }

	shader_file::~shader_file() {
	}

    void shader_file::save(const std::string& path) const {
        throw "not impl!";
    }
}