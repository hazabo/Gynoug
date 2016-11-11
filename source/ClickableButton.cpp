#include "ClickableButton.h"
#include <iostream>

ClickableButton::ClickableButton(const std::string& a_Text, const float& a_Startx, const float& a_Starty, const float a_Width, const float a_Height, const UG::SColour& a_Colour)
{
	m_Text=a_Text;
	m_StartX=a_Startx;
	m_StartY=a_Starty;
	m_Width=a_Width;
	m_Height=a_Height;
	m_Colour=a_Colour;
}

ClickableButton::~ClickableButton()
{

}

bool ClickableButton::Update(float MouseX, float MouseY)
{
	if (MouseX > m_StartX - m_Width*0.5f
		&& MouseX < m_StartX + m_Width*0.5f
		&& MouseY > m_StartY - m_Height*0.5f
		&& MouseY < m_StartY + m_Height*0.5f)
		return true;
	return false;

}

void ClickableButton::Draw()
{
	//Left line 
	UG::Application::DrawLine(m_StartX - m_Width*0.5f, m_StartY - m_Height*0.5f, m_StartX - m_Width*0.5f, m_StartY + m_Height*0.5f, m_Colour);
	//Right line
	UG::Application::DrawLine(m_StartX + m_Width*0.5f, m_StartY - m_Height*0.5f, m_StartX + m_Width*0.5f, m_StartY + m_Height*0.5f, m_Colour);
	//Top line
	UG::Application::DrawLine(m_StartX - m_Width*0.5f, m_StartY + m_Height*0.5f, m_StartX + m_Width*0.5f, m_StartY + m_Height*0.5f, m_Colour);
	//Bottom line
	UG::Application::DrawLine(m_StartX - m_Width*0.5f, m_StartY - m_Height*0.5f, m_StartX + m_Width*0.5f, m_StartY - m_Height*0.5f, m_Colour);
	//Text
	if (m_Text.length()!=0)
		UG::Application::DrawString(m_Text.c_str(), m_StartX-m_Text.length()*7.5f, m_StartY+13.f, 1.f, m_Colour);
}
