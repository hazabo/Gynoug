

#ifndef __STONE_ENEMY_H__
#define __STONE_ENEMY_H__

#include "Enemy.h"

class StoneEnemy : public Enemy
{
public:
	StoneEnemy();
	StoneEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	StoneEnemy(const StoneEnemy& a_copy);
	~StoneEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__STONE_ENEMY_H__
