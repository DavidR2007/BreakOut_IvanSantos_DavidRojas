#pragma once
#pragma once
#include "Scene.h"


class CreditosScene : public Scene {
	virtual void Start()
	{

	};

	virtual void Render()
	{
		system("cls");
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "##################################################" << std::endl;
		std::cout << "#                                                #" << std::endl;
		ConsoleSetColor(YELLOW, BLACK);
		std::cout << "#             BREAKOUT - GAME OVER               #" << std::endl;
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "#                                                #" << std::endl;
		std::cout << "##################################################" << std::endl;
		std::cout << "#                                                #" << std::endl;
		std::cout << "#   Desarrollado por:                            #" << std::endl;
		ConsoleSetColor(WHITE, BLACK);
		std::cout << "#   > Ivan Santos Polo                           #" << std::endl;
		std::cout << "#   > David Rojas Herreros                       #" << std::endl;
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "#                                                #" << std::endl;
		ConsoleSetColor(GREEN, BLACK);
		std::cout << "#   Curso: DAMVIOD1                              #" << std::endl;
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "#                                                #" << std::endl;
		std::cout << "##################################################" << std::endl;
		std::cout << std::endl;
		ConsoleSetColor(WHITE, BLACK);
		std::cout << "      Presiona '1' para volver al Menu Principal  " << std::endl;
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

		nextScene = SceneIndex::MENU;

	};
};
