

#ifndef __EYE_ENEMY_H__
#define __EYE_ENEMY_H__

#include "Enemy.h"

class EyeEnemy : public Enemy
{
public:
	EyeEnemy();
	EyeEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	EyeEnemy(const EyeEnemy& a_copy);
	~EyeEnemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__EYE_ENEMY_H__
