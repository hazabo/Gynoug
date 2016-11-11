

#ifndef __BALL_ENEMY_H__
#define __BALL_ENEMY_H__

#include "Enemy.h"

class BallEnemy : public Enemy
{
public:
	BallEnemy();
	BallEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	BallEnemy(const BallEnemy& a_copy);
	~BallEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__BALL_ENEMY_H__
