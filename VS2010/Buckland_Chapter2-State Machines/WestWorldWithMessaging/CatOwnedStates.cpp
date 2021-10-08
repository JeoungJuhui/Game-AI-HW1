#include "CatOwnedStates.h"  // �����
#include "fsm/State.h"
#include "Cat.h"   // �����
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for SleepAllDay
SleepAllDay* SleepAllDay::Instance()
{
	static SleepAllDay instance;

	return &instance;
}


void SleepAllDay::Enter(Cat* pCat)
{
	// ����̴� ���� ������ �ʴٸ�, ��� ���翡�� ���� �ܴ�.
	if (pCat->Location() != yard)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The cat sleeps in the yard.]";

		pCat->ChangeLocation(yard);
	}
}


void SleepAllDay::Execute(Cat* pCat)
{
	// ���� ������ ������ ����.

	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[zzzzzzzzzzzzzzzzzz]" << ", m_iThirst: "<< pCat->m_iThirst;

	if (pCat->Thirsty())
	{
		pCat->GetFSM()->ChangeState(VisitHomeGetWater::Instance());
	}
}


void SleepAllDay::Exit(Cat* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": "
		<< "[The cat wants water.]";
}


bool SleepAllDay::OnMessage(Cat* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for VisitHomeGetWater

VisitHomeGetWater* VisitHomeGetWater::Instance()
{
	static VisitHomeGetWater instance;
	
	return &instance;
}

void VisitHomeGetWater::Enter(Cat* pCat)
{
	// ������ ��� �̵�
	if (pCat->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The cat in the shack.]";

		pCat->ChangeLocation(shack);
	}

	// ����̰� ���翡�� �λ��Ѵ�. (�޼��� ����)
	// �ش� �޼��� �ڵ��� MinersWifeOwnedStates.cpp ������ 59��°�� ����
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : ����̰� 
		ent_Elsa,            //ID of recipient : ���翡�� �λ�
		Msg_Hee_haw,   //the message           : �λ�(�޼���) ����
		NO_ADDITIONAL_INFO);
}


void VisitHomeGetWater::Execute(Cat* pCat)
{
	// ���� �ؼ�
	pCat->DrinkWater();

	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The sound of drinking water]" << ", m_iThirst: " << pCat->m_iThirst;

	pCat->GetFSM()->ChangeState(SleepAllDay::Instance());
}


void VisitHomeGetWater::Exit(Cat* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The cat go to the yard.]";
}


bool VisitHomeGetWater::OnMessage(Cat* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
