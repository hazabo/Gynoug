
#include "Stone Enemy.h"

StoneEnemy::StoneEnemy()
	:Enemy("./images/Stone Enemy.png", Vector2(80.f, 74.f))
{

}

StoneEnemy::StoneEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

StoneEnemy::StoneEnemy(const StoneEnemy& a_copy)
	: Enemy(a_copy)
{

}

StoneEnemy::~StoneEnemy()
{

}

void StoneEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
	//get position, width and velocity
	float a_Width;
	Vector2 a_Position;
	Vector2 a_Velocity;
	GetWidth(a_Width);
	GetPosition(a_Position);
	GetVelocity(a_Velocity);
	if (a_Position.y < a_Width)
	{
		a_Velocity.y *= -1.f;
		SetVelocity(a_Velocity);
	}
}

void StoneEnemy::Draw()
{
	Enemy::Draw();
}
