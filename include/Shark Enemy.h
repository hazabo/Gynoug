

#ifndef __SHARK_ENEMY_H__
#define __SHARK_ENEMY_H__

#include "Enemy.h"

class SharkEnemy : public Enemy
{
public:
	SharkEnemy();
	SharkEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	SharkEnemy(const SharkEnemy& a_copy);
	~SharkEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__SHARK_ENEMY_H__
