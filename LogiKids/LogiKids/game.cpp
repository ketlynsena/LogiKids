#include "game.h"

N_Queens* nrainhas;
Map_Coloring* colorindo_bh;
Hanoi_Tower* bolo_hanoi;
Knapsack* mochila;
BalanceScale* balanca;
TravelingSalesman* mineiro_viajante;

Timer*        Game::timer = nullptr;
SDL_Renderer* Game::renderer    = nullptr;
TTF_Font*     Game::consolas    = nullptr;
SDL_Cursor*   Game::cursor      = nullptr;
SDL_Cursor*   Game::cursor_hand = nullptr;
TextTexture*  Game::pontuacao   = nullptr;
TextTexture*  Game::tempo       = nullptr;
GameTexture*  Game::cerebro     = nullptr;
GameTexture*  Game::ampulheta   = nullptr;

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
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);// | SDL_WINDOW_BORDERLESS);

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
    consolas = TTF_OpenFont("assets/fonts/consola.ttf", 35);
    if (consolas == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        isRunning = false;
    }

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

    SDL_Surface* icon = IMG_Load("assets/puzzle_icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    tela_principal  = new GameTexture("assets/tela_principal.png", 0, 0, false, false);
    modo_historia   = new GameTexture("assets/modo_historia.png", 0, 0, false, false);
    selecao_nivel   = new GameTexture("assets/selecao_nivel.png", 0, 0, false, false);
    botao_x         = new GameTexture("assets/buttons/x", 740, 20, true, false);
    botao_play      = new GameTexture("assets/buttons/play", 740, 550, true, false);

    level_marker[0] = new GameTexture("assets/buttons/level_marker_yellow", 249, 509, true, false);
    level_marker[1] = new GameTexture("assets/buttons/level_marker_pink", 373, 504, true, false);
    level_marker[2] = new GameTexture("assets/buttons/level_marker_blue", 368, 425, true, false);
    level_marker[3] = new GameTexture("assets/buttons/level_marker_green", 488, 447, true, false);
    level_marker[4] = new GameTexture("assets/buttons/level_marker_orange", 614, 472, true, false);
    level_marker[5] = new GameTexture("assets/buttons/level_marker_sky_blue", 687, 401, true, false);

    nrainhas         = new N_Queens();
    colorindo_bh     = new Map_Coloring();
    bolo_hanoi       = new Hanoi_Tower();
    mochila          = new Knapsack();
    balanca          = new BalanceScale();
    mineiro_viajante = new TravelingSalesman();
    timer            = new Timer();

    parabens        = new GameTexture("assets/parabens_garota.png", 204, 134, false, false);
    botao_continuar = new GameTexture("assets/buttons/play", 381, 468, true, false);
    overlay         = new GameTexture("assets/overlay.png", 0, 0, false, false);
    cerebro         = new GameTexture("assets/brain.png", 647, 28, false, false);
    ampulheta       = new GameTexture("assets/ampulheta.png", 514, 25, false, false);

    pontuacao = new TextTexture("0", branco, consolas, 40, 696, 28);
    tempo = new TextTexture("0:0", branco, consolas, 40, 546, 28);

    //timer->start();

}

void Game::handleMenuEvents(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN) {
        state = GAME_LEVELS;//STORY;
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
        state = GAME_LEVELS;
    }
    if (nrainhas->gameWon())
    {
        if (timer->isStarted())
            timer->stop();

        if (botao_continuar->handleEvent(event)) {
            nrainhas->resetLevel();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }
    nrainhas->handleEvent(event);
}

void Game::handleLevelEvents(SDL_Event* event)
{
    if (level_marker[0]->handleEvent(event))
    {
        state = GAME_QUEENS;
        timer->start();
    }

    if (level_marker[1]->handleEvent(event))
    {
        state = GAME_MAP_COLORING;
        timer->start();
    }

    if (level_marker[2]->handleEvent(event))
    {
        state = GAME_HANOI;
        timer->start();
    }

    if (level_marker[3]->handleEvent(event))
    {
        state = GAME_KNAPSACK;
        timer->start();
    }

    if (level_marker[4]->handleEvent(event))
    {
        state = GAME_SCALE;
        timer->start();
    }

    if (level_marker[5]->handleEvent(event))
    {
        state = GAME_TSP;
        timer->start();
    }

    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
}

void Game::handleMapColoringEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        colorindo_bh->resetMap();
        state = GAME_LEVELS;
    }

    if (colorindo_bh->gameWon())
    {
        if (timer->isStarted())
            timer->stop();

        if (botao_continuar->handleEvent(event)) {
            colorindo_bh->resetMap();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }

    colorindo_bh->handleEvent(event);
}

void Game::handleHanoiEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        bolo_hanoi->resetLevel();
        state = GAME_LEVELS;
    }

    if (bolo_hanoi->gameWon())
    {
        if (timer->isStarted())
            timer->stop();

        if (botao_continuar->handleEvent(event)) {
            bolo_hanoi->resetLevel();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }
    else {
        bolo_hanoi->handleEvent(event);
    }
}

void Game::handleKnapsackEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        mochila->resetLevel();
        state = GAME_LEVELS;
    }
    if (mochila->gameWon())
    {
        if (timer->isStarted())
            timer->stop();
        if (botao_continuar->handleEvent(event)) {
            mochila->resetLevel();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }
    else {
        mochila->handleEvent(event);
    }
    
}

void Game::handleScaleEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        balanca->resetLevel();
        state = GAME_LEVELS;
    }

    if (balanca->gameWon())
    {
        if (timer->isStarted())
            timer->stop();
        if (botao_continuar->handleEvent(event)) {
            balanca->resetLevel();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }
    else {
        balanca->handleEvent(event);
    }
}

void Game::handleTSPEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        mineiro_viajante->resetLevel();
        state = GAME_LEVELS;
    }
    if (mineiro_viajante->gameWon())
    {
        if (timer->isStarted())
            timer->stop();
        if (botao_continuar->handleEvent(event)) {
            mineiro_viajante->resetLevel();
            pontos += 1;
            pontuacao->loadText(std::to_string(pontos), branco, consolas, 40);
            state = GAME_LEVELS;
        }
    }
    else {
        mineiro_viajante->handleEvent(event);
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
            if (timer->isStarted())
                timer->pause();
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

        case GAME_KNAPSACK:
            handleKnapsackEvents(&event);
            break;

        case GAME_SCALE:
            handleScaleEvents(&event);
            break;
        case GAME_TSP:
            handleTSPEvents(&event);
        default:
            break;
        }
    }
}

void Game::update()
{
    if (timer->isStarted())
    {
        timeText = timer->toMinutesAndSeconds(timer->getTicks());
        tempo->loadText(timeText, branco, consolas, 40);
    }    

    switch (state) {
    case GAME_QUEENS:
        nrainhas->update();
        break;
    case GAME_HANOI:
        bolo_hanoi->update();
        break;
    case GAME_KNAPSACK:
        mochila->update();
        break;
    case GAME_SCALE:
        balanca->update();
        break;
    case GAME_TSP:
        mineiro_viajante->update();
        break;
    default:
        break;
    }  
}

void Game::renderGameScore() {    
    pontuacao->render();
    cerebro->render();
    tempo->render();
    ampulheta->render();
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
        for (int i = 0; i < N_LEVELS; i++)
        {
            if(level_marker[i])
                level_marker[i]->render();
        }
        pontuacao->render();
        cerebro->render();
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
        if (colorindo_bh->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_HANOI:
        bolo_hanoi->render();
        if (bolo_hanoi->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_KNAPSACK:
        mochila->render();
        if (mochila->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_SCALE:
        balanca->render();
        if (balanca->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;
    case GAME_TSP:
        mineiro_viajante->render();
        if (mineiro_viajante->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    default:
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    TTF_CloseFont(consolas);
    consolas = NULL;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeCursor(cursor);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
