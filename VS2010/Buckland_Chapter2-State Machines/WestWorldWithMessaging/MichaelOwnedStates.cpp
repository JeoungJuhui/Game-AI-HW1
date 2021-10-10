#include "MichaelOwnedStates.h"  // ����Ŭ
#include "fsm/State.h"
#include "Michael.h"   // ����Ŭ
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
	// ����Ŭ�� ��ȹ�� �ϼ��� ������ �繫�ǿ��� ��ȹ�� ����ϴ�.
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
	//��ȹ�� �ϼ��Ǹ� ������ ���� ������ ����ϴ�.

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
	// ������ �̵��Ѵ�.
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


		// ����Ŭ�� �����ʸ� �θ���.
		// �޼��� �ڵ� EleanorOwnedStates.cpp ������ 86��°�� ����
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pCat->ID(),        //ID of sender      : ����Ŭ�� 
			ent_Eleanor,            //ID of recipient : �����ʸ� �θ���.
			Msg_Helpme_Eleanor,   //the message           : �޼��� ����
			NO_ADDITIONAL_INFO);

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael smiles wickedly.]";
		pCat->GetFSM()->ChangeState(ReportToBoss::Instance()); //�����ʸ� �θ� �� ��翡�� �����ϴ� ������ȯ.

		break;
	
	case 1:

		//��ȹ�� �����Ѵ�.
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Michael ruined the plan.]";

		pCat->GetFSM()->ChangeState(MakePlan::Instance()); //�ٽ� ��ȹ�� �����.
		pCat->SetTrap();

		break;
	}
	//������ �����.

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

	pCat->GetFSM()->ChangeState(MakePlan::Instance()); //��翡�� ������ ��, �ٽ� ��ȹ�� ����� ������ ���� ��ȯ.

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
