
#include "Falling Enemy.h"

FallingEnemy::FallingEnemy()
	:Enemy("./images/Falling Enemy.png", Vector2(108, 181))
{

}

FallingEnemy::FallingEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

FallingEnemy::FallingEnemy(const FallingEnemy& a_copy)
	: Enemy(a_copy)
{

}

FallingEnemy::~FallingEnemy()
{

}

void FallingEnemy::Update(float a_fDeltaTime,Player* a_fPlayer)
{
	Enemy::Update(a_fDeltaTime);
	//Get Positions and Dimensions
	Vector2 a_EnemyPosition;
	float a_EnemyWidth;
	GetPosition(a_EnemyPosition);
	GetWidth(a_EnemyWidth);
	Vector2 a_PlayerPosition;
	float a_PlayerWidth;
	a_fPlayer->GetPosition(a_PlayerPosition);
	a_fPlayer->GetWidth(a_PlayerWidth);
	   //(a_pv2Position1.x + a_pHalfWidth1 > a_pv2Position2.x - a_pHalfWidth2 && a_pv2Position1.x - a_pHalfWidth1 < a_pv2Position2.x + a_pHalfWidth2)
	if (((a_PlayerPosition.x + (a_PlayerWidth*0.5f)) > (a_EnemyPosition.x - (a_EnemyWidth*0.5f))) && (((a_PlayerPosition.x - (a_PlayerWidth*0.5f)) < (a_EnemyPosition.x + (a_EnemyWidth*0.5f)))))
	{
		Vector2 a_EnemyVelocity;
		GetVelocity(a_EnemyVelocity);
		a_EnemyVelocity = Vector2(a_EnemyVelocity.x, a_EnemyVelocity.x*1.7f);
		SetVelocity(a_EnemyVelocity);
	}
}

void FallingEnemy::Draw()
{
	Enemy::Draw();
}
