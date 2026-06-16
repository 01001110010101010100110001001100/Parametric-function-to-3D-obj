#include "VertexShader.h"
#include "RenderChicken.h"
#include <exception>


VertexShader::VertexShader(const void* shader_byte_code,size_t byte_code_size,RenderChicken* chicken): m_chicken(chicken) {
	if (!SUCCEEDED(m_chicken->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		throw std::exception("VertexShader not created");
}

VertexShader::~VertexShader() {
	m_vs->Release();
}
