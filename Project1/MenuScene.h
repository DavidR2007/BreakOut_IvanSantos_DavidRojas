#pragma once
#include <windows.h>
#include "Scene.h"


class MenuScene : public Scene {
	virtual void Start() 
	{

	};
	int pos = 0;
	int i = 0;
	virtual void Render() 
	{																		
		i++;
		render();
	};
	
	void render() {
		switch (i)
		{
		case 1:
			std::cout << " ___.                __                          __    " << std::endl;
			std::cout << " |  |________ ______ |  | __ ____  ____  __ ____/  |_  " << std::endl;
			std::cout << " | __ |_  __  |__  | |  |/ // __ |/  _ ||  |  |_   __| " << std::endl;
			std::cout << " | |_| |  | |// __ | |    < | ___(  <_> )  |  / |  |   " << std::endl;
			std::cout << " |___  |__|  (____ ) |__|_ ||___> <____/|____/  |__|   " << std::endl;
			renderMenu();
			Sleep(100);
			system("cls");
			break;
		case 2:
			std::cout << "      ___.                __                          __    " << std::endl;
			std::cout << "      |  |________ ______ |  | __ ____  ____  __ ____/  |_  " << std::endl;
			std::cout << "      | __ |_  __  |__  | |  |/ // __ |/  _ ||  |  |_   __| " << std::endl;
			std::cout << "      | |_| |  | |// __ | |    < | ___(  <_> )  |  / |  |   " << std::endl;
			std::cout << "      |___  |__|  (____ ) |__|_ ||___> <____/|____/  |__|   " << std::endl;
			renderMenu();
			Sleep(100);
			system("cls");
			break;
		default:
			i = 0;
			break;
		}
	}


	virtual void Update() 
	{
		bool exitScene = false;
		
		while (!exitScene) {
			Sleep(100);

			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
			}

			if (GetAsyncKeyState('S'))
			{
				if (pos >= 2)
				{
					pos = 0;
				}
				else
				{
					pos++;
				}
			}
			if (GetAsyncKeyState('W'))
			{
				if (pos <= 0)
				{
					pos = 2;
				}
				else
				{
					pos--;
				}
			}
			if (GetAsyncKeyState('E'))
			{
				switch (pos)
				{
				case 0:
					nextScene = SceneIndex::GAMEPLAY;
					break;
				case 1:
					nextScene = SceneIndex::CREDITOS;
					break;
				case 2:
					exit(0);
					break;
				default:
					break;
				}
				exitScene = true;
			}
			Render();
			
		}
		
		

	};
	virtual void renderMenu() {
		switch (pos)
		{
		case 0:
			std::cout << "\033[32m" << "> PLAY <" << "\033[0m" << std::endl;
			std::cout << std::endl;
			std::cout << "  credits" << std::endl;
			std::cout << std::endl;
			std::cout << "  out" << std::endl;
			break;
		case 1:
			std::cout << "  play " << std::endl;
			std::cout << std::endl;
			std::cout << "\033[32m" << "> CREDITS <" << "\033[0m" << std::endl;
			std::cout << std::endl;
			std::cout << "  out" << std::endl;
			break;
		case 2:
			std::cout << "  play " << std::endl;
			std::cout << std::endl;
			std::cout  << "  credits"  << std::endl;
			std::cout << std::endl;
			std::cout << "\033[31m" << "> OUT <" << "\033[0m" <<  std::endl;
			break;
		default:
			break;
		}
		
	}
};
