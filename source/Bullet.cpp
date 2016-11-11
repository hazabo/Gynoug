
#include "Bullet.h"

Bullet::Bullet(const char * a_pTextureFileName, Vector2 & a_v2Dimensions) 
	: Entity(a_pTextureFileName, a_v2Dimensions.x, a_v2Dimensions.y)
{

}

Bullet::Bullet(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Entity(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{
	
}

Bullet::Bullet(const Bullet& a_copy) : Entity(a_copy)
{
	
}

Bullet::~Bullet()
{

}

void Bullet::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
}

void Bullet::Draw()
{
	Entity::Draw();
}
