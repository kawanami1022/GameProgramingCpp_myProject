#include <SDL.h>
#include "../Constant.h"
#include "GameScene.h"
#include "../System/SceneManager.h"

GameScene::GameScene(SceneManager& sceneMng):BaseScene(sceneMng)
{
}

void GameScene::ProcessInput()
{
}

void GameScene::Update(const float& deltaTime)
{
}

void GameScene::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
