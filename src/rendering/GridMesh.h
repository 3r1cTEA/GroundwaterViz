#pragma once

#include <vector>
#include <QVector3D>



class GridMesh
{
public:

    GridMesh();

    struct Vertex{
        QVector3D position;
        QVector3D normal;
    };

    //update to take Grid3D from core and io
    void buildFromGrid();

    void buildTestGrid(int nx, int ny, int nz, float dx, float dy, float dz);

    const std::vector<Vertex>& vertices() const {return m_vertices;}
    const std::vector<unsigned int>& indices() const {return m_indices;}

    void clear();

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    void addQuad(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D& d, const QVector3D& normal);


};


