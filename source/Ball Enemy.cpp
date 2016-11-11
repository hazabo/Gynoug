
#include "Ball Enemy.h"
#include <iostream>
BallEnemy::BallEnemy() 
	:Enemy("./images/Ball Enemy.png", Vector2(68,69))
{
	
}

BallEnemy::BallEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	:Enemy( a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{
	
}

BallEnemy::BallEnemy(const BallEnemy& a_copy) 
	: Enemy(a_copy)
{
	
}

BallEnemy::~BallEnemy()
{

}

void BallEnemy:: Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
	Vector2 a_Position;
	Vector2 a_Velocity;
	Vector2 a_Acceleration;
	int ScreenHeight = 850;
	GetPosition(a_Position);
	GetVelocity(a_Velocity);
	GetAcceleration(a_Acceleration);
	//if the enemy has acceleration
	if ((a_Acceleration.y > 0.f) && (a_Position.y > ScreenHeight*0.5f))
	{
		SetAcceleration(Vector2(a_Acceleration.x, a_Acceleration.y*-1.f));
	}
	else if((a_Acceleration.y < 0.f) && (a_Position.y < ScreenHeight*0.5f))
	{
		SetAcceleration(Vector2(a_Acceleration.x, a_Acceleration.y*-1.f));
	}
	

}

void BallEnemy:: Draw()
{
	Enemy::Draw();
}