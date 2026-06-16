#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>
#include "Prequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderChicken* chicken);
	void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void setIndexBuffer(const IndexBufferPtr& index_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexTriangleList(UINT index_count,UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setPixelShader(const PixelShaderPtr& pixel_shader);

	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr& texture);

	void setConstBuffer(const VertexShaderPtr& vertex_shader, const ConstBufferPtr& buffer);
	void setConstBuffer(const PixelShaderPtr& pixel_shader, const ConstBufferPtr& buffer);
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
	RenderChicken* m_chicken = nullptr;
private:
	friend class ConstBuffer;
};

