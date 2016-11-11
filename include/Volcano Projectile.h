

#ifndef __VOLCANO_PROJECTILE_H__
#define __VOLCANO_PROJECTILE_H__

#include "Enemy.h"

class VolcanoProjectile : public Enemy
{
public:
	VolcanoProjectile();
	VolcanoProjectile(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	VolcanoProjectile(const VolcanoProjectile& a_copy);
	~VolcanoProjectile();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__VOLCANO_PROJECTILE_H__
