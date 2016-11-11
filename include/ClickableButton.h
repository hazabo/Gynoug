
#ifndef __CLICKABLE_BUTTON_H__
#define __CLICKABLE_BUTTON_H__
#include "Application.h"

class ClickableButton
{
public:
	ClickableButton(const std::string& a_Text, const float& a_Startx, const float& a_Starty, const float a_Width, const float a_Height, const UG::SColour& a_Colour);
	~ClickableButton();

	bool Update(float MouseX, float MouseY);

	void Draw();
private:
	std::string m_Text;
	float m_StartX;
	float m_StartY;
	float m_Width;
	float m_Height;
	UG::SColour m_Colour;
};
#endif //__CLICKABLE_BUTTON_H__