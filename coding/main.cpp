#include <iostream>
#include "game.h"



int main()
{   
    //Init srand
    srand(static_cast<unsigned>(time(NULL)));
    //Init Game engine(Calls default ctor)
    Game game;

    //Game Loop
    while(game.running()){
        //Update the Game
        game.update();
        //Render to the screen
        game.render();
    }
    //End of application
    return 0;
}