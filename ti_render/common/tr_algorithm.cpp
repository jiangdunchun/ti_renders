#include "tr_algorithm.h"

#include <algorithm>

using namespace std;
using namespace glm;

#define PI 3.1415926

namespace ti_render {
	void tr_algorithm::decompose_mat4(
		const mat4& tansform,
		vec3& position,
		vec3& rotation,
		vec3& scale) {
		position = vec3(tansform[3]);

		scale.x = length(tansform[0]);
		scale.y = length(tansform[1]);
		scale.z = length(tansform[2]);

		mat3 rot_mat(
			vec3(tansform[0]) / scale.x,
			vec3(tansform[1]) / scale.y,
			vec3(tansform[2]) / scale.z);

		float m20 = rot_mat[2][0];
		m20 = m20 > 1.0f ? 1.0f : m20;
		m20 = m20 < -1.0f ? -1.0f : m20;

		rotation.y = asin(m20);
		if (abs(rot_mat[2][0]) < 0.9999999f) {
			rotation.x = atan2(-1.0f * rot_mat[2][1], rot_mat[2][2]);
			rotation.z = atan2(-1.0f * rot_mat[1][0], rot_mat[0][0]);
		}
		else {
			rotation.x = atan2(rot_mat[1][2], rot_mat[1][1]);
			rotation.z = 0.0f;
		}
		rotation = float(180.0f / PI) * rotation;
	}

	bool tr_algorithm::is_contain_in_AABB(
		vec3 point,
		AABB AABB_o,
		mat4 AABB_o_trans) {
		mat4 inverse_trans = inverse(AABB_o_trans);
		point = vec3(inverse_trans * (vec4(point, 1.0f)));

		vec3 delta_min = point - AABB_o.min;
		if (delta_min.x < 0 || delta_min.y < 0 || delta_min.z < 0) return false;

		vec3 delta_max = AABB_o.max - point;
		if (delta_max.x < 0 || delta_max.y < 0 || delta_max.z < 0) return false;

		return true;
	}

	bool tr_algorithm::is_intersect_with_AABB(
		ray ray,
		AABB AABB,
		mat4 AABB_trans) {
		mat4 inverse_trans = inverse(AABB_trans);

		ray.origin = vec3(inverse_trans * (vec4(ray.origin, 1.0f)));
		ray.direction = vec3(inverse_trans * (vec4(ray.direction, 0.0f)));

		vec3 d_min = (AABB.min - ray.origin) / ray.direction;
		vec3 d_max = (AABB.max - ray.origin) / ray.direction;

		vec3 d_front = glm::min(d_min, d_max);
		vec3 d_back = glm::max(d_min, d_max);

		float near_d = std::max(std::max(d_front.x, d_front.y), d_front.z);
		float far_d = std::min(std::min(d_back.x, d_back.y), d_back.z);

		if (near_d < 0 && far_d < 0) return false;
		else return near_d < far_d;
	}
}