#include "Game.h"

//Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Private Functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game Logic initialization
    this->points = 0;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 500.f;
    this->maxEnemies = 5;

}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);

}

//Accessors
const bool Game::running()const
{
    return this->window->isOpen();
}

//Functions
void Game::spawnEnemy()
{
    /*
        Spawns enemies and sets their colors and positions
        - Both of these properties will be random
        - Adds enemy to the vector
    */
   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
   );

   this->enemy.setFillColor(sf::Color::Green);
   this->enemies.push_back(this->enemy);



}


void Game::pollEvents()
{
    //Event polling
    //Whenever an event occurs, saves it into the ev variable for evaluation
    while(this->window->pollEvent(ev))
    {
        switch(ev.type)
        {
        case sf::Event::Closed:
            //Whenever the window is closed, it sends it to the event ev, the actual closing must be done manually
            this->window->close();
            break;
        //How to check if a key is pressed at all, use for movement!
        case sf::Event::KeyPressed:
            if(ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::updateMousePositions()
{
    //Updates the mouse positions relative to window (Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
    //Also responsible for moving enemies downwards
    //Removes enemies from the screen (TODO)
    //Updating the timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies){
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //Move the enemies (5 down for this example)
    for(auto &e : this->enemies)
    {
        e.move(0.f, 1.f);
    }
}

void Game::update()
{
    //Remeber to call this to update the ev variable before you can update anything!
    this->pollEvents();
    this->updateMousePositions();
    this->updateEnemies();
}

void Game::renderEnemies()
{
    //Rendering all of the enemies
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{
    /*
        - Clear old frame
        - Render Objects
        - Display frame in new window
    */

    this->window->clear();
    //Draw game objects
    this->renderEnemies();

    this->window->display();
}
