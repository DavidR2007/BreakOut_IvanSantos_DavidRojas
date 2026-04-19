#pragma once
#include "GameObject.h"

// Clase para las paredes del borde de la pantalla que enmarcan el nivel
class Wall : public GameObject {
protected:
	bool isBottom; // Para saber si es el muro que te mata por debajo
public:
	Wall(Vector2 pos, ConsoleColor c, bool b)
		: GameObject(pos, '#', c), isBottom(b) {} // Uso el símbolo '#' para pintar cada bloque del muro

	inline bool GetIsBottom() const { return isBottom; }
};
