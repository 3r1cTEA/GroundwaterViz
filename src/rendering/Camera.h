#pragma once
#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
    Camera();

    //movement
    void moveForward(float delta);
    void moveRight(float delta);
    void moveUp(float delta);

    //rotate
    void yaw(float degrees);
    void pitch(float degrees);

    //matrix to return
    QMatrix4x4 viewMatrix() const;



private:
    QVector3D position {0.0f, 0.0f, 3.0f};
    QVector3D front    {0.0f, 0.0f, -1.0f};
    QVector3D up       {0.0f, 1.0f, 0.0f};
    QVector3D right    {1.0f, 0.0f, 0.0f};

    float yawAngle{-90.0f};
    float pitchAngle{0.0f};

    void updateVectors();


};


