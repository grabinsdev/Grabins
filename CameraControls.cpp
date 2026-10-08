#include "CameraControls.h"

#include <algorithm>
#include <cmath>

void UpdateCameraControls(Camera3D *camera)
{
    Vector3 offset = {
        camera->position.x - camera->target.x,
        camera->position.y - camera->target.y,
        camera->position.z - camera->target.z
    };

    float distance = std::sqrt(
        offset.x * offset.x + offset.y * offset.y + offset.z * offset.z
    );
    float yaw = std::atan2(offset.x, offset.z);
    float pitch = std::asin(offset.y / distance);

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        const Vector2 mouseDelta = GetMouseDelta();
        yaw -= mouseDelta.x * 0.005f;
        pitch += mouseDelta.y * 0.005f;
    }

    pitch = std::max(-1.55334f, std::min(1.55334f, pitch));
    distance *= std::exp(-GetMouseWheelMove() * 0.1f);
    distance = std::max(1.0f, std::min(50.0f, distance));

    const float horizontalDistance = distance * std::cos(pitch);
    camera->position = {
        camera->target.x + horizontalDistance * std::sin(yaw),
        camera->target.y + distance * std::sin(pitch),
        camera->target.z + horizontalDistance * std::cos(yaw)
    };
}
