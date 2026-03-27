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

#define MAP_SIZE 15



int main() {
    srand((unsigned int)time(NULL));

    Scene * myScenes[3];
    bool isExitTime = false;
    myScenes[Scene::MENU] = new MenuScene;
    myScenes[Scene::GAMEPLAY] = new GameplayScene;

    Scene::SceneIndex index = Scene::MENU;

    while(!isExitTime)
    {
        myScenes[index]->Start();
        myScenes[index]->Update();
        index = myScenes[index] -> ChangeScene();
    }
    
    



    return 0;
}
