#include "game.h"
#include "texture_manager.h"
#include "game_object.h"
#include "button.h"
#include "nqueens.h"

GameObject* tela_principal;
GameObject* modo_historia;
GameObject* selecao_nivel;
GameObject* parabens;
GameObject* overlay;

N_Queens* nrainhas;

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::gFont = nullptr;

//Buttons objects
Button* botao_x;
Button* botao_play;
Button* level_marker;
Button* botao_continuar;
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

        //Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            isRunning = false;
        }
    }

    gFont = TTF_OpenFont("assets/fonts/learners.ttf", 28);
    if (gFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        isRunning = false;
    }
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Texture* textTexture;
    textTexture = TextureManager::loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor);

    tela_principal  = new GameObject("assets/tela_principal.png", 0, 0);
    modo_historia   = new GameObject("assets/modo_historia.png", 0, 0);
    selecao_nivel   = new GameObject("assets/selecao_nivel.png", 0, 0);
    botao_x       = new Button("x", 740, 20);
    botao_play    = new Button("play", 740, 550);
    level_marker    = new Button("level_marker", 250, 500);
    nrainhas        = new N_Queens();
    parabens = new GameObject("assets/parabens.png", 210, 180);
    botao_continuar = new Button("play", 380, 345);
    overlay = new GameObject("assets/overlay.png", 0, 0);

}

void Game::handleMenuEvents(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN) {
        state = GAME_STORY;
    }
}

void Game::handleStoryEvents(SDL_Event* event) {
    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
    if (botao_play->handleEvent(event)) {
        state = GAME_LEVELS;
    }
}

void Game::handleNQueensEvents(SDL_Event* event) {
    if (botao_x->handleEvent(event)) {
        nrainhas->resetLevel();
        state = GAME_MENU;
    }
    if (nrainhas->getGameState())
    {
        if (botao_continuar->handleEvent(event)) {
            nrainhas->resetLevel();
            state = GAME_LEVELS;
        }
    }
    nrainhas->handleEvent(event);
}

void Game::handleLevelEvents(SDL_Event* event)
{
    if (level_marker->handleEvent(event))
    {
        state = GAME_QUEENS;
    }

    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
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
            handleLevelEvents(&event);
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
    switch (state) {
    case GAME_QUEENS:
        nrainhas->update();
    }
    
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
        level_marker->render();
        break;
    case GAME_QUEENS:
        nrainhas->render();        
        if (nrainhas->getGameState()) {
            //state = GAME_WIN;
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
    default:
        break;
    }
    SDL_RenderPresent(renderer);

}

void Game::clean()
{
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
