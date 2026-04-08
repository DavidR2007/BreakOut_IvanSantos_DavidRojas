#pragma once
#include <windows.h>
#include "Scene.h"


class MenuScene : public Scene {
	virtual void Start() 
	{

	};

	virtual void Render() 
	{																		
		std::cout << " ___.                __                          __    "<< std::endl;
		std::cout << " |  |________ ______ |  | __ ____  ____  __ ____/  |_  "<< std::endl;
		std::cout << " | __ |_  __  |__  | |  |/ // __ |/  _ ||  |  |_   __| "<< std::endl;
		std::cout << " | |_| |  | |// __ | |    < | ___(  <_> )  |  / |  |   "<< std::endl;
		std::cout << " |___  |__|  (____ ) |__|_ ||___> <____/|____/  |__|   "<< std::endl;
		renderMenu();
		Sleep(200);
		system("cls");
		std::cout << std::endl;
		std::cout << " ___.                __                          __    " << std::endl;
		std::cout << " |  |________ ______ |  | __ ____  ____  __ ____/  |_  " << std::endl;
		std::cout << " | __ |_  __  |__  | |  |/ // __ |/  _ ||  |  |_   __| " << std::endl;
		std::cout << " | |_| |  | |// __ | |    < | ___(  <_> )  |  / |  |   " << std::endl;
		std::cout << " |___  |__|  (____ ) |__|_ ||___> <____/|____/  |__|   " << std::endl;
		renderMenu();
		Sleep(200);
		system("cls");
	};
				   
	virtual void Update() 
	{
		bool exitScene = false;
		while (!exitScene) {
			Sleep(100);

			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
			}

			if (GetAsyncKeyState('W'))
			{

			}
			if (GetAsyncKeyState('S'))
			{

			}

			Render();
			
		}
		
		nextScene = SceneIndex::GAMEPLAY;

	};
	virtual void renderMenu() {
		std::cout << "Play " << std::endl;
		std::cout << std::endl;
		std::cout << "Out " << std::endl;
	}
};
