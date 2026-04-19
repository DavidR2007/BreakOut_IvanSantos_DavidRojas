#pragma once
#include "GameObject.h"
#include <Windows.h>

// Clase para la pala que controla el jugador
class Pad : public GameObject {
private:
    int width;    // Lo ancha que es la pala
    int mapSize;  // El límite del mapa para no salirme por los bordes

public:
    Pad(Vector2 newPosition, ConsoleColor newColor, int newWidth, int newMapSize)
        : GameObject(newPosition, '_', newColor) {  // Uso '_' para dibujar la pala
        width = newWidth;
        mapSize = newMapSize;
    }

    int GetWidth() const {
        return width;
    }

    // Compruebo si algo choca contra la pala, teniendo en cuenta lo ancha que es
    bool IsAtPosition(Vector2 target) const override {
        // Si no está en la misma altura (eje y), no se tocan seguro
        if (target.y != position.y) return false;
        
        // Si cae en el rango de anchura de la pala (eje x), es choque
        if (target.x >= position.x - width && target.x <= position.x + width) return true;
        
        return false;
    }

    void Update() override;
    void Render() override;
};