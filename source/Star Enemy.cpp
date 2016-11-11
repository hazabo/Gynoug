
#include "Star Enemy.h"

StarEnemy::StarEnemy(float a_OscillPoint)
	:Enemy("./images/Star Enemy.png", Vector2(147.f, 150.f))
{
	m_OscillPoint = a_OscillPoint;
}

StarEnemy::StarEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

StarEnemy::StarEnemy(const StarEnemy& a_copy)
	: Enemy(a_copy)
{
	m_OscillPoint=a_copy.m_OscillPoint;
}

StarEnemy::~StarEnemy()
{

}

void StarEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
	Vector2 a_Position;
	Vector2 a_Velocity;
	Vector2 a_Acceleration;
	GetPosition(a_Position);
	GetVelocity(a_Velocity);
	GetAcceleration(a_Acceleration);

	if ((a_Acceleration.y > 0.f) && (a_Position.y > m_OscillPoint))
	{
		SetAcceleration(Vector2(a_Acceleration.x, a_Acceleration.y*-1.f));
	}
	else if ((a_Acceleration.y < 0.f) && (a_Position.y < m_OscillPoint))
	{
		SetAcceleration(Vector2(a_Acceleration.x, a_Acceleration.y*-1.f));
	}
}

void StarEnemy::Draw()
{
	Enemy::Draw();
}

