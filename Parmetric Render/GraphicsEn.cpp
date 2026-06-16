#pragma comment(lib,"d3dcompiler.lib")
#include "GraphicsEn.h"
#include "RenderChicken.h"
#include <exception>

GraphicsEn* GraphicsEn::m_engine = nullptr;

GraphicsEn::GraphicsEn() {
	try {
		m_render_chicken = new RenderChicken();
	}
	catch (...) { throw std::exception("GraphicsEn shat its pants"); }

	try {
		m_tex_krak = new Texturekrak();
	}
	catch (...) { throw std::exception("Texturekrak shat its pants"); }

	try {
		m_mesh_krak = new Meshkrak();
	}
	catch (...) { throw std::exception("Meshkrak shat its pants"); }

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_chicken->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_bite_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_chicken->releaseCompiledShader();

}

RenderChicken* GraphicsEn::getRenderChicken(){
	return m_render_chicken;
}

Texturekrak* GraphicsEn::getTextureKrak()
{
	return m_tex_krak;
}

Meshkrak* GraphicsEn::getMeshKrak(){

	return m_mesh_krak;
}

void GraphicsEn::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size){
	*byte_code = m_mesh_layout_bite_code;
	*size = m_mesh_layout_size;


}

GraphicsEn::~GraphicsEn(){
	GraphicsEn::m_engine = nullptr;
	delete m_mesh_krak;
	delete m_tex_krak;
	delete m_render_chicken;
}


GraphicsEn* GraphicsEn::get() {
	return m_engine;
}

void GraphicsEn::create(){
	if (GraphicsEn::m_engine) throw std::exception("GraphicsEn shat its pants twice");
	GraphicsEn::m_engine = new GraphicsEn();
}

void GraphicsEn::release(){
	if (GraphicsEn::m_engine) return;
	delete GraphicsEn::m_engine;
}
