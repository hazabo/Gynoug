
#include "Eye Enemy.h"

EyeEnemy::EyeEnemy()
	:Enemy("./images/Eye Enemy.png", Vector2(112, 74))
{

}

EyeEnemy::EyeEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

EyeEnemy::EyeEnemy(const EyeEnemy& a_copy)
	: Enemy(a_copy)
{

}

EyeEnemy::~EyeEnemy()
{

}

void EyeEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void EyeEnemy::Draw()
{
	Enemy::Draw();
}
