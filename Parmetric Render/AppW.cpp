#include "AppW.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "Controls.h"
#include "Mesh.h"
#include <stdio.h>
#include <math.h>
#include<iostream>


template <typename T> float sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

struct vertex {
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D m_SX70_position;
};


AppW::AppW() {
}

void AppW::update() {
	constant cc;


	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
	Matrix4x4 temp;
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(m_light_rot_y);

	m_light_rot_y += 0.707f* m_delta_time;

	cc.m_light_direction = m_light_rot_matrix.getZDirection();

	m_delta_scale += m_delta_time / 0.55f; //speed

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));
	//cc.m_world *= temp;


	/*cc.m_world.setScale(Vector3D(m_scale_obj, m_scale_obj, m_scale_obj));
	cc.m_world.setTranslation(Vector3D(m_pos_y, 0 ,m_pos_x));
	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;*/

	cc.m_world.setIdentity();
	Matrix4x4 world_SX70;
	world_SX70.setIdentity();
	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_SX70 *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_SX70 *= temp;

	Vector3D new_pos = m_world_SX70.getTranslation()+ world_SX70.getZDirection() * (m_direction * 0.01f) +
		Vector3D(0.0f, -world_SX70.getZDirection().m_y * (m_direction * 0.01f),0.0f ) + Vector3D(0.0f,m_verticaldir * 0.01f, 0.0f);
	new_pos =new_pos + world_SX70.getXDirection() * (m_seidedir * 0.01f);

	world_SX70.setTranslation(Vector3D(new_pos));

	cc.m_SX70_position = new_pos;

	m_world_SX70 = world_SX70;
	world_SX70.inverse();

	cc.m_view=world_SX70;
	/*cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f);*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext(), &cc);
}

void AppW::drawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, const PixelShaderPtr& ps,const ConstBufferPtr& cb, const TexturePtr& tex) {

	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setConstBuffer(vs, cb);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setConstBuffer(ps, cb);


	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setPixelShader(ps);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setTexture(ps, tex);


	//GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	//GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->drawIndexTriangleList(m_ib->getSizeIndexList(), 0, 0);

	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setVertexBuffer(mesh->getVertexBuffer());
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setIndexBuffer(mesh->getIndexBuffer());
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->drawIndexTriangleList(mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);



}


AppW::~AppW() {
}

void Create_point_list(const int q,Vector3D* position_list) {
	{
		float size = 0.5;
		float x = 0;
		float y = 0;
		float z = 0;
		float a1 = 1.06f;
		float a2 = 10.0f;
		float h = 1.067f;
		float s = cos(h);
		float l = 0.49999999f;
		float q_f = (float)q;
		for (int u = 0; u <= q; u++) {
			for (int v = 0; v <= q; v++) {
				float u_f = ((float)u / q_f - .5f) * 2.0F;
				float v_f = ((float)v / q_f - .5f) * 1.0f;
				y = v_f;
				float q1 = 0.54f * tanh(1.44f * abs(sin(3.14 * u_f))) / 2;
				float k = -.2 * u_f * u_f + .2f;
				z =-.2 +0 * k + q1 * (3 * a1 * (v_f + l) * log(fmaxf(fabs(v_f + l), 1e-6f)) * (1 + sgn(v_f + l)) -
					(exp(-powf(fmaxf(abs(33 * (u_f + .5f)), 1e-6f), 2)) + exp(-powf(fmaxf(abs(33 * (u_f - .5f)), 1e-6f), 2)))
					* a2 / 36.0f * exp(-powf(fmaxf(abs(36.0f * (v_f + 0.03f + l) - 36.0f / 2.71f), 1e-6f), 4))
					- .0f * sin(v_f + l) * (1 + sgn(v_f + l - .01f)));
				x = .8f * u_f * (1 + 0 * exp(-powf(3.7f * (z / a2 * 36 / 8 - .5f), 2)) * cos(u_f / 2 * 2 * 3.14));
				x = x * size;
				y = y * size;
				z = z * size - size;
				position_list[v + u * (q + 1)] = { Vector3D(x,y,z) };
				//if (u == 0) {
				//	printf("Index Access: position_list[%d] = (%f, %f, %f)\n", v, position_list[v].m_x, position_list[v].m_y, position_list[v].m_z);
				//}
				//if (u == 0 && v == 0) {
				//	printf("v_f + l = %f\n", v_f + l);
				//}
				//if (u == 0 && v == 0) {
				//	printf("Pow base: %f\n", (36.0f * (v_f + 0.03f + l) - 36.0f / 2.71f));
				//}
			}
		}
	}
}

void Create_vertex_list(const int q, vertex* vertex_list, Vector3D* position_list) {

	for (int u = 0; u <= q - 1; u++) {
		for (int v = 0; v <= q - 1; v++) {
				int base = (v + u * q) * 4;

			// Texture coordinates based on grid position
			float u_tex = (float)u / q;
			float v_tex = (float)v / q;

			vertex_list[base + 0] = { position_list[v + u * (q + 1)], { u_tex, 1.0f - v_tex } };          // Bottom-left
			vertex_list[base + 1] = { position_list[v + 1 + u * (q + 1)], { u_tex, 1.0f - (v_tex + 1.0f / q) } }; // Bottom-right
			vertex_list[base + 2] = { position_list[v + 1 + (u + 1) * (q + 1)], { u_tex + 1.0f / q, 1.0f - (v_tex + 1.0f / q) } }; // Top-right
			vertex_list[base + 3] = { position_list[v + (u + 1) * (q + 1)], { u_tex + 1.0f / q, 1.0f - v_tex } }; // Top-left
		}
	}
}

void Create_index_list(const int q, unsigned int* index_list) {
	{
		for (int u = 0; u <= q - 1; u++) {
			for (int v = 0; v <= q - 1; v++) {
				int base = (v + u * q) * 6;
				int vert_base = (v + u * q) * 4;
				index_list[base + 0] = vert_base + 0; // Bottom-left
				index_list[base + 1] = vert_base + 1; // Bottom-right
				index_list[base + 2] = vert_base + 2; // Top-right
				index_list[base + 3] = vert_base + 2; // Top-right
				index_list[base + 4] = vert_base + 3; // Top-left
				index_list[base + 5] = vert_base + 0; // Bottom-left
			}
		}
	}
	{
		for (int u = 0; u <= q - 1; u++) {
			for (int v = 0; v <= q - 1; v++) {
				int start = q * q * 6;
				int base = (v + u * q) * 6;
				int vert_base = (v + u * q) * 4;
				index_list[start + base + 5] = vert_base + 0; // Bottom-left
				index_list[start + base + 4] = vert_base + 1; // Bottom-right
				index_list[start + base + 3] = vert_base + 2; // Top-right
				index_list[start + base + 2] = vert_base + 2; // Top-right
				index_list[start + base + 1] = vert_base + 3; // Top-left
				index_list[start + base + 0] = vert_base + 0; // Bottom-left
			}
		}
	}
}

void AppW::onCreate() {
	Window::onCreate();
	Controls::get()->addReciver(this);
	//GraphicsEn::get()->init();
	//GraphicsEn::get()->getRenderChicken()->createSwapChain();  //??

	m_boob_tex = GraphicsEn::get()->getTextureKrak()->createTextureFromFile(L"C:\\...\\Assets\\Textures\\duck.png"); ///!!!!! Modify the path to your local Assets file location 
	m_wood_tex = GraphicsEn::get()->getTextureKrak()->createTextureFromFile(L"C:\\...\\Assets\\Textures\\wood.jpg");
	m_sky_tex = GraphicsEn::get()->getTextureKrak()->createTextureFromFile(L"C:\\..\\Assets\\Textures\\wood.jpg");

	m_mesh = GraphicsEn::get()->getMeshKrak()->createMeshFromFile(L"C:\\Users\\manam\\Desktop\\phen_v4\\SimV4\\.vs\\Assets\\Meshes\\suzanne.obj");
	m_sky_mesh = GraphicsEn::get()->getMeshKrak()->createMeshFromFile(L"C:\\Users\\manam\\Desktop\\phen_v4\\SimV4\\.vs\\Assets\\Meshes\\teapot.obj");

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEn::get()->getRenderChicken()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	

	m_world_SX70.setTranslation(Vector3D(0, 0, -1.5));

	/*
	const int q = 70;
	CustomOBJ obj1(q);
	Vector3D position_list[(q + 1) * (q + 1)];
	for (int i = 0; i < ((q + 1) * (q + 1)); i++) {
		position_list[i] = obj1.Get_point_list()[i];
	}
	vertex vertex_list[(q + 0) * (q + 0) * 4];
	for (int i = 0; i < (q + 0) * (q + 0) * 4; i++) {
		vertex_list[i] = obj1.Get_vertex_list()[i];
	}
	UINT size_list = ARRAYSIZE(vertex_list);
	unsigned int index_list[(q) * (q) * 6 * 2];
	for (int i = 0; i < (q) * (q) * 6 * 2; i++) {
		index_list[i] = obj1.Get_index_list()[i];
	}
	*/
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	const int q = 70;

	Vector3D position_list[(q + 1) * (q + 1)];
	vertex vertex_list[(q + 0) * (q + 0)*4];
	Create_point_list(q, position_list);
	Create_vertex_list(q, vertex_list, position_list);



	Vector2D texcoord_list[4] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};


	UINT size_list = ARRAYSIZE(vertex_list);
	unsigned int index_list[(q)*(q)*6*2];
	Create_index_list(q, index_list);



	////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	/*
	{
		for (int u = 0; u < q - 1; u++) {
			for (int v = 0; v < q - 1; v++) {
				index_list[5 + (v + u * (q - 1)) * 6] = v + u * q;
				index_list[4 + (v + u * (q - 1)) * 6] = v + (1 + u) * q;
				index_list[3 + (v + u * (q - 1)) * 6] = v + 1 + (1 + u) * q;
				index_list[2 + (v + u * (q - 1)) * 6] = v + 1 + (1 + u) * q;
				index_list[1 + (v + u * (q - 1)) * 6] = v + 1 + u * q;
				index_list[0 + (v + u * (q - 1)) * 6] = v + u * q;
			}
		}
	}
	*/


	///Test1
	/*
	vertex vertex_list[] = {
		//x y z RGB

		//Face 1
		{Vector3D(-0.5f,-0.5f,-0.5f), Vector3D(1,0,0), Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),  Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),  Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f), Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//Face 2
		{ Vector3D(0.5f,-0.5f,0.5f),  Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),   Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),  Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f), Vector3D(0,1,0), Vector3D(0,0.2f,0) }

		//{Vector3D(-0.5f,-0.5f,0.0f),Vector3D(-0.32f,-0.11f,0.0f),Vector3D(0,0,0),Vector3D(0,1,0)}, // POS1
		//{Vector3D(-0.5f,0.5f,0.0f),Vector3D(-0.11f,0.78f,0.0f),Vector3D(1,1,0),Vector3D(0,1,1) }, // POS2
		//{Vector3D(0.5f,-0.5f,0.0f),Vector3D(0.75f,-0.73f,0.0f),Vector3D(0,0,1),Vector3D(1,0,0) },// POS2
		//{Vector3D(0.5f,0.5f,0.0f),Vector3D(0.88f,0.77f,0.0f),Vector3D(1,1,1),Vector3D(0,0,1) }
		//{Vector3D(-0.5f,-0.5f,0.0f),Vector3D(0,1,0)}, // POS1
		//{Vector3D(-0.5f,0.5f,0.0f),Vector3D(0,1,1) }, // POS2
		//{Vector3D(0.5f,-0.5f,0.0f),Vector3D(1,0,0) },// POS2
		//{Vector3D(0.5f,0.5f,0.0f),Vector3D(0,0,1) }
	};

	UINT size_list = ARRAYSIZE(vertex_list);
	

	
	unsigned int index_list[] = {
		//Face 1
		0,1,2,
		2,3,0,

		//Face 2
		4,5,6,
		6,7,4,

		//Face 3
		1,6,5,
		5,2,1,

		//Face 4
		7,0,3,
		3,4,7,

		//Face 5
		3,2,5,
		5,4,3,

		//Face 6
		7,6,1,
		1,0,7
	};
	*/

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEn::get()->getRenderChicken()->createIndexBuffer(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEn::get()->getRenderChicken()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEn::get()->getRenderChicken()->createVertexShader(shader_byte_code, size_shader);


	//it does not interfear
	m_vb = GraphicsEn::get()->getRenderChicken()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, (UINT)size_shader);
	GraphicsEn::get()->getRenderChicken()->releaseCompiledShader();

	GraphicsEn::get()->getRenderChicken()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEn::get()->getRenderChicken()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEn::get()->getRenderChicken()->releaseCompiledShader();

	GraphicsEn::get()->getRenderChicken()->compilePixelShader(L"SkyBoxShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_sky_ps = GraphicsEn::get()->getRenderChicken()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEn::get()->getRenderChicken()->releaseCompiledShader();


	constant cc;
	m_cb = GraphicsEn::get()->getRenderChicken()->createConstBuffer(&cc, sizeof(constant));

}

void AppW::onUpdate() {
	Window::onUpdate();
	Controls::get()->update();
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 0, 1, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	update();

	//drawMesh(m_mesh, m_vs, m_ps, m_cb, m_wood_tex);
	//drawMesh(m_sky_mesh, m_vs, m_sky_ps, m_cb, m_sky_tex);


	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setConstBuffer(m_vs, m_cb);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setConstBuffer(m_ps, m_cb);


	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setTexture(m_ps, m_boob_tex);

	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	GraphicsEn::get()->getRenderChicken()->getImmediateDeviceContext()->drawIndexTriangleList(m_ib->getSizeIndexList(), 0, 0);

	m_swap_chain->present(true);
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppW::onDestroy() {
	Window::onDestroy();
	//GraphicsEn::get()->release();
}

void AppW::WinActive(){
	Controls::get()->addReciver(this);
}

void AppW::WinInactive(){
	Controls::get()->removeReciver(this);
}

void AppW::Keyon(int key)
{
	if (key == 'W') {
		//m_pos_x -= 1.5F * m_delta_time;
		m_direction = 1.0f;
	}
	else if (key == 'S') {
		// += 1.5F * m_delta_time;
		m_direction = -1.0f;
	}

	else if (key == 'A') {
		//m_pos_y += 1.5F * m_delta_time;
		m_seidedir = -1.0f;
	}
	else if (key == 'D') {
		//m_pos_y -= 1.5F * m_delta_time;
		m_seidedir = 1.0f;
	}
	else if (key == 'E') {
		m_verticaldir = 1.0f;
	}
	else if (key == 'Q') {
		m_verticaldir = -1.0f;
	}
	else if (key == 'F') {
		m_light_rot_y-= 0.707f* m_delta_time;
	}
}

void AppW::Keyoff(int key){
	m_direction = 0.0f;
	m_seidedir = 0.0f;
	m_verticaldir = 0.0f;
}

void AppW::Mousedynamic(const Point& delta_mouse_pos){
	if (Lmouse_check) {
		m_rot_x -= .314 * delta_mouse_pos.m_y * m_delta_time;
		m_rot_y -= .314 * delta_mouse_pos.m_x * m_delta_time;
	}
}

void AppW::LeftMouseON(const Point& mouse_pos){
	Lmouse_check = true;
}

void AppW::LeftMouseOFF(const Point& mouse_pos){
	Lmouse_check = false;
}

void AppW::RightMouseON(const Point& mouse_pos){
}

void AppW::RightMouseOFF(const Point& mouse_pos){
}
