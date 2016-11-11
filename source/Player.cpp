#include "Player.h"

Player::Player() : Entity("./images/Player.png", 116, 115)
{
	m_BulletTimer = 0.f;
}

Player::Player(const Player& a_player) : Entity(a_player)
{
	
}

Player::~Player()
{
}

void Player::Update(float a_fTimeStep)
{
	Entity::Update(a_fTimeStep);
	Vector2 v2Pos;
	GetPosition(v2Pos);
	float v2PosX = 0;
	float v2PosY = 0;

	//Use the following to test for player Movement
	if (UG::Application::IsKeyDown(UG::KEY_RIGHT))
	{
		v2PosX += 320* a_fTimeStep;
	}
	if (UG::Application::IsKeyDown(UG::KEY_LEFT))
	{
		v2PosX -= 320* a_fTimeStep;
	}
	if (UG::Application::IsKeyDown(UG::KEY_UP))
	{
		v2PosY += 320* a_fTimeStep;
	}
	if (UG::Application::IsKeyDown(UG::KEY_DOWN))
	{
		v2PosY -= 320*a_fTimeStep;
	}
	v2Pos.x += v2PosX;
	v2Pos.y += v2PosY;
	SetPosition(v2Pos);
	m_BulletTimer += a_fTimeStep;
}

void Player::Draw()
{
	Entity::Draw();
}

bool Player::BulletReady()
{
	if (m_BulletTimer >= 0.25f)
	{
		m_BulletTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}
