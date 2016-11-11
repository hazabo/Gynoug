
#include "Shark Enemy.h"

SharkEnemy::SharkEnemy()
	:Enemy("./images/Shark Enemy.png", Vector2(234, 182))
{

}

SharkEnemy::SharkEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

SharkEnemy::SharkEnemy(const SharkEnemy& a_copy)
	: Enemy(a_copy)
{

}

SharkEnemy::~SharkEnemy()
{

}

void SharkEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void SharkEnemy::Draw()
{
	Enemy::Draw();
}
