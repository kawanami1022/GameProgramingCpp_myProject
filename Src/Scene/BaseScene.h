#pragma once
#include <SDL.h>
class SceneManager;

class BaseScene
{
protected:
	SceneManager* sceneMng_ = nullptr;
public:
	BaseScene(SceneManager&);
	virtual ~BaseScene() = default;
	virtual void ProcessInput() = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
};

