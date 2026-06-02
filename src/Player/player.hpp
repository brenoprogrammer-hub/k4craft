#pragma once

#include <raylib.h>
#include <cmath>
#include "camera.hpp"

struct Player
{
    camera cam;

    Vector3 position = { 0, 2, 0 };
    Vector3 velocity = { 0, 0, 0 };

    float speed = 6.0f;

    float gravity = -20.0f;
    float jumpStrength = 8.0f;

    bool isOnGround = false;
    float groundLevel = 0.0f;

    float yaw = 0.0f;
    float pitch = 0.0f;
    float mouseSensitivity = 0.1f;

    void Init()
    {
        DisableCursor();
    }

    void Jump()
    {
        if (isOnGround)
        {
            velocity.y = jumpStrength;
            isOnGround = false;
        }
    }

    void Update(float dt)
    {
        Vector2 mouseDelta = GetMouseDelta();

        yaw -= mouseDelta.x * mouseSensitivity;
        pitch -= mouseDelta.y * mouseSensitivity;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        float yawRad = yaw * DEG2RAD;
        float pitchRad = pitch * DEG2RAD;

        Vector3 forwardLook = {
            cosf(pitchRad) * sinf(yawRad),
            sinf(pitchRad),
            cosf(pitchRad) * cosf(yawRad)
        };

        Vector3 forward = {
            sinf(yawRad),
            0,
            cosf(yawRad)
        };

        Vector3 right = {
            forward.z,
            0,
            -forward.x
        };

        if (IsKeyDown(KEY_W)) {
            position.x += forward.x * speed * dt;
            position.z += forward.z * speed * dt;
        }
        if (IsKeyDown(KEY_S)) {
            position.x -= forward.x * speed * dt;
            position.z -= forward.z * speed * dt;
        }
        if (IsKeyDown(KEY_A)) {
            position.x += right.x * speed * dt;
            position.z += right.z * speed * dt;
        }
        if (IsKeyDown(KEY_D)) {
            position.x -= right.x * speed * dt;
            position.z -= right.z * speed * dt;
        }

        if (IsKeyPressed(KEY_SPACE))
            Jump();

        velocity.y += gravity * dt;
        position.y += velocity.y * dt;

        if (position.y <= groundLevel)
        {
            position.y = groundLevel;
            velocity.y = 0;
            isOnGround = true;
        }
        else
        {
            isOnGround = false;
        }

        cam.cam.position = { position.x, position.y + 1.8f, position.z };

        cam.cam.target = {
            cam.cam.position.x + forwardLook.x,
            cam.cam.position.y + forwardLook.y,
            cam.cam.position.z + forwardLook.z
        };
    }
};