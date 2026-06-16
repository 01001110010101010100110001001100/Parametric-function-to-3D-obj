#pragma once
#include "Resourcekrak.h"

class Meshkrak: public Resourcekrak {
public:
	Meshkrak();
	~Meshkrak();

	MeshPtr createMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);

};

