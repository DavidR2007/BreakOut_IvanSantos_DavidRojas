#pragma once
#include "GameObject.h"

// Los ladrillos que tenemos que romper con la pelota
class Brick : public GameObject 
{
public:
	bool destroyed; // Para saber si ya le he dado un golpe y tengo que borrarlo

	Brick(Vector2 _pos, ConsoleColor c)
		: GameObject(_pos, '=', c), destroyed(false) {} // Cada ladrillo se pinta con un '='

	inline bool GetDestroyed() const { return destroyed; }
	inline void Destroy() { destroyed = true; }

    // Pinto el ladrillo en pantalla solo si no lo han roto todavía
	void Render() override 
	{
		if (!destroyed) 
		{
			GameObject::Render();
		}
	}
};