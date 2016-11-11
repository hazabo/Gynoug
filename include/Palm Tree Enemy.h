

#ifndef __PALM_TREE_ENEMY_H__
#define __PALM_TREE_ENEMY_H__

#include "Enemy.h"

class PalmTreeEnemy : public Enemy
{
public:
	PalmTreeEnemy();
	PalmTreeEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	PalmTreeEnemy(const PalmTreeEnemy& a_copy);
	~PalmTreeEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__PALM_TREE_ENEMY_H__
