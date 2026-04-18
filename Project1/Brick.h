#pragma once
#include "GameObject.h"

class Brick : public GameObject 
{
public:
	bool destroyed;
	Brick(Vector2 _pos, ConsoleColor c)
		: GameObject(_pos, '=', c), destroyed(false) {}
	inline bool GetDestroyed() const { return destroyed; }
	inline void Destroy() { destroyed = true; }

	void Render() override 
	{
		if (!destroyed) 
		{
			GameObject::Render();
		}
	}
};