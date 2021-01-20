#include "game.h"
#include "texture_manager.h"
#include "game_object.h"

GameObject* dragon;
GameObject* tela_principal;
GameObject* modo_historia;
GameObject* selecao_nivel;
GameObject* botao_x;
GameObject* botao_play;

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized" << std::endl;

        window = SDL_CreateWindow( title, xpos, ypos, width, height, flags);

        if(window)
        {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        isRunning = true;
    }
    //else
    //{
    //    isRunning = false;
    //}
    dragon = new GameObject("assets/dragon.png", 0, 0);
    tela_principal = new GameObject("assets/tela_principal.png", 0, 0);
    modo_historia = new GameObject("assets/modo_historia.png", 0, 0);
    selecao_nivel = new GameObject("assets/selecao_nivel.png", 0, 0);
    botao_x = new GameObject("assets/botao_x.png", 740, 20);
    botao_play = new GameObject("assets/botao_play.png", 740, 550);

}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update()
{
    dragon->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // stuff
    //dragon->render();
    switch(state)
    {
    case GAME_MENU:
        tela_principal->render();
    break;
    case GAME_STORY:
        modo_historia->render();
        botao_play->render();
        botao_x->render();
        break;
    case GAME_LEVELS:
        selecao_nivel->render();
        botao_x->render();
        break;
    default:
        break;
    }
    SDL_RenderPresent(renderer);

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
