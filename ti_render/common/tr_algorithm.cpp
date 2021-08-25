#include "tr_algorithm.h"

#include <algorithm>
#include <map>

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
		AABB aabb_o,
		mat4 aabb_o_trans) {
		mat4 inverse_trans = inverse(aabb_o_trans);
		point = vec3(inverse_trans * (vec4(point, 1.0f)));

		vec3 delta_min = point - aabb_o.min;
		if (delta_min.x < 0 || delta_min.y < 0 || delta_min.z < 0) return false;

		vec3 delta_max = aabb_o.max - point;
		if (delta_max.x < 0 || delta_max.y < 0 || delta_max.z < 0) return false;

		return true;
	}

	bool tr_algorithm::is_intersect_with_AABB(
		ray ray,
		AABB aabb,
		mat4 aabb_trans) {
		mat4 inverse_trans = inverse(aabb_trans);

		ray.origin = vec3(inverse_trans * (vec4(ray.origin, 1.0f)));
		ray.direction = vec3(inverse_trans * (vec4(ray.direction, 0.0f)));

		vec3 d_min = (aabb.min - ray.origin) / ray.direction;
		vec3 d_max = (aabb.max - ray.origin) / ray.direction;

		vec3 d_front = glm::min(d_min, d_max);
		vec3 d_back = glm::max(d_min, d_max);

		float near_d = std::max(std::max(d_front.x, d_front.y), d_front.z);
		float far_d = std::min(std::min(d_back.x, d_back.y), d_back.z);

		if (near_d < 0 && far_d < 0) return false;
		else return near_d < far_d;
	}

	void tr_algorithm::generate_plane(
		float width, float height,
		int x_num, int y_num,
		surface& face, AABB& aabb) {
		vec3 ld = vec3(width / -2.0f, 0.0f, height / 2.0f);

		vector<vertex> vertices;
		vec3 normal = vec3(0.0f, 1.0f, 0.0f);
		vec3 tangent = vec3(1.0f, 0.0f, 0.0f);
		vec3 bi_tangent = vec3(0.0f, 0.0f, -1.0f);
		float t_step_x = 1.0f / x_num;
		float t_step_y = 1.0f / y_num;
		float p_step_x = width * t_step_x;
		float p_step_y = -1.0f * height * t_step_y;
		for (int y = 0; y <= y_num; y++) {
			for (int x = 0; x <= x_num; x++) {
				vec3 position = ld + float(x) * vec3(p_step_x, 0.0f, 0.0f) + float(y) * vec3(0.0f, 0.0f, p_step_y);
				vec2 tex_coord = vec2(float(x) * t_step_x, float(y) * t_step_y);
				vertices.push_back({ position, tex_coord, normal, tangent, bi_tangent });
			}
		}

		vector<unsigned int> indices;
		for (int y = 0; y < y_num; y++) {
			for (int x = 0; x < x_num; x++) {
				indices.push_back(y * (x_num + 1) + x);
				indices.push_back(y * (x_num + 1) + x + 1);
				indices.push_back((y + 1) * (x_num + 1) + x + 1);
				indices.push_back(y * (x_num + 1) + x);
				indices.push_back((y + 1) * (x_num + 1) + x + 1);
				indices.push_back((y + 1) * (x_num + 1) + x);
			}
		}

		aabb = { vec3(width / -2.0f, 0.0f, height / -2.0f), vec3(width / 2.0f, 0.0f, height / 2.0f) };
		face.vertices = vertices;
		face.indices = indices;
		face.aabb = aabb;
	}

	void tr_algorithm::build_triagnles(
		surface& face,
		vector<triangle*>& ts,
		vector<edge*>& es,
		vector<point*>& ps,
		bool directed) {
		for (int i = 0; i < face.vertices.size(); i++) {
			point* n_point = new point();
			n_point->v = &face.vertices[i];
			ps.push_back(n_point);
		}

		map<tuple<point*, point*>, edge*> edge_buffer;
		map<tuple<point*, point*>, edge*>::iterator edge_iter;

		for (int i = 0; i < face.indices.size() / 3; i++) {
			triangle* n_triangle = new triangle();
			n_triangle->p0 = ps[face.indices[i * 3]];
			n_triangle->p0->ts.push_back(n_triangle);
			n_triangle->p1 = ps[face.indices[i * 3 + 1]];
			n_triangle->p1->ts.push_back(n_triangle);
			n_triangle->p2 = ps[face.indices[i * 3 + 2]];
			n_triangle->p2->ts.push_back(n_triangle);
			n_triangle->e0 = nullptr;
			n_triangle->e1 = nullptr;
			n_triangle->e2 = nullptr;

			edge_iter = edge_buffer.find({ n_triangle->p0 , n_triangle->p1 });
			if (edge_iter != edge_buffer.end()) {
				n_triangle->e0 = edge_iter->second;
				n_triangle->e0->ts.push_back(n_triangle);
			}
			else {
				if (directed) {
					edge_iter = edge_buffer.find({ n_triangle->p1 , n_triangle->p0 });
					if (edge_iter != edge_buffer.end()) {
						n_triangle->e0 = edge_iter->second;
						n_triangle->e0->ts.push_back(n_triangle);
					}
				}
			}

			edge_iter = edge_buffer.find({ n_triangle->p1 , n_triangle->p2 });
			if (edge_iter != edge_buffer.end()) {
				n_triangle->e1 = edge_iter->second;
				n_triangle->e1->ts.push_back(n_triangle);
			}
			else {
				if (directed) {
					edge_iter = edge_buffer.find({ n_triangle->p2 , n_triangle->p1 });
					if (edge_iter != edge_buffer.end()) {
						n_triangle->e1 = edge_iter->second;
						n_triangle->e1->ts.push_back(n_triangle);
					}
				}
			}

			edge_iter = edge_buffer.find({ n_triangle->p2 , n_triangle->p0 });
			if (edge_iter != edge_buffer.end()) {
				n_triangle->e2 = edge_iter->second;
				n_triangle->e2->ts.push_back(n_triangle);
			}
			else {
				if (directed) {
					edge_iter = edge_buffer.find({ n_triangle->p0 , n_triangle->p2 });
					if (edge_iter != edge_buffer.end()) {
						n_triangle->e2 = edge_iter->second;
						n_triangle->e2->ts.push_back(n_triangle);
					}
				}
			}

			if (!n_triangle->e0) {
				edge* n_edge = new edge();
				n_edge->p0 = n_triangle->p0;
				n_edge->p1 = n_triangle->p1;
				es.push_back(n_edge);
				edge_buffer[{n_edge->p0, n_edge->p1}] = n_edge;
				n_triangle->e0 = n_edge;
				n_triangle->e0->ts.push_back(n_triangle);
				n_triangle->p0->es.push_back(n_triangle->e0);
				n_triangle->p1->es.push_back(n_triangle->e0);
			}
			if (!n_triangle->e1) {
				edge* n_edge = new edge();
				n_edge->p0 = n_triangle->p1;
				n_edge->p1 = n_triangle->p2;
				es.push_back(n_edge);
				edge_buffer[{n_edge->p0, n_edge->p1}] = n_edge;
				n_triangle->e1 = n_edge;
				n_triangle->e1->ts.push_back(n_triangle);
				n_triangle->p1->es.push_back(n_triangle->e1);
				n_triangle->p2->es.push_back(n_triangle->e1);
			}
			if (!n_triangle->e2) {
				edge* n_edge = new edge();
				n_edge->p0 = n_triangle->p2;
				n_edge->p1 = n_triangle->p0;
				es.push_back(n_edge);
				edge_buffer[{n_edge->p0, n_edge->p1}] = n_edge;
				n_triangle->e2 = n_edge;
				n_triangle->e2->ts.push_back(n_triangle);
				n_triangle->p2->es.push_back(n_triangle->e2);
				n_triangle->p0->es.push_back(n_triangle->e2);
			}

			ts.push_back(n_triangle);
		}
	}
}