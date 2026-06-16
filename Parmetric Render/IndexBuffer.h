#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list,RenderChicken* chicken);
	UINT getSizeIndexList();
	~IndexBuffer();
private:
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	RenderChicken* m_chicken = nullptr;
private:
	friend class DeviceContext;
};
