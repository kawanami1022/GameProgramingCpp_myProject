#pragma once
#include <memory>
#include <SDL.h>
class SceneManager;

class Application
{
	friend class SceneManager;
private:
	Application() = default;
	~Application() = default;
	std::unique_ptr<SceneManager> sceneMng_;


	SDL_Renderer* gRenderer = NULL;
	int tickLastFrame = 0;
	bool quit_ = false;
public:
	static Application& Instance();
	bool Initialize();
	void Run();
	void Close();
};

