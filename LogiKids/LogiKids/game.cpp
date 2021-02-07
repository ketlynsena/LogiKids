#include "game.h"
#include "texture_manager.h"
#include "game_object.h"
#include "button.h"
#include "nqueens.h"

GameObject* tela_principal;
GameObject* modo_historia;
GameObject* selecao_nivel;

N_Queens* nrainhas;

SDL_Renderer* Game::renderer = nullptr;

//Buttons objects
Button* botao_x_s;
Button* botao_play_s;
SDL_Rect spriteClips[3];

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        isRunning = true;
    }
    tela_principal  = new GameObject("assets/tela_principal.png", 0, 0);
    modo_historia   = new GameObject("assets/modo_historia.png", 0, 0);
    selecao_nivel   = new GameObject("assets/selecao_nivel.png", 0, 0);
    botao_x_s       = new Button("x", 740, 20);
    botao_play_s    = new Button("play", 740, 550);
    nrainhas = new N_Queens();
}


void Game::handleMenuEvents(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN) {
        state = GAME_STORY;
    }
}

void Game::handleStoryEvents(SDL_Event* event) {
    if (botao_x_s->handleEvent(event)) {
        //printf("Button X was pressed.\n");
        state = GAME_MENU;
    }
    if (botao_play_s->handleEvent(event)) {
        //printf("Button Play was pressed.\n");
        state = GAME_QUEENS;//GAME_LEVELS;
    }
}

void Game::handleNQueensEvents(SDL_Event* event) {
    if (botao_x_s->handleEvent(event)) {
        //printf("Button X was pressed.\n");
        state = GAME_MENU;
    }
    nrainhas->handleEvent(event);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        isRunning = false;
    }
    else {
        switch (state) {
        case GAME_MENU:
            handleMenuEvents(&event);
            break;
        case GAME_STORY:
            handleStoryEvents(&event);
            break;
        case GAME_LEVELS:
            break;
        case GAME_QUEENS:
            handleNQueensEvents(&event);
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    //dragon->update();
    nrainhas->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    switch (state)
    {
    case GAME_MENU:
        tela_principal->render();
        break;
    case GAME_STORY:
        modo_historia->render();
        botao_play_s->render();
        botao_x_s->render();
        break;
    case GAME_LEVELS:
        selecao_nivel->render();
        botao_x_s->render();
        break;
    case GAME_QUEENS:
        nrainhas->render();
        botao_x_s->render();
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
