#include "GridMesh.h"

GridMesh::GridMesh()
{

}



GridMesh GridMesh::fromGrid3D(const Grid3D &grid)
{
    GridMesh mesh;

       float dx = grid.dx();
       float dy = grid.dy();
       float dz = grid.dz();

       for (int k = 0; k < grid.nz(); ++k)
       for (int j = 0; j < grid.ny(); ++j)
       for (int i = 0; i < grid.nx(); ++i)
       {
           int idx = grid.index(i, j, k);
           float scalar = grid.head()[idx];

           // Cell bounds
           float x0 = i * dx;
           float y0 = j * dy;
           float z0 = k * dz;

           float x1 = x0 + dx;
           float y1 = y0 + dy;
           float z1 = z0 + dz;

           QVector3D p000(x0, y0, z0);
           QVector3D p100(x1, y0, z0);
           QVector3D p010(x0, y1, z0);
           QVector3D p110(x1, y1, z0);

           QVector3D p001(x0, y0, z1);
           QVector3D p101(x1, y0, z1);
           QVector3D p011(x0, y1, z1);
           QVector3D p111(x1, y1, z1);

           // Determine if face is on boundary
           bool left   = (i == 0);
           bool right  = (i == grid.nx() - 1);
           bool front  = (j == 0);
           bool back   = (j == grid.ny() - 1);
           bool bottom = (k == 0);
           bool top    = (k == grid.nz() - 1);

           if (left)
               mesh.addQuad(p000, p001, p011, p010, QVector3D(-1,0,0), scalar);

           if (right)
               mesh.addQuad(p100, p110, p111, p101, QVector3D(1,0,0), scalar);

           if (front)
               mesh.addQuad(p000, p100, p101, p001, QVector3D(0,-1,0), scalar);

           if (back)
               mesh.addQuad(p010, p011, p111, p110, QVector3D(0,1,0), scalar);

           if (bottom)
               mesh.addQuad(p000, p010, p110, p100, QVector3D(0,0,-1), scalar);

           if (top)
               mesh.addQuad(p001, p101, p111, p011, QVector3D(0,0,1), scalar);
       }

       return mesh;
}



void GridMesh::clear()
{
m_vertices.clear();
m_indices.clear();
}



void GridMesh::addQuad(
    const QVector3D& a,
    const QVector3D& b,
    const QVector3D& c,
    const QVector3D& d,
    const QVector3D& normal,
    float scalar)
{
    unsigned int start = static_cast<unsigned int>(m_vertices.size());

    m_vertices.push_back({a, normal, scalar});
    m_vertices.push_back({b, normal, scalar});
    m_vertices.push_back({c, normal, scalar});
    m_vertices.push_back({d, normal, scalar});

    m_indices.push_back(start + 0);
    m_indices.push_back(start + 1);
    m_indices.push_back(start + 2);

    m_indices.push_back(start + 2);
    m_indices.push_back(start + 3);
    m_indices.push_back(start + 0);
}
