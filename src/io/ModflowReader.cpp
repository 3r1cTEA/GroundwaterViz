#include "ModflowReader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Grid3D ModflowReader::load(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }

    int nx {0}, ny {0}, nz{0};

    float dx{1.0f}, dy{1.0f}, dz{1.0f};

    std::string line;

    while (std::getline(file, line))
    {
        if (line.find("NX") != std::string::npos)
            nx = std::stoi(line.substr(3));

        else if (line.find("NY") != std::string::npos)
            ny = std::stoi(line.substr(3));

        else if (line.find("NZ") != std::string::npos)
            nz = std::stoi(line.substr(3));

        else if (line.find("DX") != std::string::npos)
            dx = std::stof(line.substr(3));

        else if (line.find("DY") != std::string::npos)
            dy = std::stof(line.substr(3));

        else if (line.find("DZ") != std::string::npos)
            dz = std::stof(line.substr(3));

        else if (line.find("HEAD") != std::string::npos)
            break;
    }

    Grid3D grid(nx, ny, nz, dx, dy, dz);

    int idx = 0;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        float value;

        while (ss>> value)
        {
            if (idx < grid.cellCount())
                grid.head()[idx++] = value;
        }
    }

    std::cout <<"Loaded grid: "
             << nx << "by" << ny << "by" << nz <<std::endl;

    return grid;
}
