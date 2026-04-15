#pragma once
#include "Scene.h"
#include "FileManager.h"

class GameplayScene : public Scene {
    int score;
    


public:
    void CreateWalls() {
        for (int i = 0; i < MAP_SIZE; i++) {
            objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
            objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true));

            if (i > 0 && i < MAP_SIZE - 1) {
                objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
                objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
            }
        }
    }

    void CreateBricks() {
        for (int row = 1; row <= 3; row++) {
            for (int col = 1; col < MAP_SIZE - 1; col++) {
                objects.push_back(new Brick(Vector2(col, row), CYAN));
            }
        }
    }

    void CreatePlayer() {
        objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
    }

    void CreateBall() {
        objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
    }

    void Start() override{
        CreateWalls();
        CreateBricks();
        CreatePlayer();
        CreateBall();
    }

    void Render() override{
        system("cls");
        ConsoleSetColor(WHITE, BLACK);

        for (int i = 0; i < objects.size(); i++) {
            objects[i]->Render();
        }

        ConsoleXY(MAP_SIZE, MAP_SIZE);
    }

    void Update() override{
        bool isPlaying = true;

        while (isPlaying) {
            Sleep(100);

            for (int i = 0; i < objects.size(); i++) {
                objects[i]->Update();
            }
            Render();
            if (GetAsyncKeyState('2'))
            {
                isPlaying = false;
                nextScene = SceneIndex::CREDITOS;
            }

            RankingInfo actualMatch;
			actualMatch.score = score;
			actualMatch.name = "Player";
			FileManager::SaveScore(actualMatch);
            
        }

       
    }

};