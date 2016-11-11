

#ifndef __BARRAGE_ENEMY_H__
#define __BARRAGE_ENEMY_H__

#include "Enemy.h"
#include "Player.h"

class BarrageEnemy : public Enemy
{
public:
	BarrageEnemy(Player* a_Player);
	BarrageEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	BarrageEnemy(const BarrageEnemy& a_copy);
	~BarrageEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__BARRAGE_ENEMY_H__
