#include "SceneManager.h"
#include "../Application.h"
#include "../Scene/TitleScene.h"

SceneManager::SceneManager()
{
	scenes_.emplace_back(std::make_unique<TitleScene>(*this));
}

void SceneManager::ChangeScene(std::unique_ptr<BaseScene> scene)
{
	auto& playingScene = *scenes_.begin();
	playingScene = std::move(scene);
}

void SceneManager::ProcessInput(Application& application)
{
	for (const auto& scene : scenes_)
		scene->ProcessInput();
}

void SceneManager::Update(const float& deltaTime, Application& application)
{
	for (const auto& scene : scenes_)
		scene->Update(deltaTime);
}

void SceneManager::Render(Application& application)
{
	for (const auto& scene : scenes_)
		scene->Render(application.gRenderer);
}
