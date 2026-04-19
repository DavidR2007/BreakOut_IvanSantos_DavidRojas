#include "GameObject.h"

// Pintado genérico para casi cualquier objeto en la consola
void GameObject::Render()
{
	ConsoleSetColor(color, BLACK); // Le pongo su colorcito sobre fondo negro
	ConsoleXY(position.x, position.y); // Llevo el cursor del texto a su posición
	std::cout << charToPrint; // Y lo pinto por pantalla
}
