#include "game.h"

N_Queens* nrainhas;
Map_Coloring* colorindo_bh;
Hanoi_Tower* bolo_hanoi;

SDL_Renderer* Game::renderer    = nullptr;
TTF_Font*     Game::gFont       = nullptr;
SDL_Cursor*   Game::cursor      = nullptr;
SDL_Cursor*   Game::cursor_hand = nullptr;

Game::Game()  {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
            std::cout << "Window created" << std::endl;

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
    //textTexture = TextureManager::loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor);

    SDL_Surface* cursorSurface = IMG_Load("assets/cursors/seta.png");
    SDL_Surface* handSurface   = IMG_Load("assets/cursors/mao.png");

    if (!cursorSurface || !handSurface) {
        isRunning = false;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    cursor_hand = SDL_CreateColorCursor(handSurface, 0, 0);

    if (!cursor || !cursor_hand) {
        isRunning = false;
    }

    SDL_SetCursor(cursor);

    tela_principal  = new GameTexture("assets/tela_principal.png", 0, 0, false, false);
    modo_historia   = new GameTexture("assets/modo_historia.png", 0, 0, false, false);
    selecao_nivel   = new GameTexture("assets/selecao_nivel.png", 0, 0, false, false);
    botao_x         = new GameTexture("assets/buttons/x", 740, 20, true, false);
    botao_play      = new GameTexture("assets/buttons/play", 740, 550, true, false);
    level_marker    = new GameTexture("assets/buttons/level_marker", 250, 500, true, false);

    nrainhas        = new N_Queens();
    colorindo_bh    = new Map_Coloring();
    bolo_hanoi      = new Hanoi_Tower();

    parabens        = new GameTexture("assets/parabens.png", 210, 180, false, false);
    botao_continuar = new GameTexture("assets/buttons/play", 380, 345, true, false);
    overlay         = new GameTexture("assets/overlay.png", 0, 0, false, false);

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
    if (nrainhas->gameWon())
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
        state = GAME_HANOI;//GAME_MAP_COLORING; //GAME_QUEENS; - Para debugar map coloring primeiro
    }

    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
}

void Game::handleMapColoringEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }

    colorindo_bh->handleEvent(event);
}

void Game::handleHanoiEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
    bolo_hanoi->handleEvent(event);
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

        case GAME_MAP_COLORING:
            handleMapColoringEvents(&event);
            break;

        case GAME_HANOI:
            handleHanoiEvents(&event);
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
        break;
    case GAME_HANOI:
        bolo_hanoi->update();
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
        botao_play   ->render();
        botao_x      ->render();
        break;

    case GAME_LEVELS:
        selecao_nivel->render();
        botao_x      ->render();
        level_marker ->render();
        break;

    case GAME_QUEENS:
        nrainhas->render();        
        if (nrainhas->gameWon()) {
            overlay ->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_MAP_COLORING:
        colorindo_bh->render();
        botao_x     ->render();
        break;

    case GAME_HANOI:
        bolo_hanoi->render();
        botao_x->render();
        break;

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
    SDL_FreeCursor(cursor);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
