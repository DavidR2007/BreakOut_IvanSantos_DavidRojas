#pragma once
#include "Scene.h"
#include "FileManager.h"

class GameplayScene : public Scene {
    int score;
    int lives;
    Pad* myPad;
    Ball* myBall;

public:
    GameplayScene() {
        score = 0;
        lives = 3;
        myPad = nullptr;
        myBall = nullptr;
    }

    void CreateWalls() {
        for (int i = 0; i < MAP_SIZE; i++) {
            objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
            objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), RED, true));

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
        myPad = new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 2, MAP_SIZE); // Pala un poco más ancha
        objects.push_back(myPad);
    }

    void CreateBall() {
        myBall = new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects);
        myBall->AttachToPad(myPad);
        objects.push_back(myBall);
    }

    void Start() override {
        for (GameObject* obj : objects) {
            delete obj;
        }
        objects.clear();

        score = 0;
        lives = 3;

        CreateWalls();
        CreateBricks();
        CreatePlayer();
        CreateBall();
    }

    void Render() override {
        system("cls");
        ConsoleSetColor(WHITE, BLACK);

        for (int i = 0; i < objects.size(); i++) {
            objects[i]->Render();
        }

        ConsoleXY(1, MAP_SIZE + 1);
        std::cout << "Vidas: " << lives << "   Puntos: " << score;
        if (myBall && myBall->isStuck) {
            ConsoleXY(1, MAP_SIZE + 2);
            std::cout << "Presiona ESPACIO para lanzar!";
        }

        ConsoleXY(MAP_SIZE, MAP_SIZE);
    }

    void Update() override {
        bool isPlaying = true;

        while (isPlaying) {
            // El limite de delay baja a 80ms para que la respuesta de movimiento en consola se sienta fluida.
            Sleep(80); 

            for (int i = 0; i < objects.size(); i++) {
                objects[i]->Update();
            }


            if (myBall && myBall->scoreGained > 0) {
                score += myBall->scoreGained;
                myBall->scoreGained = 0;
            }

            Render();

            if (myBall->isDead) { // Si la bola toca fondo
                lives--;
                if (lives > 0) {
                    myBall->isDead = false;
                    myBall->AttachToPad(myPad);
                }
                else {
                    isPlaying = false;
                }
            }

            // Comprobar si quedan ladrillos
            bool hasBricks = false;
            for (int i = 0; i < objects.size(); i++) {
                if (objects[i]->charToPrint == '=') {
                    hasBricks = true;
                    break;
                }
            }

            if (!hasBricks) { 
                isPlaying = false;
            }
        } // Fin del bucle jugable

        // --- FIN DE PARTIDA ---
        system("cls");
        ConsoleSetColor(YELLOW, BLACK);
        std::cout << "\n\n   --- FIN DE LA PARTIDA ---\n" << std::endl;
        ConsoleSetColor(WHITE, BLACK);
        std::cout << "   Puntos obtenidos: " << score << std::endl;
        std::cout << "   Introduce tu alias (sin espacios): ";
        
        std::string nombre;
        std::cin >> nombre;

        // Guardar progreso en el fichero
        RankingInfo actualMatch;
        actualMatch.score = score;
        actualMatch.name = nombre;
        FileManager::SaveScore(actualMatch);

        // Ir al tablero de record
        nextScene = SceneIndex::RANKING;
    }

};