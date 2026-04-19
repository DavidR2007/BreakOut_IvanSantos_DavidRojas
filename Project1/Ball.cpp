#include "Ball.h"

// Comprueba si la pelota está ocupando la misma posición que otro objeto
bool Ball::IsCollidingWith(GameObject* other) {
    return other->IsAtPosition(position);
}

void Ball::Update() {

    // Si la pelota está pegada a la pala (al inicio o después de perder una vida)
    if (isStuck) {
        if (attachedPad != nullptr) {
            // Mantengo la pelota justo encima de la pala
            position.x = attachedPad->GetPosition().x;
            position.y = attachedPad->GetPosition().y - 1;
        }

        // Si el jugador pulsa espacio, la pelota se suelta y empieza a moverse
        if (GetAsyncKeyState(VK_SPACE) != 0) {
            Release();

            // Dirección inicial hacia arriba a la derecha
            direction.x = 1;
            direction.y = -1;
        }
        return; // Mientras esté pegada no sigue con el resto de la lógica
    }


    // --- Movimiento horizontal ---
    if (direction.x != 0) {
        position.x += direction.x;

        for (int i = 0; i < objects->size(); i++) {
            GameObject* currentObject = (*objects)[i];
            if (currentObject == this) continue; // Evito colisiones conmigo mismo

            if (IsCollidingWith(currentObject)) {

                // Si toca la línea roja del fondo, la pelota muere
                if (currentObject->color == RED) {
                    isDead = true;
                    break;
                }

                bool isPad = (currentObject->charToPrint == '_'); // '_' es la pala

                // Si choca con un ladrillo
                if (currentObject->charToPrint == '=') {
                    Brick* brick = dynamic_cast<Brick*>(currentObject);
                    if (brick) {
                        brick->destroyed = true;
                        scoreGained += 15 + (combo * 5); // Combo para sumar más puntos
                        combo++;
                    }

                    // Elimino el ladrillo del vector
                    delete currentObject;
                    objects->erase(objects->begin() + i);
                    i--;
                }

                // Rebote horizontal (si no es la pala)
                if (!isPad) {
                    position.x -= direction.x;
                    direction.x = -direction.x;
                }
                else {
                    // Si toca la pala, reinicio el combo
                    combo = 0;
                }

                break;
            }
        }
    }


    // --- Movimiento vertical ---
    if (direction.y != 0 && !isDead) {
        position.y += direction.y;

        for (int i = 0; i < objects->size(); i++) {
            GameObject* currentObject = (*objects)[i];
            if (currentObject == this) continue;

            if (IsCollidingWith(currentObject)) {

                // Si toca la línea roja, muere
                if (currentObject->color == RED) {
                    isDead = true;
                    break;
                }

                bool isPad = (currentObject->charToPrint == '_');

                // Si toca un ladrillo
                if (currentObject->charToPrint == '=') {
                    Brick* brick = dynamic_cast<Brick*>(currentObject);
                    if (brick) {
                        brick->destroyed = true;
                        scoreGained += 15 + (combo * 5);
                        combo++;
                    }

                    delete currentObject;
                    objects->erase(objects->begin() + i);
                    i--;
                }
                // Si toca la pala
                else if (isPad) {
                    // Rebote hacia arriba
                    position.y -= direction.y;
                    direction.y = -abs(direction.y);

                    // Ajusto la dirección horizontal según dónde golpee la pala
                    if (attachedPad != nullptr) {
                        int padCentro = attachedPad->GetPosition().x;

                        if (position.x < padCentro) direction.x = -1;
                        else if (position.x > padCentro) direction.x = 1;
                        else direction.x = 0;
                    }

                    combo = 0; // Reinicio combo al tocar la pala
                    break;
                }

                // Rebote vertical normal (si no es la pala)
                if (!isPad) {
                    position.y -= direction.y;
                    direction.y = -direction.y;
                }

                break;
            }
        }
    }
}
