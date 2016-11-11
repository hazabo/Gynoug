
#include "Palm Tree Enemy.h"

PalmTreeEnemy::PalmTreeEnemy()
	:Enemy("./images/Palm Tree Enemy.png", Vector2(158, 149))
{

}

PalmTreeEnemy::PalmTreeEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

PalmTreeEnemy::PalmTreeEnemy(const PalmTreeEnemy& a_copy)
	: Enemy(a_copy)
{

}

PalmTreeEnemy::~PalmTreeEnemy()
{

}

void PalmTreeEnemy::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void PalmTreeEnemy::Draw()
{
	Enemy::Draw();
}
