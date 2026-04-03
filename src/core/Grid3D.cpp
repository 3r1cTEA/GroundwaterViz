#include "Grid3D.h"


Grid3D::Grid3D(int nx, int ny, int nz,
               float dx, float dy, float dz)
    : m_nx(nx),
      m_ny(ny),
      m_nz(nz),
      m_dx(dx),
      m_dy(dy),
      m_dz(dz)
{
    m_head.resize(nx * ny * nz, 0.0f);
}

int Grid3D::cellCount() const
{
    return m_nx * m_ny * m_nz;
}

int Grid3D::index(int i, int j, int k) const
{
    return i + j * m_nx + k * m_nx * m_ny;
}

std::vector<float>& Grid3D::head()
{
    return m_head;
}

const std::vector<float>& Grid3D::head() const
{
    return m_head;
}
