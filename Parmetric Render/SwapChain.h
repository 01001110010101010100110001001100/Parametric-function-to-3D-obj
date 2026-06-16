#pragma once
#pragma comment(lib,"d3d11.lib")
#include <d3d11.h>
#include "Prequisites.h"

class SwapChain
{
public:
	SwapChain(HWND hwnd,UINT width,UINT height,RenderChicken* chicken);
	bool present(bool vsync);
	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;
	RenderChicken* m_chicken = nullptr;
private:
	friend class DeviceContext;
};

