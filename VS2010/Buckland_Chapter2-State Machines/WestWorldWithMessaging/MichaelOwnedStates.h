#ifndef Michael_OWNED_STATES_H
#define Michael_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MichaelOwnedStates.h
//
//  ����Ŭ�� �繫�ǿ��� ��ȹ�� ����ϴ�. -------------MakePlan
//  ��ȹ�� ��� �ϼ��Ǹ�(5) ��ȹ�� �����մϴ�. -------DoPlan
//  �����ʸ� �θ��� Boss���� �����մϴ�. -------------ReportToBoss
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Michael;
struct Telegram;


class MakePlan : public State<Michael>
{
private:

	MakePlan() {}

	//copy ctor and assignment should be private
	MakePlan(const MakePlan&);
	MakePlan& operator=(const MakePlan&);

public:

	//this is a singleton
	static MakePlan* Instance();

	virtual void Enter(Michael* miner);

	virtual void Execute(Michael* miner);

	virtual void Exit(Michael* miner);

	virtual bool OnMessage(Michael* agent, const Telegram& msg);

};

//------------------------------------------------------------------------

class DoPlan : public State<Michael>
{
private:

	DoPlan() {}

	//copy ctor and assignment should be private
	DoPlan(const DoPlan&);
	DoPlan& operator=(const DoPlan&);

public:

	//this is a singleton
	static DoPlan* Instance();

	virtual void Enter(Michael* miner);

	virtual void Execute(Michael* miner);

	virtual void Exit(Michael* miner);

	virtual bool OnMessage(Michael* agent, const Telegram& msg);
};

class ReportToBoss : public State<Michael>
{
private:

	ReportToBoss() {}

	//copy ctor and assignment should be private
	ReportToBoss(const ReportToBoss&);
	ReportToBoss& operator=(const ReportToBoss&);

public:

	//this is a singleton
	static ReportToBoss* Instance();

	virtual void Enter(Michael* miner);

	virtual void Execute(Michael* miner);

	virtual void Exit(Michael* miner);

	virtual bool OnMessage(Michael* agent, const Telegram& msg);
};





#endif