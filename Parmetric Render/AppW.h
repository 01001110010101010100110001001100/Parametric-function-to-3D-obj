#pragma once
#pragma comment(lib,"d3d11.lib") 
#include "Window.h"
#include "GraphicsEn.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputReciver.h"
#include "Matrix4x4.h"


class AppW: public Window,public InputReciver
{
public:
	AppW();
	void update();
	~AppW();
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void WinActive() override;
	virtual void WinInactive() override;
	// Inherited via InputReciver
	virtual void Keyon(int key) override;
	virtual void Keyoff(int key) override;
	virtual void Mousedynamic(const Point& delta_mouse_pos) override;

	virtual void LeftMouseON(const Point& mouse_pos) override;
	virtual void LeftMouseOFF(const Point& mouse_pos) override;
	virtual void RightMouseON(const Point& mouse_pos) override;
	virtual void RightMouseOFF(const Point& mouse_pos) override;
	//void Meshbuild(vertex vertex_list[], int q);
	//void Meshbuild_id(unsigned int index_list[], int q);
public:
	void drawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, const PixelShaderPtr& ps,
		const ConstBufferPtr& cb, const TexturePtr& tex);

private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps; 
	PixelShaderPtr m_sky_ps;
	ConstBufferPtr m_cb;

	TexturePtr m_wood_tex;
	TexturePtr m_sky_tex;
	TexturePtr m_boob_tex;
	MeshPtr m_mesh;
	MeshPtr m_sky_mesh;

	IndexBufferPtr m_ib;
	VertexBufferPtr m_vb;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_pos_x = 0.0f;
	float m_pos_y = 0.0f;
	float m_direction = 0.0f;
	float m_seidedir = 0.0f;
	float m_verticaldir = 0.0f;

	float m_light_rot_y = 0.0f;

	float m_scale_obj = 1;
	bool Lmouse_check = false;

	Matrix4x4 m_world_SX70;

};

