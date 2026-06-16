#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include <vector>

struct vertex {
	Vector3D position;
	Vector2D texcoord;
};

class CustomOBJ {
public:
	CustomOBJ(size_t q);
	~CustomOBJ();
	 
	void Create_point_list();
	void Create_vertex_list();
	void Create_index_list();
	std::vector<Vector3D> Get_point_list();
	std::vector<vertex>  Get_vertex_list();
	std::vector<unsigned int> Get_index_list();
private:
	std::vector<Vector3D> position_list;
	std::vector<vertex> vertex_list;
	std::vector<unsigned int> index_list;
	int q = 0;
};