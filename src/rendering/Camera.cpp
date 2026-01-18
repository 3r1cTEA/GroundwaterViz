#include "Camera.h"
#include <QtMath>

Camera::Camera()
{
    updateVectors();
}

void Camera::moveForward(float delta)
{
    position += front * delta;
    qDebug() << "Camera pos:" << position;
}

void Camera::moveRight(float delta)
{
    position += right * delta;
}

void Camera::moveUp(float delta)
{
    position += up * delta;
}

void Camera::yaw(float degrees)
{
    yawAngle += degrees;
    updateVectors();
}

void Camera::pitch(float degrees)
{
    pitchAngle += degrees;
    pitchAngle = qBound(-89.0f, pitchAngle, 89.0f);
    updateVectors();
}

QMatrix4x4 Camera::viewMatrix() const
{
    QMatrix4x4 view;
    //viewMatrix.lookAt(eye, center, up)
    //gets the math to transform the world relative to the camera
    view.lookAt(position, position + front,up);
    return view;
}

void Camera::updateVectors()
{
    QVector3D f;
        f.setX(qCos(qDegreesToRadians(yawAngle)) * qCos(qDegreesToRadians(pitchAngle)));
        f.setY(qSin(qDegreesToRadians(pitchAngle)));
        f.setZ(qSin(qDegreesToRadians(yawAngle)) * qCos(qDegreesToRadians(pitchAngle)));
        front = f.normalized();

        right = QVector3D::crossProduct(front, QVector3D(0,1,0)).normalized();
        up    = QVector3D::crossProduct(right, front).normalized();
}
