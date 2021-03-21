#pragma once
#include "BaseScene.h"
class GameScene :
    public BaseScene
{
public:
    GameScene(SceneManager&);
    ~GameScene() = default;
    void ProcessInput() override;
    void Update(const float& deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
};

