#pragma once
#include "Scene.h"

class Gameplay : public Scene {


public:
	void Start()
	{
		std::cout << "Estoy empezando gameplay";
	}


	void Update()
	{
		while (true)
		{
			Sleep(100);
			std::cout << "Estoy en Gameplay";
		}
		
	}

	void Render() override
	{

	}
};