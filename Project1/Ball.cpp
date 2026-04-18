#include "Ball.h"

bool Ball::IsCollidingWith(GameObject* other) {
    return other->IsAtPosition(position);
}

void Ball::Update() {
    if (isStuck) {
        if (attachedPad != nullptr) {
            position.x = attachedPad->GetPosition().x;
            position.y = attachedPad->GetPosition().y - 1;
        }
        if (GetAsyncKeyState(VK_SPACE) != 0) {
            Release();

            direction.x = 1;
            direction.y = -1;
        }
        return;
    }


    if (direction.x != 0) {
        position.x += direction.x;
        for (int i = 0; i < objects->size(); i++) {
            GameObject* currentObject = (*objects)[i];
            if (currentObject == this) continue;

            if (IsCollidingWith(currentObject)) {
                if (currentObject->color == RED) {
                    isDead = true; break;
                }
                bool isPad = (currentObject->charToPrint == '_');

                if (currentObject->charToPrint == '=') {
                    Brick* brick = dynamic_cast<Brick*>(currentObject);
                    if (brick) { brick->destroyed = true; scoreGained += 15 + (combo * 5); combo++; }
                    delete currentObject;
                    objects->erase(objects->begin() + i);
                    i--;
                }


                if (!isPad) {
                    position.x -= direction.x;
                    direction.x = -direction.x;
                }
                break;
            }
        }
    }

    if (direction.y != 0 && !isDead) {
        position.y += direction.y;
        for (int i = 0; i < objects->size(); i++) {
            GameObject* currentObject = (*objects)[i];
            if (currentObject == this) continue;

            if (IsCollidingWith(currentObject)) {
                if (currentObject->color == RED) {
                    isDead = true; break;
                }

                if (currentObject->charToPrint == '=') {
                    Brick* brick = dynamic_cast<Brick*>(currentObject);
                    if (brick) { brick->destroyed = true; scoreGained += 15 + (combo * 5); combo++; }
                    delete currentObject;
                    objects->erase(objects->begin() + i);
                    i--;
                }
                else if (currentObject->charToPrint == '_') // Pad
                {
                    position.y -= direction.y;
                    direction.y = -abs(direction.y);

                    if (attachedPad != nullptr) {
                        int padCentro = attachedPad->GetPosition().x;
                        if (position.x < padCentro) direction.x = -1;
                        else if (position.x > padCentro) direction.x = 1;
                        else direction.x = 0;
                    }
                    combo = 0;
                    break;
                }


                if (currentObject->charToPrint != '_') {
                    position.y -= direction.y;
                    direction.y = -direction.y;
                }
                break;
            }
        }
    }
}
