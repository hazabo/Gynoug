

#ifndef __FALLING_ENEMY_H__
#define __FALLING_ENEMY_H__

#include "Enemy.h"
#include "Player.h"

class FallingEnemy : public Enemy
{
public:
	FallingEnemy();
	FallingEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	FallingEnemy(const FallingEnemy& a_copy);
	~FallingEnemy();

	virtual void Update(float a_fDeltaTime,Player* a_fPlayer);
	virtual void Draw();
private:

};

#endif //__FALLING_ENEMY_H__
