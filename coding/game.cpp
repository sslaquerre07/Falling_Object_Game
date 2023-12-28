#include "Game.h"

//Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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
    this->health = 10;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 20.f;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->endGame = false;

}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}

void Game::initFonts()
{
    if(!this->font.loadFromFile("C:/Falling_Object_Game/Fonts/arial.ttf"))
    {
        std::cout << "Failed to load in the font" << "\n";
    };
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);

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

   //Randomize the enemy type
   int type =  rand() % 5;
   switch (type)
   {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        break;
    
   }


   //Spawn the enemy
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
        //Checks if the health in game is less than 0
        if(this->health <= 0)
            this->window->close();

    }
}

void Game::updateMousePositions()
{
    //Updates the mouse positions relative to window (Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points:" << this->points << "\n"
        << "Health" << this->health << "\n";
    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    //Also responsible for moving enemies downwards
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

    //Moving and updating the enemies
    for(int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 1.f);

        //Check if the enemy is off screen and delete (Remeber top left is 0,0)
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";
        }
    }
    
    //Check if clicked upon:

    /*
    Logic breakdown:
        If button is clicked, check if the left mouse is pressed
        If so, it checks if any of the enemies are within where the mouse is
        If so, remove the enemy from the array of enemies
    */
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //Checks if the mouse is being held down
        if(this->mouseHeld == false)
        {
            //Done to ensure that the mouse cannot be held down
            this->mouseHeld == true;
            bool deleted = false;
            for(size_t i = 0; i < this->enemies.size() && deleted == false;i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {

                    //Gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if(this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 5;
                    else if(this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;
                    std::cout << "Points: " << this->points << "\n";
                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHeld == false;
    }
}

void Game::update()
{
    //Remeber to call this to update the ev variable before you can update anything!
    this->pollEvents();
    if(this->endGame == false)
    {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all of the enemies
    for(auto &e : this->enemies)
    {
        target.draw(e);
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
    this->renderEnemies(*this->window);

    //Render the text for the game
    this->renderText(*this->window);

    this->window->display();
}

