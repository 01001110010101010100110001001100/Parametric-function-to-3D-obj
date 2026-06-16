#pragma once
#include <memory>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstBuffer;
class VertexShader;
class PixelShader;
class RenderChicken;
class GraphicsEn;
class Resource;
class Resourcekrak;
class Texture;
class Texturekrak;
class Meshkrak;
class Mesh;

typedef std::shared_ptr<SwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstBuffer> ConstBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<RenderChicken> RenderChickenPtr;
typedef std::shared_ptr<GraphicsEn> GraphicsEnPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
