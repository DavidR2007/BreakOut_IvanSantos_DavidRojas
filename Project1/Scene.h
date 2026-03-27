#pragma once
#include "GameObject.h"
#include <vector>

class Scene {
public:
	enum SceneIndex { MENU, GAMEPLAY, RANKING };
protected:
	std::vector<GameObject*> objects;
	SceneIndex nextScene;

//	Scene();
//	~Scene();
	

public:
	

	virtual void Start() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

	SceneIndex ChangeScene()
	{
		return nextScene;
	}
};