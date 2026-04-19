#pragma once
#include "Vector2.h"
#include "ConsoleControl.h"

// Clase base para cualquier cosa que salga en pantalla (pala, bola, paredes...)
class GameObject {
protected:
    Vector2 position; // Dónde está colocado en el mapa
public:
    ConsoleColor color; // El colorcito que le toca
    char charToPrint;   // El símbolo con el que se dibuja en consola
    
    GameObject(Vector2 newPosition, char newChar, ConsoleColor newColor) {
        position = newPosition;
        charToPrint = newChar;
        color = newColor;
    }

    virtual ~GameObject() = default;

    Vector2 GetPosition() const {
        return position;
    }

    // Comprueba si choco exactamente en esta coordenada (para objetos de 1x1)
    virtual bool IsAtPosition(Vector2 target) const {
        return position == target;
    }

    char GetCharToPrint() const {
        return charToPrint;
    }

    // Lo dejo vacío para sobrescribirlo en cada hijo con su propia lógica (moverse, etc)
    virtual void Update() {
    }

    // Cada hijo pintará lo suyo o tirará de este render padre
    virtual void Render();
};