#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size,RenderChicken* chicken);
	~PixelShader();
private:
	ID3D11PixelShader* m_ps;
	RenderChicken* m_chicken = nullptr;
private:
	friend class RenderChicken;
	friend class DeviceContext;
};