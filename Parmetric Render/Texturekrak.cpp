#include "Texturekrak.h"
#include "Texture.h"

Texturekrak::Texturekrak(): Resourcekrak()
{
}

Texturekrak::~Texturekrak()
{
}

TexturePtr Texturekrak::createTextureFromFile(const wchar_t* file_path)
{
    return std::static_pointer_cast<Texture>(createResorceFromFile(file_path));
}

Resource* Texturekrak::createResourceFromFileConcrete(const wchar_t* file_path){

    Texture* tex = nullptr;
    try {
        tex = new Texture(file_path);
    }
    catch (...){}
    return tex;
}
