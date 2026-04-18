#pragma once
#include "GameObject.h"
#include "Wall.h"
#include "Brick.h"
#include "Pad.h"

#include <vector>

class Ball : public GameObject 
{
private:
    Vector2 direction;
    std::vector<GameObject*>* objects;

    bool IsCollidingWith(GameObject* other);


public:
    bool isDead;
    bool isStuck;
    Pad* attachedPad;
    int scoreGained;
    int combo;

    Ball(Vector2 newPosition, ConsoleColor newColor, std::vector<GameObject*>& gameObjects)
        : GameObject(newPosition, '@', newColor), isDead(false), isStuck(true), attachedPad(nullptr), scoreGained(0), combo(0) 
        {
        direction = Vector2(1, -1);
        objects = &gameObjects;
    }

    void AttachToPad(Pad* pad) 
    {
        attachedPad = pad;
        isStuck = true;
    }

    void Release() 
    {
        isStuck = false;
        direction = Vector2(1, -1);
        combo = 0;
    }

    void Update() override;
};