#pragma once
#include <d3d11.h>
#include "Prequisites.h"
#include "RenderChicken.h"
#include "Texturekrak.h"
#include "Meshkrak.h"

class GraphicsEn
{
private:
	GraphicsEn();
	~GraphicsEn();

public:
	//bool init();
	//bool release();
	RenderChicken* getRenderChicken();
	Texturekrak* getTextureKrak();
	Meshkrak* getMeshKrak();
	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);
public:
	static GraphicsEn* get();
	static void create();
	static void release();
private:
	RenderChicken* m_render_chicken = nullptr;
	Texturekrak* m_tex_krak = nullptr;
	Meshkrak* m_mesh_krak = nullptr;
	static GraphicsEn* m_engine;

	unsigned char m_mesh_layout_bite_code[1024]; //remember 
	size_t m_mesh_layout_size = 0;
};

