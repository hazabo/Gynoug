

#ifndef __STAR_ENEMY_H__
#define __STAR_ENEMY_H__

#include "Enemy.h"

class StarEnemy : public Enemy
{
public:
	//OscillPoint is the point the enemy will oscilate vertically around
	StarEnemy(float a_OscillPoint);
	StarEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	StarEnemy(const StarEnemy& a_copy);
	~StarEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:
	float m_OscillPoint;
};

#endif //__STAR_ENEMY_H__
