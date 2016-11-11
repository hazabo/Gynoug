

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Application.h"

#define MAX_PLAYER_KEYS 4

class Player : public Entity
{
public:
	Player();
	Player(const Player& a_Player);

	virtual ~Player();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();
	bool BulletReady();

protected:
private:
	

	unsigned int m_fLives;
	unsigned int m_fHealth;
	unsigned int m_PlayerKeys[MAX_PLAYER_KEYS];
	float m_BulletTimer;

};

#endif //__PLAYER_H__