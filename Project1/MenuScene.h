#pragma once
#include "Scene.h"


class MenuScene : public Scene {
	virtual void Start() 
	{

	};

	virtual void Render() 
	{
		std::cout << "##################################################" << std::endl;
		std::cout << "#................................................#" << std::endl;
		std::cout << "#....H......H...HHHHHHHH...H.......HHHHHHHH......#" << std::endl;
		std::cout << "#....H......H...H......H...H.......H......H......#" << std::endl;
		std::cout << "#....HHHHHHHH...H......H...H.......HHHHHHHH......#" << std::endl;
		std::cout << "#....H......H...H......H...H.......H......H......#" << std::endl;
		std::cout << "#....H......H...HHHHHHHH...HHHHHH..H......H......#" << std::endl;
		std::cout << "#................................................#" << std::endl;
		std::cout << "##################################################" << std::endl;
		Sleep(200);
		system("cls");
		std::cout << "##################################################" << std::endl;
		std::cout << "#................................................#" << std::endl;
		std::cout << "#....H......H...HHHHHHHH...H.......HHHHHHHH......#" << std::endl;
		std::cout << "#....HHHHHHHH...H......H...H.......H......H......#" << std::endl;
		std::cout << "#....H......H...H......H...H.......H......H......#" << std::endl;
		std::cout << "#....H......H...H......H...H.......HHHHHHHH......#" << std::endl;
		std::cout << "#....H......H...HHHHHHHH...HHHHHH..H......H......#" << std::endl;
		std::cout << "#................................................#" << std::endl;
		std::cout << "##################################################" << std::endl;
		system("cls");
		Sleep(200);
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
