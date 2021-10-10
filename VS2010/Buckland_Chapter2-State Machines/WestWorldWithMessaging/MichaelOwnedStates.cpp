#include "MichaelOwnedStates.h"  // 마이클
#include "fsm/State.h"
#include "Michael.h"   // 마이클
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


//------------------------------------------------------------------------methods for MakePlan
MakePlan* MakePlan::Instance()
{
	static MakePlan instance;

	return &instance;
}


void MakePlan::Enter(Michael* pCat)
{
	// 마이클은 계획이 완성될 때까지 사무실에서 계획을 세웁니다.
	if (pCat->Location() != office)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael is making plan.]";

		pCat->ChangeLocation(office);
	}
}


void MakePlan::Execute(Michael* pCat)
{

	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "Aha! I have an idea!" << ", m_plan: " << pCat->m_plan<<"/5";

	if (pCat->Planning())
	{
		pCat->GetFSM()->ChangeState(DoPlan::Instance());
	}
	//계획이 완성되면 밖으로 나가 함정을 만듭니다.

}


void MakePlan::Exit(Michael* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": "
		<< "[Michael goes to town.]";
}


bool MakePlan::OnMessage(Michael* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for DoPlan

DoPlan* DoPlan::Instance()
{
	static DoPlan instance;

	return &instance;
}

void DoPlan::Enter(Michael* pCat)
{
	// 마을로 이동한다.
	if (pCat->Location() != town)
	{

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael is making trap with Janet.]"; 
		pCat->ChangeLocation(town);
	}

}


void DoPlan::Execute(Michael* pCat)
{

	switch (RandInt(0,1))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael calls Eleanor.]";


		// 마이클이 엘리너를 부른다.
		// 메세지 핸들 EleanorOwnedStates.cpp 파일의 86번째줄 참조
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pCat->ID(),        //ID of sender      : 마이클이 
			ent_Eleanor,            //ID of recipient : 엘리너를 부른다.
			Msg_Helpme_Eleanor,   //the message           : 메세지 내용
			NO_ADDITIONAL_INFO);

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael smiles wickedly.]";
		pCat->GetFSM()->ChangeState(ReportToBoss::Instance()); //엘리너를 부른 뒤 상사에게 보고하는 상태전환.

		break;
	
	case 1:

		//계획이 실패한다.
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael ruined the plan.]";

		pCat->GetFSM()->ChangeState(MakePlan::Instance()); //다시 계획을 세운다.
		pCat->SetTrap();

		break;
	}
	//함정을 만든다.

}


void DoPlan::Exit(Michael* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael goes to the office.]";

	SetTextColor(FOREGROUND_RED);


}


bool DoPlan::OnMessage(Michael* pCat, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for ReportToBoss

ReportToBoss* ReportToBoss::Instance()
{
	static ReportToBoss instance;

	return &instance;
}

void ReportToBoss::Enter(Michael* pCat)
{
	if (pCat->Location() != office)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael goes to his office.]";

		pCat->ChangeLocation(office);
	}

}

void ReportToBoss::Execute(Michael* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael reports his trap to boss, Shone.]";
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Shone is satisfied.]";

	pCat->GetFSM()->ChangeState(MakePlan::Instance()); //상사에게 보고한 뒤, 다시 계획을 세우는 것으로 상태 전환.

}

void ReportToBoss::Exit(Michael* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael needs new plan.]";
	pCat->SetTrap();

}

bool ReportToBoss::OnMessage(Michael* pCat, const Telegram& msg)
{
	return false;

}
