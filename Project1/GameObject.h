#pragma once
#include "Vector2.h"
#include "ConsoleControl.h"

class GameObject {
protected:
    Vector2 position;
public:
    ConsoleColor color;
    char charToPrint;
    GameObject(Vector2 newPosition, char newChar, ConsoleColor newColor) {
        position = newPosition;
        charToPrint = newChar;
        color = newColor;
    }

    virtual ~GameObject() = default;

    Vector2 GetPosition() const {
        return position;
    }

    virtual bool IsAtPosition(Vector2 target) const {
        return position == target;
    }

    char GetCharToPrint() const {
        return charToPrint;
    }

    virtual void Update() {
    }

    virtual void Render();
};