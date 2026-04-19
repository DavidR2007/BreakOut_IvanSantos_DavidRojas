#pragma once
#include "GameObject.h"
#include "Wall.h"
#include "Brick.h"
#include "Pad.h"

#include <vector>

// La clase para la pelota del juego
class Ball : public GameObject 
{
private:
    Vector2 direction; // Indica hacia dónde se está moviendo (x, y)
    std::vector<GameObject*>* objects; // Un puntero a todos los objetos del mapa para comprobar choques

    // Método privado para ver si estoy tocando otro objeto concreto
    bool IsCollidingWith(GameObject* other);

public:
    bool isDead; // Si se me ha caído a la zona roja de abajo
    bool isStuck; // Si está pegada a la pala sin moverse
    Pad* attachedPad; // Referencia a la pala a la que estoy pegado
    int scoreGained; // Puntos que llevo ganados en este fotograma
    int combo; // Mi racha de ladrillos rotos sin tocar la pala

    // Constructor donde inicializo todas las movidas
    Ball(Vector2 newPosition, ConsoleColor newColor, std::vector<GameObject*>& gameObjects)
        : GameObject(newPosition, '@', newColor), isDead(false), isStuck(true), attachedPad(nullptr), scoreGained(0), combo(0) 
        {
        direction = Vector2(1, -1); // Por defecto salgo hacia arriba a la derecha
        objects = &gameObjects;
    }

    // Para pegar la pelota a la pala (útil al empezar la partida o al perder vida)
    void AttachToPad(Pad* pad) 
    {
        attachedPad = pad;
        isStuck = true;
    }

    // Función que suelta la pelota al pulsar la tecla espacio
    void Release() 
    {
        isStuck = false;
        direction = Vector2(1, -1); // Reseteo su dirección inicial por si acaso
        combo = 0; // Se pierde el multiplicador al soltarla
    }

    // Actualiza la lógica de movimiento y rebotes
    void Update() override;
};