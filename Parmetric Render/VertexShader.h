#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size,RenderChicken* chicken);
	~VertexShader();
private:
	ID3D11VertexShader* m_vs;
	RenderChicken* m_chicken=nullptr;
private:
	friend class RenderChicken;
	friend class DeviceContext;
};

