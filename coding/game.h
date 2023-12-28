
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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
        void updateText();
        void updateEnemies();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
    private:
        //Variables 
        //Window
        sf::RenderWindow* window;
        sf::Event ev;
        sf::VideoMode videoMode;

        //Mouse Position
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //Resources 
        sf::Font font;

        //Text
        sf::Text uiText;

        //Game Logic (Requires initialization)
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;

        //Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        //Private Functions
        void initVariables();
        void initWindow();
        void initEnemies();
        void initFonts();
        void initText();

};

#endif