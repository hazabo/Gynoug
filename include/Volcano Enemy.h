

#ifndef __VOLCANO_ENEMY_H__
#define __VOLCANO_ENEMY_H__

#include "Enemy.h"

class VolcanoEnemy : public Enemy
{
public:
	VolcanoEnemy();
	VolcanoEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	VolcanoEnemy(const VolcanoEnemy& a_copy);
	~VolcanoEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__VOLCANO_ENEMY_H__
