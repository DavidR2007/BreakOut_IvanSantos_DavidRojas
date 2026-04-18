#pragma once
#include <windows.h>
#include "Scene.h"


class MenuScene : public Scene 
{
	int pos = 0;
	int frame = 0;

public:
	virtual void Start() override
	{
		pos = 0;
		frame = 0;
	}
// El Logo de breakout se ha hecho con un programa web y implementado en el proyecto por IA
	virtual void Render() override
	{
		system("cls");

		ConsoleSetColor(CYAN, BLACK);
		std::cout << "\n\n";
		std::cout << "      ____  _____  ______ ___   _  __ ____  _   _  _____\n";
		std::cout << "     | __ )|  __ \\|  ____/ _ \\ | |/ // __ \\| | | ||_   _|\n";
		std::cout << "     |  _ \\| |__) | |__ / /_\\ \\| ' /| |  | | | | |  | |  \n";
		std::cout << "     | |_) |  _  /|  __| _   _ | . \\| |__| | |_| |  | |  \n";
		std::cout << "     |____/|_| \\_\\|____/_/   \\_\\_|\\_\\\\____/ \\___/   |_|  \n";
		std::cout << "\n\n\n\n";

		renderMenu();
	}

	virtual void Update() override
	{
		bool exitScene = false;
		
		while (!exitScene) 
		{
			Render(); 
			
			Sleep(150); 

			if (GetAsyncKeyState(VK_DOWN))
			{
				pos++;
				if (pos > 3) pos = 0;
			}
			if (GetAsyncKeyState(VK_UP))
			{
				pos--;
				if (pos < 0) pos = 3;
			}
			if (GetAsyncKeyState(VK_RETURN))
			{
				switch (pos)
				{
				case 0:
					nextScene = SceneIndex::GAMEPLAY;
					break;
				case 1:
					nextScene = SceneIndex::RANKING;
					break;
				case 2:
					nextScene = SceneIndex::CREDITOS;
					break;
				case 3:
					exit(0);
					break;
				}
				exitScene = true;
			}
		}
	}

	virtual void renderMenu() 
	{
		ConsoleSetColor(WHITE, BLACK);
		std::cout << "         Usa las flechas arriba/abajo para mover\n";
		std::cout << "            Presiona Enter para seleccionar\n\n\n";
		
		if (pos == 0) 
		{
			ConsoleSetColor(GREEN, BLACK);
			std::cout << "                  >> JUGAR <<\n\n";
		} else 
		{
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                     Jugar\n\n";
		}

		if (pos == 1) 
		{
			ConsoleSetColor(YELLOW, BLACK);
			std::cout << "                 >> RANKING <<\n\n";
		} else 
		{
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                    Ranking\n\n";
		}

		if (pos == 2) 
		{
			ConsoleSetColor(CYAN, BLACK);
			std::cout << "                 >> CREDITOS <<\n\n";
		} else {
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                    Creditos\n\n";
		}

		if (pos == 3) 
		{
			ConsoleSetColor(RED, BLACK);
			std::cout << "                  >> SALIR <<\n\n";
		} else 
		{
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                     Salir\n\n";
		}
		
		ConsoleSetColor(WHITE, BLACK); 
	}
};
