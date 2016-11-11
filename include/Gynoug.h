#ifndef __Gynoug_H_
#define __Gynoug_H_

#include "Application.h"
#include <glm/glm.hpp>

class ClickableButton;
class Entity;
class Player;
class Background;
class BallEnemy;
class BarrageEnemy;
class ChasingEnemy;
class EyeEnemy;
class FallingEnemy;
class PalmTreeEnemy;
class SharkEnemy;
class StarEnemy;
class StoneEnemy;
class VolcanoEnemy;
class VolcanoProjectile;
class PlayerBullet;

// Derived application class that wraps up all globals neatly
class Gynoug : public UG::Application
{
public:

	Gynoug();
	virtual ~Gynoug();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	bool TestCollision(Entity * a_pEntity1, Entity * a_pEntity2);
	void CollisionPlayer();
	void CollisionPlayerBullet(int a_pBallEnemyNum);
	void CollisionBallEnemy(int a_pBallEnemyNum);
	void CollisionBarrageEnemy(int a_pBarrageEnemyNum);
	void CollisionChasingEnemy(int a_pChasingEnemyNum);
	void CollisionEyeEnemy(int a_pEyeEnemyNum);
	void CollisionFallingEnemy(int a_pFallingEnemyNum);
	void CollisionPalmTreeEnemy(int a_pPalmTreeEnemyNum);
	void CollisionSharkEnemy(int a_pSharkEnemyNum);
	void CollisionStarEnemy(int a_pStarEnemyNum);
	void CollisionStoneEnemy(int a_pStoneEnemyNum);
	void CollisionVolcanoEnemy(int a_pVolcanoEnemyNum);
	void CollisionVolcanoProjectile(int a_pVolcanoProjectileNum);
	int Gynoug::MaxEnemy();

private:

	float splashTimer;
	int m_iScreenWidth;
	int m_iScreenHeight;
	long m_iScore;
	float m_iGameClock;
	float m_iGameoverClock;
	int m_iTrigger;
	int m_iCurrentPlayers;
	int m_iCurrentPlayerBullets;
	int m_iCurrentBallEnemies;
	int m_iCurrentBarrageEnemies;
	int m_iCurrentChasingEnemies;
	int m_iCurrentEyeEnemies;
	int m_iCurrentFallingEnemies;
	int m_iCurrentPalmTreeEnemies;
	int m_iCurrentSharkEnemies;
	int m_iCurrentStarEnemies;
	int m_iCurrentStoneEnemies;
	int m_iCurrentVolcanoEnemies;
	int m_iCurrentVolcanoProjectiles;

	enum Screens
	{
		Main, Game, Highscores, Splash, InputScore
	};
	
	Screens currentScreen;

	ClickableButton* m_pNewGameButton;
	ClickableButton* m_pHighscoresButton;
	ClickableButton* m_pQuitButton;
	ClickableButton* m_pBackButton;

	Player* m_pPlayer;
	Background* m_Background[2];
	Background* m_SplashScreen;

	PlayerBullet* m_PlayerBullets[9];

	BallEnemy* m_pBallEnemies[20];
	BarrageEnemy* m_pBarrageEnemies[30];
	ChasingEnemy* m_pChasingEnemies[20];
	EyeEnemy* m_pEyeEnemies[4];
	FallingEnemy* m_pFallingEnemies[10];
	PalmTreeEnemy* m_pPalmTreeEnemies[20];
	SharkEnemy* m_pSharkEnemies[2];
	StarEnemy* m_pStarEnemies[10];
	StoneEnemy* m_pStoneEnemies[10];
	VolcanoEnemy* m_pVolcanoEnemies[2];
	VolcanoProjectile* m_pVolcanoProjectiles[20];
};

#endif // __Gynoug_H_
