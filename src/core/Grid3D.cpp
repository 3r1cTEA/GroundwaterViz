#include "Grid3D.h"


Grid3D::Grid3D(int nx, int ny, int nz, float dx, float dy, float dz)
    : m_nx{nx}, m_ny{ny}, m_nz{nz}, m_dx{dx}, m_dy{dy}, m_dz{dz}
{
    if (nx <=0 || ny <= 0 || nz <=0)
        throw std::runtime_error("grid dimensions must be positive");

    int totalCells = nx * ny * nz;

    head.resize(totalCells, 0.0f);
    kx.resize(totalCells, 1.0f);
    ky.resize(totalCells, 1.0f);
    kz.resize(totalCells, 1.0f);
}

int Grid3D::index(int i, int j, int k) const
{
    if (i<0 || i >= m_nx ||
        j<0 || j >= m_ny ||
        k<0 || k >= m_nz)
        throw std::out_of_range("Grid3D index out of range");

    return k * (m_nx * m_ny) + j * m_nx + i;
}
