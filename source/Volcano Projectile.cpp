
#include "Volcano Projectile.h"

VolcanoProjectile::VolcanoProjectile()
	:Enemy("./images/Volcano Projectile.png", Vector2(108.f, 108.f))
{

}

VolcanoProjectile::VolcanoProjectile(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

VolcanoProjectile::VolcanoProjectile(const VolcanoProjectile& a_copy)
	: Enemy(a_copy)
{

}

VolcanoProjectile::~VolcanoProjectile()
{

}

void VolcanoProjectile::Update(float a_fDeltaTime)
{
	Enemy::Update(a_fDeltaTime);
}

void VolcanoProjectile::Draw()
{
	Enemy::Draw();
}
