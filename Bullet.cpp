#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet(Game* game)
	:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Projecttile.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(400.f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(5.f);

	mLiveTime = 1.f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// Check for collision vs enemies
	for (Enemy* e : GetGame()->GetEnemies())
	{
		if (Intersect(*mCircle, *(e->GetCircle())))
		{
			// we both die on collision
			e->SetState(EDead);
			SetState(EDead);
			break;
		}
	}

	mLiveTime -= deltaTime;
	if (mLiveTime <= 0.f)
	{
		// time limit hit, die
		SetState(EDead);
	}
}