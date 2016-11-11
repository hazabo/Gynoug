
#include "Player Bullet.h"

PlayerBullet::PlayerBullet()
	:Bullet("./images/Player Bullet.png",Vector2(41,35))
{

}
PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Update(float a_fDeltaTime)
{
	Bullet::Update(a_fDeltaTime);
}
void PlayerBullet::Draw()
{
	Bullet::Draw();
}