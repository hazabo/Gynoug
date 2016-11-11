#include "Entity.h"
#include "Application.h"
#include "Gynoug.h"

Entity::Entity(const char* a_textureFileName, float a_width, float a_height)
{
	m_iSpriteID = UG::Application::CreateSprite(a_textureFileName, a_width, a_height, true);
	m_fWidth = a_width;
	m_fHeight = a_height;
}

Entity::Entity(const char* a_textureFileName, const Vector2& a_v2Size, const float* a_fv4UVCoords)
{
	m_iSpriteID = UG::Application::CreateSprite(a_textureFileName, a_v2Size, Vector2(0.5f, 0.5f), a_fv4UVCoords);
	m_fWidth = a_v2Size.x;
	m_fHeight = a_v2Size.y;
}

Entity::Entity(const Entity& a_Entity)
{
	m_iSpriteID = UG::Application::DuplicateSprite(a_Entity.m_iSpriteID);
	m_fWidth = a_Entity.m_fWidth;
	m_fHeight = a_Entity.m_fHeight;
	m_Position.SetValue(a_Entity.m_Position);
	m_Velocity.SetValue(a_Entity.m_Velocity);
	m_Acceleration.SetValue(a_Entity.m_Acceleration);
}

Entity::~Entity()
{
	UG::Application::DestroySprite(m_iSpriteID);
}

void Entity::Update(float a_fDeltaTime)
{
	//Update position by adding the average velocity over the last delta time (X+((2V+A)/2)
	SetPosition(m_Position + Vector2((((m_Velocity.x * 2.f + (m_Acceleration.x*a_fDeltaTime))*0.5f)*a_fDeltaTime), (((m_Velocity.y * 2.f + (m_Acceleration.y*a_fDeltaTime))*0.5f)*a_fDeltaTime)));
	SetVelocity(m_Velocity + Vector2(m_Acceleration.x*a_fDeltaTime,m_Acceleration.y*a_fDeltaTime));
}

void Entity::Draw()
{
	UG::Application::DrawSprite(m_iSpriteID);
}

void Entity::GetPosition(Vector2& a_v2Position) const
{
	a_v2Position = m_Position;
}

void Entity::SetPosition(const Vector2& a_v2Position)
{
	m_Position.SetValue(a_v2Position);
	UG::Application::MoveSprite(m_iSpriteID, &a_v2Position.x);
}

void Entity::GetVelocity(Vector2& a_v2Velocity) const
{
	a_v2Velocity = m_Velocity;
}

void Entity::SetVelocity(Vector2& a_v2Velocity)
{
	m_Velocity.SetValue(a_v2Velocity);
}

void Entity::GetAcceleration(Vector2& a_v2Acceleration) const
{
	a_v2Acceleration = m_Acceleration;
}

void Entity::SetAcceleration(Vector2& a_v2Acceleration)
{
	m_Acceleration.SetValue(a_v2Acceleration);
}

void Entity::GetWidth(float& a_vWidth) const
{
	a_vWidth = m_fWidth;
}

void Entity::GetHeight(float& a_vHeight)const
{
	a_vHeight = m_fHeight;
}