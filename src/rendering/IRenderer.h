#pragma once

class Camera;

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual void initialize() = 0;

    virtual void render(const Camera& camera) = 0;
};
