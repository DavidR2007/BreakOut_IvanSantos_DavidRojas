#pragma once
#include <windows.h>
#include "Scene.h"


class MenuScene : public Scene {
	int pos = 0;
	int frame = 0;

public:
	virtual void Start() override
	{
		pos = 0;
		frame = 0;
	}

	virtual void Render() override
	{
		system("cls");

		// Logo de Breakout Centrado
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
		
		while (!exitScene) {
			// Para evitar el parpadeo de pantalla constante al hacer cls,
			// debemos renderizar PRIMERO. Asi la consola dibuja la interfaz y el Sleep la mantiene estatica a la vista.
			Render(); 
			
			Sleep(150); // Leve aumento del delay para dar tiempo a soltar la tecla

			if (GetAsyncKeyState('S'))
			{
				pos++;
				if (pos > 3) pos = 0;
			}
			if (GetAsyncKeyState('W'))
			{
				pos--;
				if (pos < 0) pos = 3;
			}
			if (GetAsyncKeyState('E'))
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

	virtual void renderMenu() {
		ConsoleSetColor(WHITE, BLACK);
		std::cout << "              Use W / S para mover\n";
		std::cout << "               Use E para confirmar\n\n\n";
		
		if (pos == 0) {
			ConsoleSetColor(GREEN, BLACK);
			std::cout << "                  >> JUGAR <<\n\n";
		} else {
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                     Jugar\n\n";
		}

		if (pos == 1) {
			ConsoleSetColor(YELLOW, BLACK);
			std::cout << "                 >> RANKING <<\n\n";
		} else {
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                    Ranking\n\n";
		}

		if (pos == 2) {
			ConsoleSetColor(CYAN, BLACK);
			std::cout << "                 >> CREDITOS <<\n\n";
		} else {
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                    Creditos\n\n";
		}

		if (pos == 3) {
			ConsoleSetColor(RED, BLACK);
			std::cout << "                  >> SALIR <<\n\n";
		} else {
			ConsoleSetColor(WHITE, BLACK);
			std::cout << "                     Salir\n\n";
		}
		
		ConsoleSetColor(WHITE, BLACK); // Resetear color
	}
};
