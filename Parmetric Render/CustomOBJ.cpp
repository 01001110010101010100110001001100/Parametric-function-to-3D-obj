#include "CustomOBJ.h"
#include <math.h>
#include <iostream>
template <typename T> float sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

CustomOBJ::CustomOBJ(size_t q) :position_list((q + 1)* (q + 1)), vertex_list((q + 0)* (q + 0) * 4), index_list((q)* (q) * 6 * 2), q(q) {
	CustomOBJ::Create_point_list();
	CustomOBJ::Create_vertex_list();
	CustomOBJ::Create_index_list();
}


std::vector<Vector3D> CustomOBJ::Get_point_list() {
	return position_list;
}

std::vector<vertex> CustomOBJ::Get_vertex_list() {
	return vertex_list;
}

std::vector<unsigned int> CustomOBJ::Get_index_list() {
	return index_list;
}

CustomOBJ::~CustomOBJ() {
}

void CustomOBJ::Create_point_list() {
	float x = 0;
	float y = 0;
	float z = 0;
	float a1 = 1.06f;
	float a2 = 10.0f;
	float h = 1.067f;
	float s = cos(h);
	float l = 0.49999999f;
	float q_f = (float)q;
	for (int u = 0; u <= q; u++) {
		for (int v = 0; v <= q; v++) {
			float u_f = ((float)u / q_f - .5f) * 2.0F;
			float v_f = ((float)v / q_f - .5f) * 1.0f;
			y = v_f;
			float q1 = 0.54f * tanh(1.44f * abs(sin(3.14 * u_f))) / 2;
			float k = -.2 * u_f * u_f + .2f;
			z = -.3 + 0 * k + q1 * (3 * a1 * (v_f + l) * log(fmaxf(fabs(v_f + l), 1e-6f)) * (1 + sgn(v_f + l)) -
				(exp(-powf(fmaxf(abs(33 * (u_f + .5f)), 1e-6f), 2)) + exp(-powf(fmaxf(abs(33 * (u_f - .5f)), 1e-6f), 2)))
				* a2 / 36.0f * exp(-powf(fmaxf(abs(36.0f * (v_f + 0.03f + l) - 36.0f / 2.71f), 1e-6f), 4))
				- .0f * sin(v_f + l) * (1 + sgn(v_f + l - .01f)));
			x = .8f * u_f * (1 + 0 * exp(-powf(3.7f * (z / a2 * 36 / 8 - .5f), 2)) * cos(u_f / 2 * 2 * 3.14));
			position_list[v + u * (q + 1)] = { Vector3D(x,y,z) };
			if (u == 0) {
				printf("Index Access: position_list[%d] = (%f, %f, %f)\n", v, position_list[v].m_x, position_list[v].m_y, position_list[v].m_z);
			}
			if (u == 0 && v == 0) {
				printf("v_f + l = %f\n", v_f + l);
			}
			if (u == 0 && v == 0) {
				printf("Pow base: %f\n", (36.0f * (v_f + 0.03f + l) - 36.0f / 2.71f));
			}
		}
	}
}

void CustomOBJ::Create_vertex_list() {
	for (int u = 0; u <= q - 1; u++) {
		for (int v = 0; v <= q - 1; v++) {
			int base = (v + u * q) * 4;

			// Texture coordinates based on grid position
			float u_tex = (float)u / q;
			float v_tex = (float)v / q;

			vertex_list[base + 0] = { position_list[v + u * (q + 1)], { u_tex, 1.0f - v_tex } };          // Bottom-left
			vertex_list[base + 1] = { position_list[v + 1 + u * (q + 1)], { u_tex, 1.0f - (v_tex + 1.0f / q) } }; // Bottom-right
			vertex_list[base + 2] = { position_list[v + 1 + (u + 1) * (q + 1)], { u_tex + 1.0f / q, 1.0f - (v_tex + 1.0f / q) } }; // Top-right
			vertex_list[base + 3] = { position_list[v + (u + 1) * (q + 1)], { u_tex + 1.0f / q, 1.0f - v_tex } }; // Top-left
		}
	}
}

void CustomOBJ::Create_index_list() {

	{
		for (int u = 0; u <= q - 1; u++) {
			for (int v = 0; v <= q - 1; v++) {
				int base = (v + u * q) * 6;
				int vert_base = (v + u * q) * 4;
				index_list[base + 0] = vert_base + 0; // Bottom-left
				index_list[base + 1] = vert_base + 1; // Bottom-right
				index_list[base + 2] = vert_base + 2; // Top-right
				index_list[base + 3] = vert_base + 2; // Top-right
				index_list[base + 4] = vert_base + 3; // Top-left
				index_list[base + 5] = vert_base + 0; // Bottom-left
			}
		}
	}
	{
		for (int u = 0; u <= q - 1; u++) {
			for (int v = 0; v <= q - 1; v++) {
				int start = q * q * 6;
				int base = (v + u * q) * 6;
				int vert_base = (v + u * q) * 4;
				index_list[start + base + 5] = vert_base + 0; // Bottom-left
				index_list[start + base + 4] = vert_base + 1; // Bottom-right
				index_list[start + base + 3] = vert_base + 2; // Top-right
				index_list[start + base + 2] = vert_base + 2; // Top-right
				index_list[start + base + 1] = vert_base + 3; // Top-left
				index_list[start + base + 0] = vert_base + 0; // Bottom-left
			}
		}
	}

}