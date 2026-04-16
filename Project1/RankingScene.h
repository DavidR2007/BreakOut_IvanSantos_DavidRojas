#pragma once
#include <vector>
#include "FileManager.h"

#include <iostream>
#include "Scene.h"
#include "FileManager.h"
#include "ConsoleControl.h"

class RankingScene : public Scene
{
	std::vector<RankingInfo> rankingList;

public:
	RankingScene() {
		rankingList = FileManager::LoadRanking();
	}

	virtual void Start() override {
		// Cargar ultimos datos actualizados
		rankingList = FileManager::LoadRanking(); 
	}

	virtual void Render() override {
		system("cls");
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "\n\n";
		std::cout << "   ========================================\n";
		std::cout << "               TOP PUNTUACIONES            \n";
		std::cout << "   ========================================\n\n";

		ConsoleSetColor(WHITE, BLACK);
		for (int i = 0; i < rankingList.size(); i++) {
			if (i == 0) ConsoleSetColor(YELLOW, BLACK); 
			else if (i == 1) ConsoleSetColor(WHITE, BLACK); 
			else if (i == 2) ConsoleSetColor(RED, BLACK); 
			else ConsoleSetColor(WHITE, BLACK);

			std::cout << "      " << (i + 1) << ". " << rankingList[i].name << " - " << rankingList[i].score << " Pts\n";
		}

		if (rankingList.empty()) {
			std::cout << "      Todavia no hay registros.\n";
		}

		std::cout << "\n";
		ConsoleSetColor(CYAN, BLACK);
		std::cout << "   ========================================\n\n";
		ConsoleSetColor(WHITE, BLACK);
		std::cout << "      Presiona '1' para ver CREDITOS\n";
		std::cout << "      Presiona '2' para volver al MENU PRINCIPAL\n";
	}

	virtual void Update() override {
		bool exitScene = false;
		while (!exitScene) {
			Render();
			Sleep(150);

			if (GetAsyncKeyState('1')) {
				nextScene = SceneIndex::CREDITOS;
				exitScene = true;
			}
			if (GetAsyncKeyState('2')) {
				nextScene = SceneIndex::MENU;
				exitScene = true;
			}
		}
	}
};