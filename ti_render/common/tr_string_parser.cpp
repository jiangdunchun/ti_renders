#include "tr_string_parser.h"

#include <vector>

using namespace std;
using namespace glm;

#define SPLIT_CHAR ','

namespace ti_render {
	string tr_string_parser::to_string(const vec2& value) {
		return std::to_string(value.x) + SPLIT_CHAR
			+ std::to_string(value.y);
	}
	string tr_string_parser::to_string(const vec3& value) {
		return std::to_string(value.x) + SPLIT_CHAR
			+ std::to_string(value.y) + SPLIT_CHAR
			+ std::to_string(value.z);
	}
	string tr_string_parser::to_string(const vec4& value) {
		return std::to_string(value.x) + SPLIT_CHAR
			+ std::to_string(value.y) + SPLIT_CHAR
			+ std::to_string(value.z) + SPLIT_CHAR
			+ std::to_string(value.w);
	}
	string tr_string_parser::to_string(const mat2& value) {
		return std::to_string(value[0][0]) + SPLIT_CHAR
			+ std::to_string(value[0][1]) + SPLIT_CHAR
			+ std::to_string(value[1][0]) + SPLIT_CHAR
			+ std::to_string(value[1][1]);
	}
	string tr_string_parser::to_string(const mat3& value) {
		return std::to_string(value[0][0]) + SPLIT_CHAR
			+ std::to_string(value[0][1]) + SPLIT_CHAR
			+ std::to_string(value[0][2]) + SPLIT_CHAR
			+ std::to_string(value[1][0]) + SPLIT_CHAR
			+ std::to_string(value[1][1]) + SPLIT_CHAR
			+ std::to_string(value[1][2]) + SPLIT_CHAR
			+ std::to_string(value[2][0]) + SPLIT_CHAR
			+ std::to_string(value[2][1]) + SPLIT_CHAR
			+ std::to_string(value[2][2]);
	}
	string tr_string_parser::to_string(const mat4& value) {
		return std::to_string(value[0][0]) + SPLIT_CHAR
			+ std::to_string(value[0][1]) + SPLIT_CHAR
			+ std::to_string(value[0][2]) + SPLIT_CHAR
			+ std::to_string(value[0][3]) + SPLIT_CHAR
			+ std::to_string(value[1][0]) + SPLIT_CHAR
			+ std::to_string(value[1][1]) + SPLIT_CHAR
			+ std::to_string(value[1][2]) + SPLIT_CHAR
			+ std::to_string(value[1][3]) + SPLIT_CHAR
			+ std::to_string(value[2][0]) + SPLIT_CHAR
			+ std::to_string(value[2][1]) + SPLIT_CHAR
			+ std::to_string(value[2][2]) + SPLIT_CHAR
			+ std::to_string(value[2][3]) + SPLIT_CHAR
			+ std::to_string(value[3][0]) + SPLIT_CHAR
			+ std::to_string(value[3][1]) + SPLIT_CHAR
			+ std::to_string(value[3][2]) + SPLIT_CHAR
			+ std::to_string(value[3][3]);
	}

	vec2 tr_string_parser::to_vec2(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 2) return vec2();

		return vec2(atof(vals[0].c_str()),
			atof(vals[1].c_str()));
	}
	vec3 tr_string_parser::to_vec3(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 3) return vec3();

		return vec3(atof(vals[0].c_str()),
			atof(vals[1].c_str()),
			atof(vals[2].c_str()));
	}
	vec4 tr_string_parser::to_vec4(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 4) return vec4();

		return vec4(atof(vals[0].c_str()),
			atof(vals[1].c_str()),
			atof(vals[2].c_str()),
			atof(vals[3].c_str()));
	}
	mat2 tr_string_parser::to_mat2(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 4) return mat2();

		return mat2(atof(vals[0].c_str()),
			atof(vals[1].c_str()),
			atof(vals[2].c_str()),
			atof(vals[3].c_str()));
	}
	mat3 tr_string_parser::to_mat3(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 9) return mat3();

		return mat3(atof(vals[0].c_str()),
			atof(vals[1].c_str()),
			atof(vals[2].c_str()),
			atof(vals[3].c_str()),
			atof(vals[4].c_str()),
			atof(vals[5].c_str()),
			atof(vals[6].c_str()),
			atof(vals[7].c_str()),
			atof(vals[8].c_str()));
	}
	mat4 tr_string_parser::to_mat4(const string& value) {
		vector<string> vals;
		int last = 0;
		for (unsigned int i = 0; i < value.length(); i++) {
			if (value[i] == SPLIT_CHAR) {
				if (i != last) vals.push_back(value.substr(last, i - last));
				last = i + 1;
			}
		}
		if (last != value.length()) vals.push_back(value.substr(last, value.length() - last));

		if (vals.size() != 16) return mat4();

		return mat4(atof(vals[0].c_str()),
			atof(vals[1].c_str()),
			atof(vals[2].c_str()),
			atof(vals[3].c_str()),
			atof(vals[4].c_str()),
			atof(vals[5].c_str()),
			atof(vals[6].c_str()),
			atof(vals[7].c_str()),
			atof(vals[8].c_str()),
			atof(vals[9].c_str()),
			atof(vals[10].c_str()),
			atof(vals[11].c_str()),
			atof(vals[12].c_str()),
			atof(vals[13].c_str()),
			atof(vals[14].c_str()),
			atof(vals[15].c_str()));
	}
}