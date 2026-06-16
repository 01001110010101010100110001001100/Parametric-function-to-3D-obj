#include "Meshkrak.h"
#include "Mesh.h"

Meshkrak::Meshkrak(){

}

Meshkrak::~Meshkrak(){

}

MeshPtr Meshkrak::createMeshFromFile(const wchar_t* file_path){
	return std::static_pointer_cast<Mesh>(createResorceFromFile(file_path));
}

Resource* Meshkrak::createResourceFromFileConcrete(const wchar_t* file_path){
    Mesh* mesh = nullptr;
    try {
        mesh = new Mesh(file_path);
    }
    catch (...) {}
    return mesh;
}
