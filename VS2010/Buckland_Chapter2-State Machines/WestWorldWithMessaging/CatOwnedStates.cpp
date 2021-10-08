#include "CatOwnedStates.h"  // 고양이
#include "fsm/State.h"
#include "Cat.h"   // 고양이
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
	// 고양이는 목이 마르지 않다면, 계속 마당에서 잠을 잔다.
	if (pCat->Location() != yard)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The cat sleeps in the yard.]";

		pCat->ChangeLocation(yard);
	}
}


void SleepAllDay::Execute(Cat* pCat)
{
	// 목이 마르면 집으로 들어간다.

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
	// 집으로 장소 이동
	if (pCat->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[The cat in the shack.]";

		pCat->ChangeLocation(shack);
	}

	// 고양이가 엘사에게 인사한다. (메세지 전달)
	// 해당 메세지 핸들은 MinersWifeOwnedStates.cpp 파일의 59번째줄 참조
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : 고양이가 
		ent_Elsa,            //ID of recipient : 엘사에게 인사
		Msg_Hee_haw,   //the message           : 인사(메세지) 내용
		NO_ADDITIONAL_INFO);
}


void VisitHomeGetWater::Execute(Cat* pCat)
{
	// 갈증 해소
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
