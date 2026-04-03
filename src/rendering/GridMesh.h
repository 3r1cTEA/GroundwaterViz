#pragma once

#include <vector>
#include <QVector3D>
#include "Grid3D.h"


class GridMesh
{
public:

    GridMesh();

    struct Vertex{
        QVector3D position;
        QVector3D normal;
        float scalar;
    };

    //update to take Grid3D from core and io
    static GridMesh fromGrid3D(const Grid3D& grid);

    const std::vector<Vertex>& vertices() const {return m_vertices;}
    const std::vector<unsigned int>& indices() const {return m_indices;}

    void clear();

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;


    void addQuad(
        const QVector3D& a,
        const QVector3D& b,
        const QVector3D& c,
        const QVector3D& d,
        const QVector3D& normal,
        float scalar);

};


