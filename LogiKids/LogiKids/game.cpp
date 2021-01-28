#include "game.h"
#include "texture_manager.h"
#include "game_object.h"
#include "button.h"

GameObject* dragon;
GameObject* tela_principal;
GameObject* modo_historia;
GameObject* selecao_nivel;
GameObject* botao_x;
GameObject* botao_play;
GameObject* n_rainhas;

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
    dragon = new GameObject("assets/dragon.png", 0, 0);
    tela_principal = new GameObject("assets/tela_principal.png", 0, 0);
    modo_historia = new GameObject("assets/modo_historia.png", 0, 0);
    selecao_nivel = new GameObject("assets/selecao_nivel.png", 0, 0);
    botao_x = new GameObject("assets/botao_x.png", 740, 20);
    botao_play = new GameObject("assets/botao_play.png", 740, 550);
    botao_x_s = new Button();
    botao_x_s->setPosition(740, 20);
    botao_play_s = new Button();
    botao_play_s->setPosition(740, 550);
    n_rainhas = new GameObject("assets/nrainhas.png", 0, 0);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (botao_x_s->currentState() == BUTTON_SPRITE_MOUSE_DOWN || botao_play_s->currentState() == BUTTON_SPRITE_MOUSE_DOWN)
        {
            if (state == GAME_MENU) {
                state = GAME_STORY;
            }
            else if (state == GAME_STORY)
            {
                state = GAME_LEVELS;
            }
            else if (state == GAME_LEVELS)
            {
                state = GAME_STORY;
            }
        }

        break;
    case SDL_KEYDOWN:
        if (state == GAME_MENU) {
            state = GAME_STORY;
        }
        else if (state == GAME_STORY)
        {
            state = GAME_LEVELS;
        }
        else if (state == GAME_LEVELS)
        {
            state = GAME_QUEENS;
        }
        else if (state == GAME_QUEENS)
        {
            state = GAME_MENU;
        }
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
    switch (state)
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
    case GAME_QUEENS:
        n_rainhas->render();
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
