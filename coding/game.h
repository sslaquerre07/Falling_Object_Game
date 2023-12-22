
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>

/*
    Class that acts as the game engine.
    Wrapper class
*/

class Game{
    public:
        //Constructors and Destructors
        Game();
        virtual ~Game();

        //Accessors
        const bool running() const;

        //Functions
        void spawnEnemy();
        
        void pollEvents();
        void updateMousePositions();
        void updateEnemies();
        void update();

        void renderEnemies();
        void render();
    private:
        //Variables 
        //Window
        sf::RenderWindow* window;
        sf::Event ev;
        sf::VideoMode videoMode;

        //Mouse Position
        sf::Vector2i mousePosWindow;

        //Game Logic (Requires initialization)
        int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;

        //Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        //Private Functions
        void initVariables();
        void initWindow();
        void initEnemies();

};

#endif