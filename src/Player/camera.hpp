#pragma once
#include <raylib.h>

struct camera
{
    Camera3D cam;

    camera()
    {
        cam.position = { 0, 2, 10 };
        cam.target = { 0, 0, 0 };
        cam.up = { 0, 1, 0 };
        cam.fovy = 100.0f;
        cam.projection = CAMERA_PERSPECTIVE;
    }
};