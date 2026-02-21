#include "GridMesh.h"

GridMesh::GridMesh()
{

}

void GridMesh::buildFromGrid()
{

}

void GridMesh::buildTestGrid(int nx, int ny, int nz, float dx, float dy, float dz)
{
    clear();

    for (int i {0}; i < nx; ++i)
    {
        for (int j{0}; j < ny; ++j)
        {
            for (int k{0}; k < nz; ++k)
            {
                QVector3D paaa(i * dx,     j * dy,     k * dz);
                QVector3D pbaa((i+1)*dx,   j * dy,     k * dz);
                QVector3D paba(i * dx,    (j+1)*dy,    k * dz);
                QVector3D pbba((i+1)*dx,  (j+1)*dy,    k * dz);

                QVector3D paab(i * dx,     j * dy,    (k+1)*dz);
                QVector3D pbab((i+1)*dx,   j * dy,    (k+1)*dz);
                QVector3D pabb(i * dx,    (j+1)*dy,   (k+1)*dz);
                QVector3D pbbb((i+1)*dx,  (j+1)*dy,   (k+1)*dz);

                if (i == 0)
                    addQuad(paaa, paab, pabb, paba, QVector3D(-1,0,0));
                if (i == nx - 1)
                    addQuad(pbaa, pbba, pbbb, pbab, QVector3D(1,0,0));
                if (j == 0)
                    addQuad(paaa, pbaa, pbab, paab, QVector3D(0,-1,0));
                if (j == ny - 1)
                    addQuad(paba, pabb, pbbb, pbba, QVector3D(0,1,0));
                if (k == 0)
                    addQuad(paaa, paba, pbba, pbaa, QVector3D(0,0,1));
                if (k == nz - 1)
                    addQuad(paab, pbab, pbbb, pabb, QVector3D(0,0,-1));

            }
        }
    }
}

void GridMesh::clear()
{
m_vertices.clear();
m_indices.clear();
}

void GridMesh::addQuad(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d, const QVector3D &normal)
{
    unsigned int startIndex = static_cast<unsigned int>(m_vertices.size());

    m_vertices.push_back({a, normal});
    m_vertices.push_back({b, normal});
    m_vertices.push_back({c, normal});
    m_vertices.push_back({d, normal});


    m_indices.push_back(startIndex + 0);
    m_indices.push_back(startIndex + 1);
    m_indices.push_back(startIndex + 2);


    m_indices.push_back(startIndex + 0);
    m_indices.push_back(startIndex + 2);
    m_indices.push_back(startIndex + 3);
}
