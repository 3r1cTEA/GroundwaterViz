#pragma once

#include <vector>
#include <stdexcept>



class Grid3D
{
public:
    Grid3D(int nx, int ny, int nz, float dx, float dy, float dz);

    //dimensions
    int nx() const {return m_nx;}
    int ny() const {return m_ny;}
    int nz() const {return m_nz;}

    float dx() const {return m_dx;}
    float dy() const {return m_dy;}
    float dz() const {return m_dz;}

    int cellCount() const;

    int index(int i, int j, int k) const;

    std::vector<float>& head();
    const std::vector<float>& head() const;

private:
    int m_nx, m_ny, m_nz;
    float m_dx, m_dy, m_dz;

    std::vector<float> m_head;
};


