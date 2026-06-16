#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class ConstBuffer
{
public:
	ConstBuffer(void* buffer, UINT size_buffer,RenderChicken* chicken);
	void update(DeviceContextPtr context, void* buffer);
	~ConstBuffer();
private:
	ID3D11Buffer* m_buffer;
	RenderChicken* m_chicken = nullptr;
private:
	friend class DeviceContext;
};