#include "Cat.h"

bool Cat::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Cat::Update()
{
	SetTextColor(0x000f);  // ÇÏ¾á»ö ±Û¾¾
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_iThirst += 1;

	m_pStateMachine->Update();
}

bool Cat::Thirsty()const
{
	if (m_iThirst >= Thirst_Cat) { return true; }

	return false;
}
