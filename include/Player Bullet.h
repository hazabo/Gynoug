
#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "Bullet.h"


class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
private:

};

#endif //__PBullet_H__