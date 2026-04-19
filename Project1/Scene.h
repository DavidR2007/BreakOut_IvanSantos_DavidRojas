#pragma once
#include "GameObject.h"
#include <vector>

// Clase base para cualquier pantallita de nuestro juego (menú, créditos, etc.)
class Scene {
public:
    // Un enum chiquito para saber qué escena toca cargar
	enum SceneIndex { MENU, GAMEPLAY, RANKING, CREDITOS};
protected:
	std::vector<GameObject*> objects; // Todos los dibujitos que salen en la escena actual
	SceneIndex nextScene; // ¿A dónde tengo que ir cuando termine esto?

//	Scene();
//	~Scene();
	

public:
	
    // Sirve para iniciar los valores (siempre se llama nada más entrar)
	virtual void Start() = 0;
    
    // Aquí dibujo todo por pantalla (suele limpiar consola antes)
	virtual void Render() = 0;
    
    // El bucle lógico infinito (mira las teclas, mueve cosas...)
	virtual void Update() = 0;

    // Me chiva cuál es la siguiente pantalla a la que me tengo que mover
	SceneIndex ChangeScene()
	{
		return nextScene;
	}
};