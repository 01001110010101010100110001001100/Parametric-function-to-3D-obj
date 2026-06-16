#pragma once
#include <unordered_map>
#include <string>
#include "Prequisites.h"
#include "Resource.h"

class Resourcekrak
{
public:
	Resourcekrak();
	virtual ~Resourcekrak();
	ResourcePtr createResorceFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};

