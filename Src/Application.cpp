#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Lib/Constraint/cast.h"
#include "Application.h"

#include "Constant.h"
#include "System/SceneManager.h"


Application& Application::Instance()
{
    static Application app;
    return app;
}

bool Application::Initialize()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        printf("SDL_ttf could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if (!gRenderer)
    {
        printf("Error creating renderer! SDL_Error: %s\n", SDL_GetError());
    }

    // init ttf
    SDL_TTF_VERSION(&compile_version)

    std::cout << "compiled with SDL_ttf version: " <<
        compile_version.major << "." <<
        compile_version.minor << "." <<
        compile_version.patch << std::endl;
    // Set the background color
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

    sceneMng_ = std::make_unique<SceneManager>();

    return true;
}

void Application::Run()
{
    while (!quit_)
    {
        // Sleep the execution until we reach the target time in millisecond
        float timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - tickLastFrame);

        // Only call delay when we are too fast to process this frame
        // When SDL_Delay is call it's free process to do other task and come back in the mean time
        if (timeToWait > 0 && timeToWait < MILLISECONDS_PER_FRAME)
            SDL_Delay(static_cast<Uint32>(timeToWait));
        
        // dealtaTime : time between current and last frame converted to second
        float deltaTime = (SDL_GetTicks() - tickLastFrame) / 1000.0f;

        // Save current time before moving to next frame
        tickLastFrame = SDL_GetTicks();

        if (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit_ = true;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        sceneMng_->ProcessInput((*this));
        sceneMng_->Update(deltaTime, (*this));
        sceneMng_->Render((*this));


    }
}

void Application::Close()
{
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
    TTF_Quit();
}
