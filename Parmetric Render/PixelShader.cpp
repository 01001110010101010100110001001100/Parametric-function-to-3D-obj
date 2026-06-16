#include "PixelShader.h"
#include "RenderChicken.h"
#include <exception>

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size,RenderChicken* chicken) : m_chicken(chicken) {
	if (!SUCCEEDED(m_chicken->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("PixelShader not created");
}

PixelShader::~PixelShader() {
	m_ps->Release();
}
