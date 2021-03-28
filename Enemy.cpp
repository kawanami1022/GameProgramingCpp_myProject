#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy(Game* game)
	:Actor(game)
{
	// Add to enemy vector
	game->GetEnemies().emplace_back(this);

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));

	// Set position at start tile
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	// Setup a nav component at the start tile
	NavComponent* nc = new NavComponent(this);
	nc->SetForwardSpeed(150.f);
	// Setup a circle for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.f);
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// Am I near the end tile?
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.f))
	{
		SetState(EDead);
	}
}