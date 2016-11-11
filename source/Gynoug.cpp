#include "Application.h"
#include "Gynoug.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <string.h>
#include <fstream>

#include "ClickableButton.h"
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "Player Bullet.h"
#include "Enemy.h"
#include "Ball Enemy.h"
#include "Barrage Enemy.h"
#include "Chasing Enemy.h"
#include "Eye Enemy.h"
#include "Falling Enemy.h"
#include "Palm Tree Enemy.h"
#include "Shark Enemy.h"
#include "Star Enemy.h"
#include "Stone Enemy.h"
#include "Volcano Enemy.h"
#include "Volcano Projectile.h"

//This is an example of a complex #define that obfuscates the entry point of the application
//APPLICATION_ENTRY can be found in Application.h it is a define that hides the main() entry point
//of the application. This is done so that each application can be called and run in the same manner
//it is not something that needs to be fully understood until much later in the CGP course.

 APPLICATION_ENTRY(Gynoug);

//A default constructor for Gynoug() and it's accompanying destructor ~FrameworkTest()
//Any initialisation could be placed in here, these are empty for now. They are here to ensure that
//the correct application creation sequence is called.
Gynoug::Gynoug(){}
Gynoug::~Gynoug(){}

//onCreate is a function that is called once on the creation of the application. This is where items 
//that will last for the duration of the application should be created. EG Player sprites
bool Gynoug::onCreate(int a_argc, char* a_argv[])
{
	currentScreen = Screens::Splash;


	Application::GetScreenSize(m_iScreenWidth, m_iScreenHeight);
	Application::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
	Application::AddFont("./fonts/invaders.fnt");

	splashTimer = 0;
	m_iScore = 0;
	m_iGameClock = 0.f;
	m_iTrigger = 0;
	m_iCurrentPlayers = 1;
	m_iCurrentPlayerBullets = 0;
	m_iCurrentBallEnemies = 0;
	m_iCurrentBarrageEnemies = 0;
	m_iCurrentChasingEnemies = 0;
	m_iCurrentEyeEnemies = 0;
	m_iCurrentFallingEnemies = 0;
	m_iCurrentPalmTreeEnemies = 0;
	m_iCurrentSharkEnemies = 0;
	m_iCurrentStarEnemies = 0;
	m_iCurrentStoneEnemies = 0;
	m_iCurrentVolcanoEnemies = 0;
	m_iCurrentVolcanoProjectiles = 0;

	//create buttons for main
	m_pNewGameButton = new ClickableButton("Start Game", m_iScreenWidth*0.5f, m_iScreenHeight*0.7f, m_iScreenWidth*0.15f, m_iScreenHeight*0.1f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
	m_pHighscoresButton = new ClickableButton("Highscores", m_iScreenWidth*0.5f, m_iScreenHeight*0.5f, m_iScreenWidth*0.15f, m_iScreenHeight*0.1f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
	m_pQuitButton = new ClickableButton("Quit", m_iScreenWidth*0.5f, m_iScreenHeight*0.3f, m_iScreenWidth*0.15f, m_iScreenHeight*0.1f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
	
	//create button for highscores
	m_pBackButton = new ClickableButton("Back", m_iScreenWidth*0.5f, m_iScreenHeight*0.13f, m_iScreenWidth*0.15f, m_iScreenHeight*0.1f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));

	m_SplashScreen = new Background("./images/Splash Screen.png", Vector2(m_iScreenWidth, m_iScreenHeight));
	m_SplashScreen->SetPosition(Vector2((m_iScreenWidth*0.5f), m_iScreenHeight*0.5f));



	return true;
}

//onUpdate - this function is called each frame of the application, the a_deltaTime variable is a floating point value
//that gives the length of time that has passed since the previous frame was rendered.
void Gynoug::onUpdate(float a_deltaTime)
{
	if (currentScreen == Screens::Splash)
	{
		if (splashTimer <= 5.f)
		{
			splashTimer+=a_deltaTime;
		}
		else
		{
			currentScreen = Screens::Main;
		}
	}

	if (currentScreen == Screens::Main)
	{
		double a_MouseX;
		double a_MouseY;
		GetMousePos(a_MouseX, a_MouseY);
	 	if (GetMouseButtonDown(0))
		{
			if (m_pNewGameButton->Update(a_MouseX, m_iScreenHeight - a_MouseY))
			{
				currentScreen = Screens::Game;
				//reset
				Gynoug::onDestroy();
				m_pPlayer = new Player();
				m_pPlayer->SetPosition(Vector2(m_iScreenWidth * 0.1f, m_iScreenHeight * 0.5f));
				for (int i = 0; i <= 1; i++)
				{
					m_Background[i] = new Background("./images/Background.png", Vector2(m_iScreenWidth + 10.f, m_iScreenHeight));
					m_Background[i]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				}
				m_Background[0]->SetPosition(Vector2((m_iScreenWidth*0.5f), m_iScreenHeight*0.5f));
				m_Background[1]->SetPosition(Vector2((m_iScreenWidth*1.5f), m_iScreenHeight*0.5f));
				m_iGameClock = 0.f;
				m_iTrigger = 0;
				m_iCurrentPlayers = 1;
			}
				
			if (m_pHighscoresButton->Update(a_MouseX, m_iScreenHeight - a_MouseY))
				currentScreen = Screens::Highscores;
			if (m_pQuitButton->Update(a_MouseX, m_iScreenHeight - a_MouseY))
				destroy();
		}
	}

	if (currentScreen == Screens::Highscores)
	{
		double a_MouseX;
		double a_MouseY;
		GetMousePos(a_MouseX, a_MouseY);
		if (GetMouseButtonDown(0))
		{
			if (m_pBackButton->Update(a_MouseX, m_iScreenHeight - a_MouseY))
				currentScreen = Screens::Main;
		}
	}

	if (currentScreen == Screens::InputScore)
	{
		//set up file and things to read to
		std::fstream ScoresFile("./Scores.txt");
		std::string ScoresString[10]{ " "," "," "," "," "," "," "," "," "," " };
		int Scores[10]{ 0,0,0,0,0,0,0,0,0,0 };
		//read from file to sting array then convert to int array

		for (int i = 0; !ScoresFile.eof() && i <= 9; i++)
		{
			std::getline(ScoresFile, ScoresString[i]);

				Scores[i] = std::stoi(ScoresString[i]);

		}
		ScoresFile.close();
		//if the players score is greater than the smallest highscore
		if (m_iScore > Scores[9])
		{
			Scores[9] = m_iScore;
			int Pos = 9;
			bool PosFound = false;
			//1 pass of insertion sort
			while (PosFound == false)
			{
				if (Scores[Pos] > Scores[Pos - 1])
				{
					int temp = Scores[Pos];
					Scores[Pos] = Scores[Pos - 1];
					Scores[Pos - 1] = temp;
					Pos--;
				}
				else
				{
					PosFound = true;
				}
			}
		}
		ScoresFile.open("./Scores.txt");
		if (ScoresFile.is_open())
			for (int i = 0; i < 10; i++)
			{
				ScoresFile << std::to_string(Scores[i]) << "\n";
			}
		else
			std::cout << "Not open";
		currentScreen = Screens::Highscores;
		ScoresFile.close();
		m_iScore = 0;
	}

	if (currentScreen == Screens::Game)
	{
		

#pragma region Enemy Spawning
		for (int i = 0; i <= 3; i++)
			if ((m_iTrigger == i) && (m_iGameClock > (2.7f + (i*0.3f))))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 2;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.75f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		for (int i = 4; i <= 7; i++)
			if ((m_iTrigger == i) && (m_iGameClock > (4.5f + ((i - 4)*0.3f))))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 2;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.25f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		for (int i = 8; i <= 12; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 6.f + ((i - 8)*0.3f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 1;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.75f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-2.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		for (int i = 13; i <= 17; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 8.7f + ((i - 13)*0.3f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 2;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.75f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;

				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.25f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		for (int i = 18; i <= 19; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 10.8f + ((i - 18)*0.8f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 6;
				m_pStarEnemies[m_iCurrentStarEnemies] = new StarEnemy(m_iScreenHeight*0.7f);
				m_pStarEnemies[m_iCurrentStarEnemies]->GetWidth(a_Width);
				m_pStarEnemies[m_iCurrentStarEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.75f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-0.25f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetHealth(Health);
				m_iCurrentStarEnemies++;
			}

		for (int i = 20; i <= 22; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 15.6f + ((i - 20)*0.6f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 6;
				m_pStarEnemies[m_iCurrentStarEnemies] = new StarEnemy(m_iScreenHeight*0.7f);
				m_pStarEnemies[m_iCurrentStarEnemies]->GetWidth(a_Width);
				m_pStarEnemies[m_iCurrentStarEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.75f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-0.25f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetHealth(Health);
				m_iCurrentStarEnemies++;
			}

		for (int i = 23; i <= 25; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 18.2f + ((i - 23)*0.6f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 6;
				m_pStarEnemies[m_iCurrentStarEnemies] = new StarEnemy(m_iScreenHeight*0.3f);
				m_pStarEnemies[m_iCurrentStarEnemies]->GetWidth(a_Width);
				m_pStarEnemies[m_iCurrentStarEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.25f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*0.25f));
				m_pStarEnemies[m_iCurrentStarEnemies]->SetHealth(Health);
				m_iCurrentStarEnemies++;
				//Last Star enemy shoots
			}

		for (int i = 26; i <= 30; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 22.f + ((i - 26)*0.8f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 25;
				m_pFallingEnemies[m_iCurrentFallingEnemies] = new FallingEnemy();
				m_pFallingEnemies[m_iCurrentFallingEnemies]->GetWidth(a_Width);
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.9f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetHealth(Health);
				m_iCurrentFallingEnemies++;
			}

		for (int i = 31; i <= 32; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 27.5f + ((i - 31)*0.8f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 25;
				m_pFallingEnemies[m_iCurrentFallingEnemies] = new FallingEnemy();
				m_pFallingEnemies[m_iCurrentFallingEnemies]->GetWidth(a_Width);
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.9f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pFallingEnemies[m_iCurrentFallingEnemies]->SetHealth(Health);
				m_iCurrentFallingEnemies++;
			}


		if ((m_iTrigger == 33) && (m_iGameClock > 32.7f))
		{
			m_iTrigger++;
			float a_Width;
			float a_Height;
			int Health = 1;
			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			m_pChasingEnemies[m_iCurrentChasingEnemies]->GetWidth(a_Width);
			m_pChasingEnemies[m_iCurrentChasingEnemies]->GetHeight(a_Height);
			//Top left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight - a_Height*0.5f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;

			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			//Middle left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.5f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;

			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			//Bottom left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, (a_Height*0.5f)));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;
		}

		if ((m_iTrigger == 34) && (m_iGameClock > 34.f))
		{
			m_iTrigger++;
			float a_Width;
			float a_Height;
			int Health = 1;
			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			m_pChasingEnemies[m_iCurrentChasingEnemies]->GetWidth(a_Width);
			m_pChasingEnemies[m_iCurrentChasingEnemies]->GetHeight(a_Height);
			//Top left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight - a_Height*0.5f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;

			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			//Bottom left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, (a_Height*0.5f)));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;

			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			//Top left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(a_Width, m_iScreenHeight - a_Height*0.5f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;

			m_pChasingEnemies[m_iCurrentChasingEnemies] = new ChasingEnemy();
			//Bottom left
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetPosition(Vector2(a_Width, (a_Height*0.5f)));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetVelocity(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pChasingEnemies[m_iCurrentChasingEnemies]->SetHealth(Health);
			m_iCurrentChasingEnemies++;
		}

		for (int i = 35; i <= 39; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 38.f + ((i - 35)*0.4f)))
			{
				m_iTrigger++;
				int Health = 3;
				float a_Width;
				m_pStoneEnemies[m_iCurrentStoneEnemies] = new StoneEnemy();
				m_pStoneEnemies[m_iCurrentStoneEnemies]->GetWidth(a_Width);
				switch (m_iTrigger - 1)
				{
				case (35) :
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetPosition(Vector2(m_iScreenWidth + (a_Width*0.5f), m_iScreenHeight*0.5f));
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-1.2f));
					break;
				case(36) :
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetPosition(Vector2(m_iScreenWidth + (a_Width*0.5f), m_iScreenHeight*0.8f));
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-1.3f));
					break;
				case(37) :
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetPosition(Vector2(m_iScreenWidth + (a_Width*0.5f), m_iScreenHeight*0.9f));
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-1.6f));
					break;
				case(38) :
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetPosition(Vector2(m_iScreenWidth + (a_Width*0.5f), m_iScreenHeight*0.8f));
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-1.4f));
					break;
				case(39) :
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetPosition(Vector2(m_iScreenWidth + (a_Width*0.5f), m_iScreenHeight*0.5f));
					m_pStoneEnemies[m_iCurrentStoneEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-1.8f));
					break;
				}
				m_pStoneEnemies[m_iCurrentStoneEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pStoneEnemies[m_iCurrentStoneEnemies]->SetHealth(Health);
				m_iCurrentStoneEnemies++;
			}

		for (int i = 40; i <= 42; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 43.7f + ((i - 40)*1.4f)))
			{
				m_iTrigger++;
				float a_Width;
				int Health = 5;
				m_pEyeEnemies[m_iCurrentEyeEnemies] = new EyeEnemy();
				m_pEyeEnemies[m_iCurrentEyeEnemies]->GetWidth(a_Width);
				switch (m_iTrigger - 1)
				{
				case(40) :
					m_pEyeEnemies[m_iCurrentEyeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.7f));
					break;
				case(41) :
					m_pEyeEnemies[m_iCurrentEyeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.5f));
					break;
				case(42) :
					m_pEyeEnemies[m_iCurrentEyeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight*0.3f));
					break;
				}
				m_pEyeEnemies[m_iCurrentEyeEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pEyeEnemies[m_iCurrentEyeEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pEyeEnemies[m_iCurrentEyeEnemies]->SetHealth(Health);
				m_iCurrentEyeEnemies++;
			}

		for (int i = 43; i <= 47; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 47.5f + ((i - 43)*0.5f)))
			{
				m_iTrigger++;
				float a_Width;
				float a_Height;
				int Health = 8;
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies] = new PalmTreeEnemy();
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->GetWidth(a_Width);
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->GetHeight(a_Height);
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight - a_Height*0.5f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetHealth(Health);
				m_iCurrentPalmTreeEnemies++;

				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies] = new PalmTreeEnemy();
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, a_Height*0.5f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetHealth(Health);
				m_iCurrentPalmTreeEnemies++;
			}

		for (int i = 48; i <= 55; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 51.7f + ((i - 48)*0.1f)))
			{
				m_iTrigger++;
				float a_Width;
				float a_Height;
				int Health = 1;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->GetHeight(a_Height);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth, m_iScreenHeight - a_Height*0.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-2.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;

			}

		for (int i = 56; i <= 63; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 53.6f + ((i - 56)*0.1f)))
			{
				m_iTrigger++;
				float a_Width;
				float a_Height;
				int Health = 1;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->GetHeight(a_Height);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth, a_Height*0.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*2.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		for (int i = 64; i <= 71; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 53.6f + ((i - 64)*0.1f)))
			{
				m_iTrigger++;
				float a_Width;
				float a_Height;
				int Health = 1;
				m_pBallEnemies[m_iCurrentBallEnemies] = new BallEnemy();
				m_pBallEnemies[m_iCurrentBallEnemies]->GetWidth(a_Width);
				m_pBallEnemies[m_iCurrentBallEnemies]->GetHeight(a_Height);
				m_pBallEnemies[m_iCurrentBallEnemies]->SetPosition(Vector2(m_iScreenWidth, m_iScreenHeight - a_Height*0.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetAcceleration(Vector2(0.f, m_iScreenHeight*-2.5f));
				m_pBallEnemies[m_iCurrentBallEnemies]->SetHealth(Health);
				m_iCurrentBallEnemies++;
			}

		if ((m_iTrigger == 72) && (m_iGameClock > 55.1f))
		{
			m_iTrigger++;
			float a_Width;
			float a_Height;
			int Health = 100;
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies] = new VolcanoEnemy();
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->GetWidth(a_Width);
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->GetHeight(a_Height);
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width*0.5f, a_Height*0.5f));
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->SetAcceleration(Vector2(0.f, 0.f));
			m_pVolcanoEnemies[m_iCurrentVolcanoEnemies]->SetHealth(Health);
			m_iCurrentVolcanoEnemies++;
		}

		for (int i = 73; i <= 75; i++)
			if ((m_iTrigger == i) && (m_iGameClock > 57.1f + ((i - 73)*0.5f)))
			{
				m_iTrigger++;
				float a_Width;
				float a_Height;
				int Health = 8;
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies] = new PalmTreeEnemy();
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->GetWidth(a_Width);
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->GetHeight(a_Height);
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetPosition(Vector2(m_iScreenWidth + a_Width, m_iScreenHeight - a_Height*0.5f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetVelocity(Vector2(m_iScreenWidth*-0.25f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetAcceleration(Vector2(0.f, 0.f));
				m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies]->SetHealth(Health);
				m_iCurrentPalmTreeEnemies++;
			}

		if (m_iGameClock > 65.f)
		{
			currentScreen = Screens::InputScore;
		}
#pragma endregion

#pragma region Entity updating
		for (int i = 0; i <= m_iCurrentPlayers - 1; i++)
		{
			m_pPlayer->Update(a_deltaTime);
			//Get position and dimensions of player
			Vector2 a_Position;
			float a_Width;
			float a_Height;
			m_pPlayer->GetPosition(a_Position);
			m_pPlayer->GetWidth(a_Width);
			m_pPlayer->GetHeight(a_Height);

			//if player is to the right of the screen set to within screen
			if (a_Position.x > m_iScreenWidth - a_Width*0.5f)
			{
				m_pPlayer->SetPosition(Vector2(m_iScreenWidth - a_Width*0.5f, a_Position.y));
			}
			//if player is to the left of the screen set to within screen
			if (a_Position.x < a_Width*0.5f)
			{
				m_pPlayer->SetPosition(Vector2(a_Width*0.5f, a_Position.y));
			}
			//if player is above screen set to within screen
			if (a_Position.y > m_iScreenHeight - a_Height*0.5f)
			{
				m_pPlayer->SetPosition(Vector2(a_Position.x, m_iScreenHeight - a_Height*0.5f));
			}
			//if player is Below screen set to within screen
			if (a_Position.y<a_Height*0.5f)
			{
				m_pPlayer->SetPosition(Vector2(a_Position.x, a_Height*0.5f));
			}
		}

		for (int i = 0; i <= m_iCurrentPlayerBullets - 1; i++)
		{
			bool BulletDestroyed = false;
			m_PlayerBullets[i]->Update(a_deltaTime);
			Vector2 a_Position;
			float a_Width;
			float a_Height;
			m_PlayerBullets[i]->GetPosition(a_Position);
			m_PlayerBullets[i]->GetWidth(a_Width);
			m_PlayerBullets[i]->GetHeight(a_Height);
			if (((a_Position.x - a_Width*0.5f) > m_iScreenWidth) || (a_Position.y<a_Height*-0.5f) || (a_Position.y>m_iScreenHeight + a_Height*0.5f))
			{
				CollisionPlayerBullet(i);
				BulletDestroyed = true;
			}
			for (int j = 0; j <= MaxEnemy(); j++)
			{
				if ((j <= m_iCurrentBallEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pBallEnemies[j])) && (!BulletDestroyed))
				{
					CollisionBallEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentBarrageEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pBarrageEnemies[j])) && (!BulletDestroyed))
				{
					CollisionBarrageEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentChasingEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pChasingEnemies[j])) && (!BulletDestroyed))
				{
					CollisionChasingEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentEyeEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pEyeEnemies[j])) && (!BulletDestroyed))
				{
					CollisionEyeEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentFallingEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pFallingEnemies[j])) && (!BulletDestroyed))
				{
					CollisionFallingEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentPalmTreeEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pPalmTreeEnemies[j])) && (!BulletDestroyed))
				{
					CollisionPalmTreeEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentSharkEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pSharkEnemies[j])) && (!BulletDestroyed))
				{
					CollisionSharkEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentStarEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pStarEnemies[j])) && (!BulletDestroyed))
				{
					CollisionStarEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentStoneEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pStoneEnemies[j])) && (!BulletDestroyed))
				{
					CollisionStoneEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentVolcanoEnemies - 1) && (TestCollision(m_PlayerBullets[i], m_pVolcanoEnemies[j])) && (!BulletDestroyed))
				{
					CollisionVolcanoEnemy(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
				if ((j <= m_iCurrentVolcanoProjectiles - 1) && (TestCollision(m_PlayerBullets[i], m_pVolcanoProjectiles[j])) && (!BulletDestroyed))
				{
					CollisionVolcanoProjectile(j);
					CollisionPlayerBullet(i);
					BulletDestroyed = true;
				}
			}
		}

		for (int i = 0; i <= 1; i++)
		{
			m_Background[i]->Update(a_deltaTime);
		}

		for (int i = 0; i <= m_iCurrentBallEnemies - 1; i++)
		{
			m_pBallEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pBallEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentChasingEnemies - 1; i++)
		{
			m_pChasingEnemies[i]->Update(a_deltaTime, m_pPlayer);
			if (TestCollision(m_pPlayer, m_pChasingEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentEyeEnemies - 1; i++)
		{
			m_pEyeEnemies[0]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pEyeEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentFallingEnemies - 1; i++)
		{
			m_pFallingEnemies[i]->Update(a_deltaTime, m_pPlayer);
			if (TestCollision(m_pPlayer, m_pFallingEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentPalmTreeEnemies - 1; i++)
		{
			m_pPalmTreeEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pPalmTreeEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentSharkEnemies - 1; i++)
		{
			m_pSharkEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pSharkEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentStarEnemies - 1; i++)
		{
			m_pStarEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pStarEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentStoneEnemies - 1; i++)
		{
			m_pStoneEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pStoneEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentVolcanoEnemies - 1; i++)
		{
			m_pVolcanoEnemies[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pVolcanoEnemies[i]))
				CollisionPlayer();
		}

		for (int i = 0; i <= m_iCurrentVolcanoProjectiles - 1; i++)
		{
			m_pVolcanoProjectiles[i]->Update(a_deltaTime);
			if (TestCollision(m_pPlayer, m_pVolcanoProjectiles[i]))
				CollisionPlayer();
		}

#pragma endregion
		// quit our application when escape is pressed
		if ((Application::IsKeyDown(UG::KEY_X)) && (m_iCurrentPlayerBullets <= 6) && (m_pPlayer->BulletReady()))
		{
			m_PlayerBullets[m_iCurrentPlayerBullets] = new PlayerBullet();
			//Get player position and width
			Vector2 PlayerPos;
			float PlayerWidth;
			m_pPlayer->GetPosition(PlayerPos);
			m_pPlayer->GetWidth(PlayerWidth);
			Vector2 a_SpawnPos;
			a_SpawnPos.SetValue(PlayerPos.x + PlayerWidth*0.5f, PlayerPos.y);
			//Spawn 3 bullets with the same speed but different vertical velocities 
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetPosition(a_SpawnPos);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetVelocity(Vector2(m_iScreenWidth, 0.f));
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetAcceleration(Vector2(0.f, 0.f));
			m_iCurrentPlayerBullets++;

			//All the bullets have the same speed but different velocities
			//the vertical velocity is proportional to the screen height
			//use a pythagorean trigangle to find the horizontal velocity
			m_PlayerBullets[m_iCurrentPlayerBullets] = new PlayerBullet();
			Vector2 a_Velocity;
			a_Velocity.y = m_iScreenHeight*0.2f;
			a_Velocity.x = powf(powf(m_iScreenWidth, 2.f) - powf(a_Velocity.y, 2.f), 0.5f);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetPosition(a_SpawnPos);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetVelocity(a_Velocity);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetAcceleration(Vector2(0.f, 0.f));
			m_iCurrentPlayerBullets++;

			//velocities are same as above with negative vertical velocity
			m_PlayerBullets[m_iCurrentPlayerBullets] = new PlayerBullet();
			a_Velocity.y *= -1.f;
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetPosition(a_SpawnPos);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetVelocity(a_Velocity);
			m_PlayerBullets[m_iCurrentPlayerBullets]->SetAcceleration(Vector2(0.f, 0.f));
			m_iCurrentPlayerBullets++;
		}
		if (Application::IsKeyDown(UG::KEY_ESCAPE))
			destroy();
		m_iGameClock += a_deltaTime;

		//if the player has died
		if (m_iCurrentPlayers < 1)
		{
			if (m_iGameoverClock < 1.f)
			{
				m_iGameoverClock += a_deltaTime;
			}
			else
			{
				currentScreen = Screens::InputScore;
			}
		}
	}
}
//onDraw is called each frame after onUpdate has been called
//this is where any rendering should be carried out
void Gynoug::onDraw()
{
	Application::ClearScreen();
	if (currentScreen == Screens::Splash)
	{
		m_SplashScreen->Draw();
	}

	if (currentScreen == Screens::Main)
	{
		m_SplashScreen->Draw();
		m_pNewGameButton->Draw();
		m_pHighscoresButton->Draw();
		m_pQuitButton->Draw();
	}

	if (currentScreen == Screens::Highscores)
	{
		UG::Application::DrawString("Highscores", m_iScreenWidth*0.5f - 10*15.f, m_iScreenHeight, 2.f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
		m_pBackButton->Draw();
		std::string Scores[10]{ "","","","","","","","","","" };
		std::ifstream ScoresFile;
		ScoresFile.open("./Scores.txt");

		for (int i = 0; ScoresFile.good() && i<=9; i++)
		{
			std::getline(ScoresFile, Scores[i]);
		}
		for (int i = 0; i <= 9; i++)
		{
			UG::Application::DrawString(Scores[i].c_str(), m_iScreenWidth*0.5f - Scores[i].length()*7.5f, (m_iScreenHeight*(0.9f-0.07*i)) + 13.f, 1.f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
		}
		ScoresFile.close();
	}

	if (currentScreen == Screens::InputScore)
	{

	}

	if (currentScreen == Screens::Game)
	{
		for (int i = 0; i <= 1; i++)
		{
			m_Background[i]->Draw();
		}
#pragma region Entity drawing

		for (int i = 0; i <= m_iCurrentPlayers - 1; i++)
		{
			m_pPlayer->Draw();
		}

		for (int i = 0; i <= m_iCurrentPlayerBullets - 1; i++)
		{
			m_PlayerBullets[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentBallEnemies - 1; i++)
		{
			m_pBallEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentChasingEnemies - 1; i++)
		{
			m_pChasingEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentEyeEnemies - 1; i++)
		{
			m_pEyeEnemies[0]->Draw();
		}
		for (int i = 0; i <= m_iCurrentFallingEnemies - 1; i++)
		{
			m_pFallingEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentPalmTreeEnemies - 1; i++)
		{
			m_pPalmTreeEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentSharkEnemies - 1; i++)
		{
			m_pSharkEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentStarEnemies - 1; i++)
		{
			m_pStarEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentStoneEnemies - 1; i++)
		{
			m_pStoneEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentVolcanoEnemies - 1; i++)
		{
			m_pVolcanoEnemies[i]->Draw();
		}
		for (int i = 0; i <= m_iCurrentVolcanoProjectiles - 1; i++)
		{
			m_pVolcanoProjectiles[i]->Draw();
		}

#pragma endregion
		//convert m_iscore to a string to be concatonated with "score" then convert back to Char* array to be put in draw string
		std::string a_Score = std::to_string(m_iScore);
		a_Score = "SCORE " + a_Score;
		char *a_ScoreChar = (char*)a_Score.c_str();
		Application::SetFont("./fonts/invaders.fnt");
		Application::DrawString(a_ScoreChar, (int)(m_iScreenWidth * 0.4f), m_iScreenHeight - 2, 1.f);
		Application::SetFont(nullptr);
	}
}

//onDestroy - this will be called at the termination of the application. Any items which need to be
//deallocated should be done so in here. E.G things that were created in the onCreate function.
void Gynoug::onDestroy()
{
	delete m_pPlayer;
	for (int i = 0; i <= 1; i++)
	{
		delete m_Background[i];
	}
	while (m_iCurrentPlayerBullets>0)
	{
		delete m_PlayerBullets[m_iCurrentPlayerBullets - 1];
		m_iCurrentPlayerBullets--;
	}
	while (m_iCurrentBallEnemies > 0)
	{
		delete m_pBallEnemies[m_iCurrentBallEnemies - 1];
		m_iCurrentBallEnemies--;
	}
	while (m_iCurrentChasingEnemies > 0)
	{
		delete m_pChasingEnemies[m_iCurrentChasingEnemies - 1];
		m_iCurrentChasingEnemies--;
	}
	while (m_iCurrentEyeEnemies > 0)
	{
		delete m_pEyeEnemies[m_iCurrentEyeEnemies - 1];
		m_iCurrentEyeEnemies--;
	}
	while (m_iCurrentFallingEnemies > 0)
	{
		delete m_pFallingEnemies[m_iCurrentFallingEnemies - 1];
		m_iCurrentFallingEnemies--;
	}
	while (m_iCurrentPalmTreeEnemies > 0)
	{
		delete m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies - 1];
		m_iCurrentPalmTreeEnemies--;
	}
	while (m_iCurrentSharkEnemies > 0)
	{
		delete m_pSharkEnemies[m_iCurrentSharkEnemies - 1];
		m_iCurrentSharkEnemies--;
	}
	while (m_iCurrentStarEnemies > 0)
	{
		delete m_pStarEnemies[m_iCurrentStarEnemies - 1];
		m_iCurrentStarEnemies--;
	}
	while (m_iCurrentStoneEnemies > 0)
	{
		delete m_pStoneEnemies[m_iCurrentStoneEnemies - 1];
		m_iCurrentStoneEnemies--;
	}
	while (m_iCurrentVolcanoEnemies > 0)
	{
		delete m_pVolcanoEnemies[m_iCurrentVolcanoEnemies-1];
		m_iCurrentVolcanoEnemies--;
	}
	while (m_iCurrentVolcanoProjectiles > 0)
	{
		delete m_pVolcanoProjectiles[m_iCurrentVolcanoProjectiles - 1];
		m_iCurrentVolcanoProjectiles--;
	}
}

bool Gynoug::TestCollision(Entity * a_pEntity1, Entity * a_pEntity2)
{
	//Get positions and dimensions of entities
	//Entity 1
	float a_pWidth1;
	float a_pHeight1;
	Vector2 a_pv2Position1;
	a_pEntity1->GetWidth(a_pWidth1);
	a_pEntity1->GetHeight(a_pHeight1);
	a_pEntity1->GetPosition(a_pv2Position1);
	float a_pHalfWidth1 = a_pWidth1*0.5f;
	float a_pHalfHeight1 = a_pHeight1*0.5f;

	//Entity 2
	float a_pWidth2;
	float a_pHeight2;
	Vector2 a_pv2Position2;
	a_pEntity2->GetWidth(a_pWidth2);
	a_pEntity2->GetHeight(a_pHeight2);
	a_pEntity2->GetPosition(a_pv2Position2);
	float a_pHalfWidth2 = a_pWidth2*0.5f;
	float a_pHalfHeight2 = a_pHeight2*0.5f;

	//Test if the X bounds of the entities meet
	//X bounds are Xpos + half width
	//if far right of entity1 is past the far left of entity 2 and far left of entity1 is before the far right of entity2
	//might need to do other way round too for collisions in the back
	if (a_pv2Position1.x + a_pHalfWidth1 > a_pv2Position2.x - a_pHalfWidth2 && a_pv2Position1.x - a_pHalfWidth1 < a_pv2Position2.x + a_pHalfWidth2)
	{
		//Then test the same for the Ypos and heights
		if (a_pv2Position1.y + a_pHalfHeight1 > a_pv2Position2.y - a_pHalfHeight2 && a_pv2Position1.y - a_pHalfHeight1 < a_pv2Position2.y + a_pHalfHeight2)
		{
			return true;
		}
	}
	return false;
}

void Gynoug::CollisionPlayer()
{
	m_iCurrentPlayers--;
}

void Gynoug::CollisionPlayerBullet(int a_pPlayerBulletNum)
{
	delete m_PlayerBullets[a_pPlayerBulletNum];
	if (a_pPlayerBulletNum != m_iCurrentPlayerBullets - 1)
	{
		m_PlayerBullets[a_pPlayerBulletNum] = new PlayerBullet(*m_PlayerBullets[m_iCurrentPlayerBullets - 1]);
		delete m_PlayerBullets[m_iCurrentPlayerBullets - 1];
	}
	m_iCurrentPlayerBullets--;
}

void Gynoug::CollisionBallEnemy(int a_pBallEnemyNum)
{
	int a_pHealth;
	m_pBallEnemies[a_pBallEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pBallEnemies[a_pBallEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 100;
		delete m_pBallEnemies[a_pBallEnemyNum];
		if (a_pBallEnemyNum != m_iCurrentBallEnemies - 1)
		{
			m_pBallEnemies[a_pBallEnemyNum] = new BallEnemy(*m_pBallEnemies[m_iCurrentBallEnemies - 1]);
			delete m_pBallEnemies[m_iCurrentBallEnemies - 1];
		}
		m_iCurrentBallEnemies--;
	}
}
 
void Gynoug::CollisionBarrageEnemy(int a_pBarrageEnemyNum)
{
	int a_pHealth;
	m_pBarrageEnemies[a_pBarrageEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pBarrageEnemies[a_pBarrageEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 100;
		delete m_pBarrageEnemies[a_pBarrageEnemyNum];
		if (a_pBarrageEnemyNum != m_iCurrentBarrageEnemies - 1)
		{
			m_pBarrageEnemies[a_pBarrageEnemyNum] = new BarrageEnemy(*m_pBarrageEnemies[m_iCurrentBarrageEnemies - 1]);
			delete m_pBarrageEnemies[m_iCurrentBarrageEnemies - 1];
		}
		m_iCurrentBarrageEnemies--;
	}
}

void Gynoug::CollisionChasingEnemy(int a_pChasingEnemyNum)
{
	int a_pHealth;
	m_pChasingEnemies[a_pChasingEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pChasingEnemies[a_pChasingEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 100;
		delete m_pChasingEnemies[a_pChasingEnemyNum];
		if (a_pChasingEnemyNum != m_iCurrentChasingEnemies - 1)
		{
			m_pChasingEnemies[a_pChasingEnemyNum] = new ChasingEnemy(*m_pChasingEnemies[m_iCurrentChasingEnemies - 1]);
			delete m_pChasingEnemies[m_iCurrentChasingEnemies - 1];
		}
		m_iCurrentChasingEnemies--;
	}
}


void Gynoug::CollisionEyeEnemy(int a_pEyeEnemyNum)
{
	int a_pHealth;
	m_pEyeEnemies[a_pEyeEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pEyeEnemies[a_pEyeEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 600;
		delete m_pEyeEnemies[a_pEyeEnemyNum];
		if (a_pEyeEnemyNum != m_iCurrentEyeEnemies - 1)
		{
			m_pEyeEnemies[a_pEyeEnemyNum] = new EyeEnemy(*m_pEyeEnemies[m_iCurrentEyeEnemies - 1]);
			delete m_pEyeEnemies[m_iCurrentEyeEnemies - 1];
		}
		m_iCurrentEyeEnemies--;
	}
}

void Gynoug::CollisionFallingEnemy(int a_pFallingEnemyNum)
{
	int a_pHealth;
	m_pFallingEnemies[a_pFallingEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pFallingEnemies[a_pFallingEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 2000;
		delete m_pFallingEnemies[a_pFallingEnemyNum];
		if (a_pFallingEnemyNum != m_iCurrentFallingEnemies - 1)
		{
			m_pFallingEnemies[a_pFallingEnemyNum] = new FallingEnemy(*m_pFallingEnemies[m_iCurrentFallingEnemies - 1]);
			delete m_pFallingEnemies[m_iCurrentFallingEnemies - 1];
		}
		m_iCurrentFallingEnemies--;
	}
}

void Gynoug::CollisionPalmTreeEnemy(int a_pPalmTreeEnemyNum)
{
	int a_pHealth;
	m_pPalmTreeEnemies[a_pPalmTreeEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pPalmTreeEnemies[a_pPalmTreeEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 300;
		delete m_pPalmTreeEnemies[a_pPalmTreeEnemyNum];
		if (a_pPalmTreeEnemyNum != m_iCurrentPalmTreeEnemies - 1)
		{
			m_pPalmTreeEnemies[a_pPalmTreeEnemyNum] = new PalmTreeEnemy(*m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies - 1]);
			delete m_pPalmTreeEnemies[m_iCurrentPalmTreeEnemies - 1];
		}
		m_iCurrentPalmTreeEnemies--;
	}
}

void Gynoug::CollisionSharkEnemy(int a_pSharkEnemyNum)
{
	int a_pHealth;
	m_pSharkEnemies[a_pSharkEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pSharkEnemies[a_pSharkEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 1300;
		delete m_pSharkEnemies[a_pSharkEnemyNum];
		if (a_pSharkEnemyNum != m_iCurrentSharkEnemies - 1)
		{
			m_pSharkEnemies[a_pSharkEnemyNum] = new SharkEnemy(*m_pSharkEnemies[m_iCurrentSharkEnemies - 1]);
			delete m_pSharkEnemies[m_iCurrentSharkEnemies - 1];
		}
		m_iCurrentSharkEnemies--;
	}
}

void Gynoug::CollisionStarEnemy(int a_pStarEnemyNum)
{
	int a_pHealth;
	m_pStarEnemies[a_pStarEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pStarEnemies[a_pStarEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 300;
		delete m_pStarEnemies[a_pStarEnemyNum];
		if (a_pStarEnemyNum != m_iCurrentStarEnemies - 1)
		{
			m_pStarEnemies[a_pStarEnemyNum] = new StarEnemy(*m_pStarEnemies[m_iCurrentStarEnemies - 1]);
			delete m_pStarEnemies[m_iCurrentStarEnemies - 1];
		}
		m_iCurrentStarEnemies--;
	}
}

void Gynoug::CollisionStoneEnemy(int a_pStoneEnemyNum)
{
	int a_pHealth;
	m_pStoneEnemies[a_pStoneEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pStoneEnemies[a_pStoneEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 100;
		delete m_pStoneEnemies[a_pStoneEnemyNum];
		if (a_pStoneEnemyNum != m_iCurrentStoneEnemies - 1)
		{
			m_pStoneEnemies[a_pStoneEnemyNum] = new StoneEnemy(*m_pStoneEnemies[m_iCurrentStoneEnemies - 1]);
			delete m_pStoneEnemies[m_iCurrentStoneEnemies - 1];
		}
		m_iCurrentStoneEnemies--;
	}
}

void Gynoug::CollisionVolcanoEnemy(int a_pVolcanoEnemyNum)
{
	int a_pHealth;
	m_pVolcanoEnemies[a_pVolcanoEnemyNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pVolcanoEnemies[a_pVolcanoEnemyNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 2500;
		delete m_pVolcanoEnemies[a_pVolcanoEnemyNum];
		if (a_pVolcanoEnemyNum != m_iCurrentVolcanoEnemies - 1)
		{
			m_pVolcanoEnemies[a_pVolcanoEnemyNum] = new VolcanoEnemy(*m_pVolcanoEnemies[m_iCurrentVolcanoEnemies - 1]);
			delete m_pVolcanoEnemies[m_iCurrentVolcanoEnemies - 1];
		}
		m_iCurrentVolcanoEnemies--;
	}
}

void Gynoug::CollisionVolcanoProjectile(int a_pVolcanoProjectileNum)
{
	int a_pHealth;
	m_pVolcanoProjectiles[a_pVolcanoProjectileNum]->GetHealth(a_pHealth);
	a_pHealth--;
	m_pVolcanoProjectiles[a_pVolcanoProjectileNum]->SetHealth(a_pHealth);
	if (a_pHealth <= 0)
	{
		m_iScore += 100;
		delete m_pVolcanoProjectiles[a_pVolcanoProjectileNum];
		if (a_pVolcanoProjectileNum != m_iCurrentVolcanoProjectiles - 1)
		{
			m_pVolcanoProjectiles[a_pVolcanoProjectileNum] = new VolcanoProjectile(*m_pVolcanoProjectiles[m_iCurrentVolcanoProjectiles - 1]);
			delete m_pVolcanoProjectiles[m_iCurrentVolcanoProjectiles - 1];
		}
		m_iCurrentVolcanoProjectiles--;
	}
}


int Gynoug::MaxEnemy()
{
	//finds the number of enemies in the class with the highest number of enemies in it
	int MaxEnemy= m_iCurrentBallEnemies;
	if (m_iCurrentChasingEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentChasingEnemies;
	if (m_iCurrentEyeEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentEyeEnemies;
	if (m_iCurrentFallingEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentFallingEnemies;
	if (m_iCurrentPalmTreeEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentPalmTreeEnemies;
	if (m_iCurrentSharkEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentSharkEnemies;
	if (m_iCurrentStarEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentStarEnemies;
	if (m_iCurrentStoneEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentStoneEnemies;
	if (m_iCurrentVolcanoEnemies > MaxEnemy)
		MaxEnemy = m_iCurrentVolcanoEnemies;
	if (m_iCurrentVolcanoProjectiles > MaxEnemy)
		MaxEnemy = m_iCurrentVolcanoProjectiles;
	return MaxEnemy;
}