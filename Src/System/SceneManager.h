#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include "../Scene/BaseScene.h"

class Application;

class SceneManager
{
private:
	friend class Application;
	friend class GameScene;
	friend class TitleScene;

	std::vector<std::unique_ptr<BaseScene>> scenes_;

	void ChangeScene(std::unique_ptr<BaseScene>);

	void ProcessInput(Application& application);
	void Update(const float& deltaTime, Application& application);
	void Render( Application& application);
public:
	SceneManager();
	~SceneManager() = default;
};

