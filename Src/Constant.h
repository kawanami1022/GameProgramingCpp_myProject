#pragma once

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int FPS = 60;
constexpr float MILLISECONDS_PER_FRAME = FPS / 1000.f;

namespace
{
    SDL_version compile_version;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    

    SDL_Event event;
}
