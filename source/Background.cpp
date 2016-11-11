
#include "Background.h"

Background::Background(const char * a_pTextureFileName, Vector2 & a_v2Dimensions) : Entity(a_pTextureFileName, a_v2Dimensions.x, a_v2Dimensions.y)
{

}

Background::~Background()
{

}

void Background::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	Vector2 a_fPosition;
	GetPosition(a_fPosition);
	if (a_fPosition.x <= (-770.f))
		SetPosition(Vector2(a_fPosition.x + 3080.f, a_fPosition.y));
}

void Background::Draw()
{
	Entity::Draw();
}