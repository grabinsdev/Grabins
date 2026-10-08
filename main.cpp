#include "Window.h"
#include "font.h"
#include "CameraControls.h"

#include <cmath>
#include <vector>

int main()
{
    WindowInit("Grabins!");

#ifdef __APPLE__
    const char *modelPath = TextFormat(
        "%s../../../model.glb",
        GetApplicationDirectory()
    );
#else
    const char *modelPath = TextFormat(
        "%s/model.glb",
        GetApplicationDirectory()
    );
#endif

    Model model = LoadModel(modelPath);
    Font f = LoadSans();
    const float gridSize = 0.01f;
    std::vector<std::vector<float>> originalVertices(model.meshCount);
    std::vector<std::vector<float>> originalNormals(model.meshCount);

    for (int meshIndex = 0; meshIndex < model.meshCount; meshIndex++)
    {
        Mesh &mesh = model.meshes[meshIndex];
        const int componentCount = mesh.vertexCount * 3;
        originalVertices[meshIndex].assign(
            mesh.vertices,
            mesh.vertices + componentCount
        );
        if (mesh.normals != nullptr)
        {
            originalNormals[meshIndex].assign(
                mesh.normals,
                mesh.normals + componentCount
            );
        }
    }

    Camera3D camera = {
        {0, 0, 6},
        {0, 0, 0},
        {0, 1, 0},
        45,
        CAMERA_PERSPECTIVE
    };

    while (!WindowShouldClose())
    {
        UpdateCameraControls(&camera);

        BeginDrawing();
        ClearBackground(BLACK);

        const float angle = static_cast<float>(GetTime()) * 45.0f * DEG2RAD;
        const float c = cosf(angle);
        const float s = sinf(angle);

        for (int meshIndex = 0; meshIndex < model.meshCount; meshIndex++)
        {
            Mesh &mesh = model.meshes[meshIndex];
            for (int vertexIndex = 0; vertexIndex < mesh.vertexCount; vertexIndex++)
            {
                const int i = vertexIndex * 3;
                const float x = originalVertices[meshIndex][i];
                const float y = originalVertices[meshIndex][i + 1];
                const float z = originalVertices[meshIndex][i + 2];

                mesh.vertices[i] = std::round((x * c + z * s) / gridSize) * gridSize;
                mesh.vertices[i + 1] = std::round(y / gridSize) * gridSize;
                mesh.vertices[i + 2] = std::round((-x * s + z * c) / gridSize) * gridSize;

                if (mesh.normals != nullptr)
                {
                    const float nx = originalNormals[meshIndex][i];
                    const float ny = originalNormals[meshIndex][i + 1];
                    const float nz = originalNormals[meshIndex][i + 2];
                    mesh.normals[i] = nx * c + nz * s;
                    mesh.normals[i + 1] = ny;
                    mesh.normals[i + 2] = -nx * s + nz * c;
                }
            }

            UpdateMeshBuffer(
                mesh,
                0,
                mesh.vertices,
                static_cast<int>(mesh.vertexCount * 3 * sizeof(float)),
                0
            );
            if (mesh.normals != nullptr)
            {
                UpdateMeshBuffer(
                    mesh,
                    2,
                    mesh.normals,
                    static_cast<int>(mesh.vertexCount * 3 * sizeof(float)),
                    0
                );
            }
        }

        BeginMode3D(camera);
        DrawModel(model, {0, 0, 0}, 1.0f, WHITE);
        EndMode3D();
        DrawTextEx(f, "Grabins!", {300, 100}, 20, 2, LIGHTGRAY);
        EndDrawing();
    }

    UnloadModel(model);
    UnloadFont(f);
    CloseWindow();
    return 0;
}