#include "ChidiOwnedStates.h"  // 치디
#include "fsm/State.h"
#include "Chidi.h"   // 치디
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include "misc/Utils.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif




//------------------------------------------------------------------------methods for WritingThesis
WritingThesis* WritingThesis::Instance()
{
	static WritingThesis instance;

	return &instance;
}


void WritingThesis::Enter(Chidi* pCat)
{
	//치디는 집에서 항상 논문을 쓴다.
	if (pCat->Location() != home)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Chidi is at home.]";

		pCat->ChangeLocation(home);
	}
}


void WritingThesis::Execute(Chidi* pCat)
{

	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Chidi is writing thesis.]";

}


void WritingThesis::Exit(Chidi* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": "
		<< "[Chidi gets nervous.]";
	//엘리너의 말을 들으면 치디는 긴장하고 논문 적는 것을 멈춘다.
}


bool WritingThesis::OnMessage(Chidi* pCat, const Telegram& msg)
{
	//엘리너에게 도와달라는 메세지를 받는다.
	if (msg.Msg == Msg_Helpme_Chidi)
	{

		cout << "\nMessage handled by " << GetNameOfEntity(pCat->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN);

		//엘리너의 메세지를 받은 치디의 반응.
		cout << "\n" << GetNameOfEntity(pCat->ID()) <<
			": What did you say?";

		//엘리너의 목소리를 들으면 배가 아픈(Stomachache) 상태로 전환된다.
		pCat->GetFSM()->ChangeState(Stomachache::Instance());

		return true;

	}

	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for VisitHomeGetWater

Stomachache* Stomachache::Instance()
{
	static Stomachache instance;

	return &instance;
}

void Stomachache::Enter(Chidi* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[When Chidi is nervous, his stomach hurts.]";
}


void Stomachache::Execute(Chidi* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "OH... I feel bad... my stomach hurts again.";
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "I don't want you to go to Badplace. You have to be a good man.";
	
	// 메세지 핸들 EleanorOwnedStates.cpp 파일의 208번째줄
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : 치디가
		ent_Eleanor,            //ID of recipient : 엘리너를 부른다.
		Msg_Be_careful_Eleanor,   //the message           : 메세지 내용
		NO_ADDITIONAL_INFO);

	pCat->GetFSM()->ChangeState(FixProblem::Instance()); //엘리너에게 말한 뒤 문제를 고치는 상태로 전환.

}


void Stomachache::Exit(Chidi* pCat)
{
	SetTextColor(FOREGROUND_GREEN);
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Chidi goes to town.]";
}


bool Stomachache::OnMessage(Chidi* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for FixProblem
FixProblem* FixProblem::Instance()
{
	static FixProblem instance;

	return &instance;
}


void FixProblem::Enter(Chidi* pCat)
{
	//치디는 문제를 해결하러 마을로 간다.
	if (pCat->Location() != town)
	{
		SetTextColor(FOREGROUND_GREEN);
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Chidi fixes the problem.]";

		pCat->ChangeLocation(town);
	}
}


void FixProblem::Execute(Chidi* pCat)
{
	//문제를 고치기 위해 세가지 행동 중 하나를 한다.
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Pick up the trash.]";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Fix the wall.]";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Say hello to neighbors kindly.]";

		break;
	}

	pCat->GetFSM()->ChangeState(WritingThesis::Instance());
	//문제 해결 후 집으로, 상태는 논문 쓰기로 전환된다.

}


void FixProblem::Exit(Chidi* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": "
		<< "[Chidi goes home]";

	
}


bool FixProblem::OnMessage(Chidi* pCat, const Telegram& msg)
{

	//send msg to global message handler
	return false;
}
