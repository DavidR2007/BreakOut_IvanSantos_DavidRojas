#include "Pad.h"

// Movimiento de la pala controlado por el jugador
void Pad::Update() {
    // Compruebo si el jugador está pulsando las flechas
    bool moveLeft = GetAsyncKeyState(VK_LEFT) != 0;
    bool moveRight = GetAsyncKeyState(VK_RIGHT) != 0;

    if (moveLeft) {
        // Evito que la pala se salga por la izquierda del mapa
        bool canMoveLeft = position.x - width > 1;
        if (canMoveLeft) {
            position.x = position.x - 1;
        }
    }

    if (moveRight) {
        // Evito que la pala se salga por la derecha
        bool canMoveRight = position.x + width < mapSize - 2;
        if (canMoveRight) {
            position.x = position.x + 1;
        }
    }
}

// Dibujo la pala en la pantalla
void Pad::Render() {
    // Pinto el centro de la pala con el método base
    GameObject::Render();

    // Pinto los bordes izquierdo y derecho de la pala según su anchura
    for (int i = 1; i <= width; i++) {
        ConsoleXY(position.x + i, position.y);
        std::cout << charToPrint;

        ConsoleXY(position.x - i, position.y);
        std::cout << charToPrint;
    }
}