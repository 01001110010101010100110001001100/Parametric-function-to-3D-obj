#pragma once
#include "Resourcekrak.h"

class Texturekrak: public Resourcekrak {

public:
	Texturekrak();
	~Texturekrak();
	TexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) ;
};

