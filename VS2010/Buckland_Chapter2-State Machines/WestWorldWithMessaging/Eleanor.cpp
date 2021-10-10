#include "Eleanor.h"

bool Eleanor::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Eleanor::Update()
{
	//set text color to green
	SetTextColor(0x000f);

	m_pStateMachine->Update();
}