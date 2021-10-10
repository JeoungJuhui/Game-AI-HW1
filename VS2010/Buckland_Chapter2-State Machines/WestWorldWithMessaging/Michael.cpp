#include "Michael.h"

bool Michael::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Michael::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_plan += 1;

	m_pStateMachine->Update();
}

bool Michael::Planning()const
{
	if (m_plan >= Plan_Complete) { return true; }

	return false;
}