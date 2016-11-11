
#include "Barrage Enemy.h"
#include "Player.h"

BarrageEnemy::BarrageEnemy(Player* a_Player)
	:Enemy("./images/Chasing Enemy.png", Vector2(71, 67))
{
	//Get Positions
	Vector2 EnemyPosition;
	Vector2 PlayerPosition;

	GetPosition(EnemyPosition);
	a_Player->GetPosition(PlayerPosition);
	//Set Speed to 0.66*the distance between the Barrage enemy and the player
	SetVelocity(Vector2((PlayerPosition.x - EnemyPosition.x)*0.66f, (PlayerPosition.y - EnemyPosition.y)));
}

BarrageEnemy::BarrageEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	:Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

BarrageEnemy::BarrageEnemy(const BarrageEnemy& a_copy)
	: Enemy(a_copy)
{

}

BarrageEnemy::~BarrageEnemy()
{

}

void BarrageEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void BarrageEnemy::Draw()
{
	Enemy::Draw();
}