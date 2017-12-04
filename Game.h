#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#define WINDOW_WIDHT    1600
#define WINDOW_HEIGHT   900

#include "Entities/Player.h"
#include "Entities/Ennemy.h"
#include "System/ATH.h"


#define ANTI_ALIAS      4

class Player;

class OSSAM
{
    public:
        enum GameStates{Playing, OnInventory, Paused};

    public:
        OSSAM();

        void Play();

        void HandleTime();
        void HandleEvents();
        void HandleAnnimation();
        void HandlePhysics();
        void HandleDisplay(); // return FPS
        Player *Captain;
        Ennemy *Bleuton;
        Ennemy *Vador;
        Ennemy *Picard;


    private:
        unsigned int GameState;

        sf::View GameView;
        sf::View ATH_View;

        sf::Sprite Background;
        sf::Texture Text_Background;

        Inventory *OpenedInventory;
        sf::RenderWindow Window;
};

#endif // GAME_H
