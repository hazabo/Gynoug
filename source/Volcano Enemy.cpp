
#include "Volcano Enemy.h"

VolcanoEnemy::VolcanoEnemy()
	:Enemy("./images/Volcano Enemy.png", Vector2(322.f, 163.f))
{

}

VolcanoEnemy::VolcanoEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

VolcanoEnemy::VolcanoEnemy(const VolcanoEnemy& a_copy)
	: Enemy(a_copy)
{

}

VolcanoEnemy::~VolcanoEnemy()
{

}

void VolcanoEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void VolcanoEnemy::Draw()
{
	Enemy::Draw();
}
