

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

class Enemy : public Entity
{
public:
	//No Default Enemy() Constructor
	Enemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions);
	Enemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords);
	Enemy(const Enemy& a_copy);
	virtual ~Enemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();

	void GetHealth(int& a_fHealth)const;
	void SetHealth(int& a_fHealth);

protected:

private:
	unsigned int m_fHealth;
};

#endif //__ENEMY_H__