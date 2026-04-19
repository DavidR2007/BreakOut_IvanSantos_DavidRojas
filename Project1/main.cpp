#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Wall.h"
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"
#include "Const.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "RankingScene.h"
#include "CreditosScene.h"

#define MAP_SIZE 15



int main() {
    // Inicializo la semilla aleatoria para cosas como el rebote o colores
    srand((unsigned int)time(NULL));

    // Creo un array para guardar las 4 escenas principales de nuestro juego
    Scene * myScenes[4];
    bool isExitTime = false; // Variable para controlar cuándo cerrar el juego

    // Instancio todas las pantallas que voy a usar
    myScenes[Scene::MENU] = new MenuScene;
    myScenes[Scene::GAMEPLAY] = new GameplayScene;
    myScenes[Scene::RANKING] = new RankingScene;
    myScenes[Scene::CREDITOS] = new CreditosScene;

    // Arrancamos el juego siempre desde el menú principal
    Scene::SceneIndex index = Scene::MENU;

    // Bucle principal del juego (se ejecuta hasta que cerremos la ventana)
    while(!isExitTime)
    {
        // Preparo la escena actual (reseteo las variables, meto los objetos...)
        myScenes[index]->Start();
        
        // Ejecuto la lógica y los pintados de la pantalla que toque ahora mismo
        myScenes[index]->Update();
        
        // Compruebo a qué escena me tengo que mover en la siguiente vuelta del bucle
        index = myScenes[index] -> ChangeScene();
    }
    
    return 0; // Se acabó lo que se daba
}
