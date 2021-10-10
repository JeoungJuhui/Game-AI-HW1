#include "ChidiOwnedStates.h"  // ġ��
#include "fsm/State.h"
#include "Chidi.h"   // ġ��
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
	//ġ��� ������ �׻� ���� ����.
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
	//�������� ���� ������ ġ��� �����ϰ� �� ���� ���� �����.
}


bool WritingThesis::OnMessage(Chidi* pCat, const Telegram& msg)
{
	//�����ʿ��� ���ʹ޶�� �޼����� �޴´�.
	if (msg.Msg == Msg_Helpme_Chidi)
	{

		cout << "\nMessage handled by " << GetNameOfEntity(pCat->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN);

		//�������� �޼����� ���� ġ���� ����.
		cout << "\n" << GetNameOfEntity(pCat->ID()) <<
			": What did you say?";

		//�������� ��Ҹ��� ������ �谡 ����(Stomachache) ���·� ��ȯ�ȴ�.
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
	
	// �޼��� �ڵ� EleanorOwnedStates.cpp ������ 208��°��
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : ġ��
		ent_Eleanor,            //ID of recipient : �����ʸ� �θ���.
		Msg_Be_careful_Eleanor,   //the message           : �޼��� ����
		NO_ADDITIONAL_INFO);

	pCat->GetFSM()->ChangeState(FixProblem::Instance()); //�����ʿ��� ���� �� ������ ��ġ�� ���·� ��ȯ.

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
	//ġ��� ������ �ذ��Ϸ� ������ ����.
	if (pCat->Location() != town)
	{
		SetTextColor(FOREGROUND_GREEN);
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Chidi fixes the problem.]";

		pCat->ChangeLocation(town);
	}
}


void FixProblem::Execute(Chidi* pCat)
{
	//������ ��ġ�� ���� ������ �ൿ �� �ϳ��� �Ѵ�.
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
	//���� �ذ� �� ������, ���´� �� ����� ��ȯ�ȴ�.

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
