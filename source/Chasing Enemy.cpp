
#include "Chasing Enemy.h"

ChasingEnemy::ChasingEnemy()
	:Enemy("./images/Chasing Enemy.png", Vector2(71, 67))
{

}

ChasingEnemy::ChasingEnemy(const char* a_pTextureFileName, Vector2& a_v2Dimensions, const float* a_fv4UVCoords)
	: Enemy(a_pTextureFileName, a_v2Dimensions, a_fv4UVCoords)
{

}

ChasingEnemy::ChasingEnemy(const ChasingEnemy& a_copy)
	: Enemy(a_copy)
{

}

ChasingEnemy::~ChasingEnemy()
{

}

void ChasingEnemy::Update(float a_fDeltaTime, Player*a_pPlayer)
{
	Enemy::Update(a_fDeltaTime);
	//Get dimensions and Positions
	Vector2 EnemyPosition;
	float EnemyHeight;
	float EnemyWidth;
	Vector2 PlayerPosition;
	float PlayerHeight;
	float PlayerWidth;

	GetPosition(EnemyPosition);
	GetWidth(EnemyWidth);
	GetHeight(EnemyHeight);
	a_pPlayer->GetPosition(PlayerPosition);
	a_pPlayer->GetWidth(PlayerWidth);
	a_pPlayer->GetHeight(PlayerHeight);

	//Enemy velocity is set as a proportion of the distance between the closest edge of its bound to the player and the players closest bounds
	Vector2 EnemyVelocity;
	//if the enemy is to the left of the player use playerpos+Width - (Enemypos-Width)
	if (PlayerPosition.x > EnemyPosition.x)
	{
		EnemyVelocity.x = (PlayerPosition.x + PlayerWidth - EnemyPosition.x + EnemyWidth)*0.33f;
	}
	//if its to the right use playerpos-width-(Enemypos+width)
	else
	{
		EnemyVelocity.x = (PlayerPosition.x - PlayerWidth - EnemyPosition.x - EnemyWidth)*0.33f;
	}
	//if the ememy is below the player use Playerpos+height-(Enemypos-height)
	if (PlayerPosition.y >EnemyPosition.y)
	{
		EnemyVelocity.y = (PlayerPosition.y + PlayerHeight - EnemyPosition.y + EnemyHeight)*0.33f;
	}
	//if its above the player use Playerpos-height-(Enemypos+height)
	else
	{
		EnemyVelocity.y = (PlayerPosition.y - PlayerHeight - EnemyPosition.y - EnemyHeight)*0.33f;
	}
	//if the speed of the enemy is less than root 4 (using pythagoras)
	//4 is the square of the speed in the pythagorian triangle where x and y velocities represent axis
	while (((EnemyVelocity.x*EnemyVelocity.x) + (EnemyVelocity.y*EnemyVelocity.y)) < 4)
		//then increase the velocities proportionately slowly until the speed is greater that the root of 4 using pythagoras
	{
		EnemyVelocity.x *= 1.01f;
		EnemyVelocity.y *= 1.01f;
	}
		
		


	SetVelocity(EnemyVelocity);
}

void ChasingEnemy::Draw()
{
	Enemy::Draw();
}