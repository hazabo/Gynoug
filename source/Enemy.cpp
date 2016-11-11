#include "Enemy.h"

Enemy::Enemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions) 
	: Entity( a_pTextureFileName, a_v2Dimensions.x, a_v2Dimensions.y)
{
	m_fHealth = 100.f;
}

Enemy::Enemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Entity(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{
	m_fHealth = 100.f;
}

Enemy::Enemy(const Enemy& a_copy) : Entity(a_copy)
{
	m_fHealth = a_copy.m_fHealth;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float a_fTimeStep)
{
	Entity::Update(a_fTimeStep);
}

void Enemy::Draw()
{
	Entity::Draw();
}

void Enemy::GetHealth (int& a_fHealth) const
{
	a_fHealth = m_fHealth;
}

void Enemy::SetHealth(int& a_fHealth)
{
	m_fHealth=a_fHealth;
}