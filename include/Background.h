

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Entity.h"


class Background : public Entity
{
public:
	Background(const char* a_pTextureFileName, Vector2& a_v2Dimensions);
	~Background();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__Bullet_H__