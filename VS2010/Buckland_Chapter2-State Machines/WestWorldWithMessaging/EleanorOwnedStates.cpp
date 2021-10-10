#include "EleanorOwnedStates.h"  // 엘리너
#include "fsm/State.h"
#include "Eleanor.h"   // 엘리너
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




//------------------------------------------------------------------------methods for StudyEthics
StudyEthics* StudyEthics::Instance()
{
	static StudyEthics instance;

	return &instance;
}


void StudyEthics::Enter(Eleanor* pCat)
{
	// 엘리너는 집에서 계속 윤리 공부를 한다.
	if (pCat->Location() != home)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor is studying ethics.]";

		pCat->ChangeLocation(home);
	}
}


void StudyEthics::Execute(Eleanor* pCat)
{
	// 책을 읽거나, 윤리에 대해 이야기하거나, 치디의 강의를 듣는다.


	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Reading ethic books.]";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Talk about ethics.]";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": [Attend chidi's lecture.]";

		break;
	}


}


void StudyEthics::Exit(Eleanor* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": "
		<< "[Eleanor goes to town.]";
	//마이클의 목소리를 들으면 마을로 향한다.
}


bool StudyEthics::OnMessage(Eleanor* pCat, const Telegram& msg)
{
	if (msg.Msg== Msg_Helpme_Eleanor)
	{

		cout << "\nMessage handled by " << GetNameOfEntity(pCat->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(0x000f);

		// 마이클의 메세지를 받은 엘리너의 반응
		cout << "\n" << GetNameOfEntity(pCat->ID()) <<
			": OK, I'm going!";

		pCat->GetFSM()->ChangeState(DoSelfish::Instance());

		return true;

	}
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for DoSelfish

DoSelfish* DoSelfish::Instance()
{
	static DoSelfish instance;

	return &instance;
}

void DoSelfish::Enter(Eleanor* pCat)
{
	// 마을로 장소 이동
	if (pCat->Location() != town)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor is walking around the town.]";

		pCat->ChangeLocation(town);
	}


}

void DoSelfish::Execute(Eleanor* pCat)
{

	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor does something selfish.]";
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor makes problem!]";
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[THE TOWN IS GOING TO BREAK!]";

	switch (RandInt(0, 1))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": I have to meet Chidi!";
		pCat->GetFSM()->ChangeState(Regret::Instance()); //이기적인 행동을 한 뒤, 반성 상태로 전환.

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": It... It's not my fault!";
		pCat->GetFSM()->ChangeState(StudyEthics::Instance()); //이기적인 행동을 한 뒤, 도망, 집으로.

		break;
	}
}


void DoSelfish::Exit(Eleanor* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor runs to home]";
	//치디를 만나러 간다.
}


bool DoSelfish::OnMessage(Eleanor* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for Regret

Regret* Regret::Instance()
{
	static Regret instance;

	return &instance;
}

void Regret::Enter(Eleanor* pCat)
{
	// 집으로 장소 이동
	if (pCat->Location() != home)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor meets Chidi.]";

		pCat->ChangeLocation(home);
	}


}


void Regret::Execute(Eleanor* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "Chidi! The town is breaking down!";
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "I guess I acted selfishly again!";

	// 엘리너가 치디를 부른다.
	// 메세지 핸들 ChidiOwnedStates.cpp 파일의 71번째줄
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : 엘리너가 
		ent_Chidi,            //ID of recipient : 치디를 부른다.
		Msg_Helpme_Chidi,   //the message           : 메세지 내용
		NO_ADDITIONAL_INFO);

}


void Regret::Exit(Eleanor* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor gose to study.]";
}


bool Regret::OnMessage(Eleanor* pCat, const Telegram& msg)
{
	if (msg.Msg == Msg_Be_careful_Eleanor)
	{

		cout << "\nMessage handled by " << GetNameOfEntity(pCat->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(0x000f);

		// 치디의 메세지를 받은 엘사의 반응
		cout << "\n" << GetNameOfEntity(pCat->ID()) <<
			": Ok, dude. I can be a good man.";

		pCat->GetFSM()->ChangeState(StudyEthics::Instance());

		return true;

	}
	//send msg to global message handler
	return false;
}