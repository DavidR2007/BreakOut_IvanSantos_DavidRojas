#pragma once
#include <windows.h>
#include "Scene.h"

// Escena del menú principal del juego
class MenuScene : public Scene
{
    int pos = 0;   // Guarda la opción seleccionada del menú
    int frame = 0; // Lo uso por si quiero animaciones simples (aunque aquí no se usa mucho)

public:
    virtual void Start() override
    {
        // Reinicio la posición del menú cada vez que entro a esta escena
        pos = 0;
        frame = 0;
    }

    // El Logo de breakout se ha hecho con un programa web y implementado en el proyecto por IA
    virtual void Render() override
    {
        system("cls"); // Limpio la consola para que no se acumulen cosas

        ConsoleSetColor(CYAN, BLACK);
        std::cout << "\n\n";

        // Dibujo del logo en ASCII
        std::cout << "      ____  _____  ______ ___   _  __ ____  _   _  _____\n";
        std::cout << "     | __ )|  __ \\|  ____/ _ \\ | |/ // __ \\| | | ||_   _|\n";
        std::cout << "     |  _ \\| |__) | |__ / /_\\ \\| ' /| |  | | | | |  | |  \n";
        std::cout << "     | |_) |  _  /|  __| _   _ | . \\| |__| | |_| |  | |  \n";
        std::cout << "     |____/|_| \\_\\|____/_/   \\_\\_|\\_\\\\____/ \\___/   |_|  \n";
        std::cout << "\n\n\n\n";

        // Llamo a la función que pinta las opciones del menú
        renderMenu();
    }

    virtual void Update() override
    {
        bool exitScene = false; // Para saber cuándo salir del bucle del menú

        while (!exitScene)
        {
            Render(); // Redibujo el menú constantemente

            Sleep(150); // Pequeña pausa para que no vaya demasiado rápido

            // Mover hacia abajo en el menú
            if (GetAsyncKeyState(VK_DOWN))
            {
                pos++;
                if (pos > 3) pos = 0; // Si me paso, vuelvo al principio
            }

            // Mover hacia arriba en el menú
            if (GetAsyncKeyState(VK_UP))
            {
                pos--;
                if (pos < 0) pos = 3; // Si subo más de la primera opción, voy a la última
            }

            // Seleccionar opción con Enter
            if (GetAsyncKeyState(VK_RETURN))
            {
                switch (pos)
                {
                case 0:
                    nextScene = SceneIndex::GAMEPLAY; // Ir al juego
                    break;
                case 1:
                    nextScene = SceneIndex::RANKING; // Ver ranking
                    break;
                case 2:
                    nextScene = SceneIndex::CREDITOS; // Créditos
                    break;
                case 3:
                    exit(0); // Salir del programa
                    break;
                }
                exitScene = true; // Salgo del menú
            }
        }
    }

    // Función que pinta las opciones del menú con colores según la selección
    virtual void renderMenu()
    {
        ConsoleSetColor(WHITE, BLACK);
        std::cout << "         Usa las flechas arriba/abajo para mover\n";
        std::cout << "            Presiona Enter para seleccionar\n\n\n";

        // Opción JUGAR
        if (pos == 0)
        {
            ConsoleSetColor(GREEN, BLACK); // Color distinto si está seleccionada
            std::cout << "                  >> JUGAR <<\n\n";
        }
        else
        {
            ConsoleSetColor(WHITE, BLACK);
            std::cout << "                     Jugar\n\n";
        }

        // Opción RANKING
        if (pos == 1)
        {
            ConsoleSetColor(YELLOW, BLACK);
            std::cout << "                 >> RANKING <<\n\n";
        }
        else
        {
            ConsoleSetColor(WHITE, BLACK);
            std::cout << "                    Ranking\n\n";
        }

        // Opción CRÉDITOS
        if (pos == 2)
        {
            ConsoleSetColor(CYAN, BLACK);
            std::cout << "                 >> CREDITOS <<\n\n";
        }
        else
        {
            ConsoleSetColor(WHITE, BLACK);
            std::cout << "                    Creditos\n\n";
        }

        // Opción SALIR
        if (pos == 3)
        {
            ConsoleSetColor(RED, BLACK);
            std::cout << "                  >> SALIR <<\n\n";
        }
        else
        {
            ConsoleSetColor(WHITE, BLACK);
            std::cout << "                     Salir\n\n";
        }

        ConsoleSetColor(WHITE, BLACK); // Vuelvo al color normal
    }
};
