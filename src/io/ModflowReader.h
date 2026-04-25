#pragma once

#include <string>
#include "Grid3D.h"

class ModflowReader
{
public:
    static Grid3D load(const std::string& filename);
};
