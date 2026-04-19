#pragma once
#include "Scene.h"
#include "FileManager.h"
#include "Ball.h"
#include "Pad.h"
#include "Wall.h"
#include "Brick.h"

// Escena principal donde se juega la partida
class GameplayScene : public Scene {
    int score;     // Puntuación actual del jugador
    int lives;     // Vidas restantes
    Pad* myPad;    // Referencia a la pala del jugador
    Ball* myBall;  // Referencia a la pelota

public:
    GameplayScene() {
        // Valores iniciales de la partida
        score = 0;
        lives = 3;
        myPad = nullptr;
        myBall = nullptr;
    }

    void CreateWalls() {
        // Creo los muros del mapa: arriba, abajo y los laterales
        for (int i = 0; i < MAP_SIZE; i++) {
            // Pared superior e inferior
            objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
            objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), RED, true)); // La roja es la que mata

            // Paredes laterales (evito duplicar esquinas)
            if (i > 0 && i < MAP_SIZE - 1) {
                objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
                objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
            }
        }
    }

    void CreateBricks() {
        // Creo 3 filas de ladrillos en la parte superior
        for (int row = 1; row <= 3; row++) {
            for (int col = 1; col < MAP_SIZE - 1; col++) {
                objects.push_back(new Brick(Vector2(col, row), CYAN));
            }
        }
    }

    void CreatePlayer() {
        // Creo la pala del jugador un poco más ancha para que sea más cómodo
        myPad = new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 2, MAP_SIZE);
        objects.push_back(myPad);
    }

    void CreateBall() {
        // Creo la pelota y la engancho a la pala al inicio
        myBall = new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects);
        myBall->AttachToPad(myPad);
        objects.push_back(myBall);
    }

    void Start() override {
        // Limpio objetos anteriores por si se vuelve a esta escena
        for (GameObject* obj : objects) {
            delete obj;
        }
        objects.clear();

        // Reinicio valores de partida
        score = 0;
        lives = 3;

        // Creo todos los elementos del nivel
        CreateWalls();
        CreateBricks();
        CreatePlayer();
        CreateBall();
    }

    void Render() override {
        system("cls");
        ConsoleSetColor(WHITE, BLACK);

        // Pinto todos los objetos del juego
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->Render();
        }

        // HUD con vidas, puntuación y combo
        ConsoleXY(1, MAP_SIZE + 1);
        std::cout << "Vidas: " << lives << "   Puntos: " << score << "   Combo: x" << (myBall ? myBall->combo : 0) << "    ";

        // Mensaje cuando la pelota está esperando a ser lanzada
        if (myBall && myBall->isStuck) {
            ConsoleXY(1, MAP_SIZE + 2);
            std::cout << "Presiona ESPACIO para lanzar!";
        }

        // Muevo el cursor fuera del mapa para evitar parpadeos
        ConsoleXY(MAP_SIZE, MAP_SIZE);
    }

    void Update() override {
        bool isPlaying = true;

        while (isPlaying) {
            // Velocidad del juego (80 ms queda más fluido que 100)
            Sleep(80);

            // Actualizo todos los objetos
            for (int i = 0; i < objects.size(); i++) {
                objects[i]->Update();
            }

            // Sumo puntos si la pelota ha destruido ladrillos
            if (myBall && myBall->scoreGained > 0) {
                score += myBall->scoreGained;
                myBall->scoreGained = 0;
            }

            Render();

            // Si la pelota cae en la zona roja, se pierde una vida
            if (myBall->isDead) {
                lives--;

                if (lives > 0) {
                    // Si aún quedan vidas, reseteo la pelota
                    myBall->isDead = false;
                    myBall->AttachToPad(myPad);
                }
                else {
                    // Si no quedan vidas, termina la partida
                    isPlaying = false;
                }
            }

            // Compruebo si quedan ladrillos (condición de victoria)
            bool hasBricks = false;
            for (int i = 0; i < objects.size(); i++) {
                if (objects[i]->charToPrint == '=') { // Los ladrillos se dibujan con '='
                    hasBricks = true;
                    break;
                }
            }

            if (!hasBricks) {
                // Si no quedan ladrillos, el jugador gana
                isPlaying = false;
            }
        }

        // Pantalla final de partida
        system("cls");
        ConsoleSetColor(YELLOW, BLACK);
        std::cout << "\n\n   --- FIN DE LA PARTIDA ---\n" << std::endl;

        ConsoleSetColor(WHITE, BLACK);
        std::cout << "   Puntos obtenidos: " << score << std::endl;
        std::cout << "   Introduce tu alias (sin espacios): ";

        std::string nombre;
        std::cin >> nombre;

        // Guardo la puntuación en el archivo
        RankingInfo actualMatch;
        actualMatch.score = score;
        actualMatch.name = nombre;
        FileManager::SaveScore(actualMatch);

        // Cambio a la escena del ranking
        nextScene = SceneIndex::RANKING;
    }

};
