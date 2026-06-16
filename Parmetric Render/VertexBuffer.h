#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader,RenderChicken* chicken);
	UINT getSizeVertexList();
	~VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderChicken* m_chicken = nullptr;
private:
	friend class DeviceContext;
};

