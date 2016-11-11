

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Entity.h"


class Bullet : public Entity
{
public:
	Bullet(const char* a_pTextureFileName, Vector2& a_v2Dimensions);
	Bullet(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	Bullet(const Bullet& a_copy);
	~Bullet();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__BULLET_H__