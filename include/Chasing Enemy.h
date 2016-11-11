

#ifndef __CHASING_ENEMY_H__
#define __CHASING_ENEMY_H__

#include "Enemy.h"
#include "Player.h"

class ChasingEnemy : public Enemy
{
public:
	ChasingEnemy();
	ChasingEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	ChasingEnemy(const ChasingEnemy& a_copy);
	~ChasingEnemy();

	virtual void Update(float a_fDeltaTime, Player*a_pPlayer);
	virtual void Draw();
private:

};

#endif //__CHASING_ENEMY_H__
