#include "game.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
    game = new Game();

    MEvent event;

    game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running())
    {
        event = game->pollEvent();
        game->handleEvents(event);
        game->update();
        game->render();
    }
    game->clean();

    return 0;
}
