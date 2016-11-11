

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Vector2.h"

class Entity
{
public:
	//Constructor with Arguments
	Entity(const char* a_textureFileName, float a_width, float a_height);
	Entity(const char* a_textureFileName, const Vector2& a_v2Size, const float* a_fv4UVCoords);
	Entity(const Entity& a_Entity);
	virtual ~Entity();


	virtual void Update(float a_fdeltaTime);
	virtual void Draw();

	void GetPosition(Vector2& a_v2Position) const;
	void SetPosition(const Vector2& a_v2Position);

	void GetVelocity(Vector2& a_v2Velocity)const;
	void SetVelocity(Vector2& a_v2Velocity);

	void GetAcceleration(Vector2& a_v2Acceleration)const;
	void SetAcceleration(Vector2& a_v2Acceleration);

	void GetWidth(float& a_vWidth) const;
	void GetHeight(float& a_vHeight)const;

protected:

	unsigned int m_iSpriteID;
private:
	float m_fWidth;
	float m_fHeight;
	Vector2 m_Position;
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
};

#endif //__ENTITY_H__