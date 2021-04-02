#include "Asteroid.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Random.h"
#include "Game.h"

Asteroid::Asteroid(Game* game):Actor(game)
{
	// ランダムな位置/向きで初期化する
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));

	// スプライトコンポーネントを作成し、テクスチャを設定する
	SpriteComponent* sc = new SpriteComponent(this);

	// Create a move component,and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	// Create a circle component(for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.f);

	// Add to mAsteroid
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

CircleComponent* Asteroid::GetCircle()
{
	return mCircle;
}
