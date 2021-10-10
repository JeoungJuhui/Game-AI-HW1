#include "EleanorOwnedStates.h"  // ������
#include "fsm/State.h"
#include "Eleanor.h"   // ������
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
	// �����ʴ� ������ ��� ���� ���θ� �Ѵ�.
	if (pCat->Location() != home)
	{
		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor is studying ethics.]";

		pCat->ChangeLocation(home);
	}
}


void StudyEthics::Execute(Eleanor* pCat)
{
	// å�� �аų�, ������ ���� �̾߱��ϰų�, ġ���� ���Ǹ� ��´�.


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
	//����Ŭ�� ��Ҹ��� ������ ������ ���Ѵ�.
}


bool StudyEthics::OnMessage(Eleanor* pCat, const Telegram& msg)
{
	if (msg.Msg== Msg_Helpme_Eleanor)
	{

		cout << "\nMessage handled by " << GetNameOfEntity(pCat->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(0x000f);

		// ����Ŭ�� �޼����� ���� �������� ����
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
	// ������ ��� �̵�
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
		pCat->GetFSM()->ChangeState(Regret::Instance()); //�̱����� �ൿ�� �� ��, �ݼ� ���·� ��ȯ.

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(pCat->ID()) << ": It... It's not my fault!";
		pCat->GetFSM()->ChangeState(StudyEthics::Instance()); //�̱����� �ൿ�� �� ��, ����, ������.

		break;
	}
}


void DoSelfish::Exit(Eleanor* pCat)
{
	cout << "\n" << GetNameOfEntity(pCat->ID()) << ": " << "[Eleanor runs to home]";
	//ġ�� ������ ����.
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
	// ������ ��� �̵�
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

	// �����ʰ� ġ�� �θ���.
	// �޼��� �ڵ� ChidiOwnedStates.cpp ������ 71��°��
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pCat->ID(),        //ID of sender      : �����ʰ� 
		ent_Chidi,            //ID of recipient : ġ�� �θ���.
		Msg_Helpme_Chidi,   //the message           : �޼��� ����
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

		// ġ���� �޼����� ���� ������ ����
		cout << "\n" << GetNameOfEntity(pCat->ID()) <<
			": Ok, dude. I can be a good man.";

		pCat->GetFSM()->ChangeState(StudyEthics::Instance());

		return true;

	}
	//send msg to global message handler
	return false;
}