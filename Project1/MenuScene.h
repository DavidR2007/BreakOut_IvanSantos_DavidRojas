#pragma once
#include "Scene.h"


class MenuScene : public Scene {
	virtual void Start() 
	{

	};

	virtual void Render() 
	{
		std::cout << "Menu, presiona 1 para continuar" << std::endl;

	};

	virtual void Update() 
	{
		bool exitScene = false;

		while (!exitScene) {
			Sleep(100);

			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
			}

			exitScene = GetAsyncKeyState('1');

			Render();
		}
		
		nextScene = SceneIndex::GAMEPLAY;

	};
};
