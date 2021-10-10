#ifndef Chidi_OWNED_STATES_H
#define Chidi_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   ChidiOwnedStates.h
//
//	ġ��� ���� ���� �� �׻� ���� �ۼ��մϴ�. --------------WritingThesis
//  �����ʸ� ���� ������ ������ �����ϰ� �谡 ���Ŵϴ�. -------Stomachache
//  �����ʰ� �ݼ��ϰ� ������ ���ư��� ������ �ذ��մϴ�. ------FixProblem
// 
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Chidi;
struct Telegram;


class WritingThesis : public State<Chidi>
{
private:

	WritingThesis() {}

	//copy ctor and assignment should be private
	WritingThesis(const WritingThesis&);
	WritingThesis& operator=(const WritingThesis&);

public:

	//this is a singleton
	static WritingThesis* Instance();

	virtual void Enter(Chidi* miner);

	virtual void Execute(Chidi* miner);

	virtual void Exit(Chidi* miner);

	virtual bool OnMessage(Chidi* agent, const Telegram& msg);

};

//------------------------------------------------------------------------

class Stomachache : public State<Chidi>
{
private:

	Stomachache() {}

	//copy ctor and assignment should be private
	Stomachache(const Stomachache&);
	Stomachache& operator=(const Stomachache&);

public:

	//this is a singleton
	static Stomachache* Instance();

	virtual void Enter(Chidi* miner);

	virtual void Execute(Chidi* miner);

	virtual void Exit(Chidi* miner);

	virtual bool OnMessage(Chidi* agent, const Telegram& msg);
};

//------------------------------------------------------------------------

class FixProblem : public State<Chidi>
{
private:

	FixProblem() {}

	//copy ctor and assignment should be private
	FixProblem(const FixProblem&);
	FixProblem& operator=(const FixProblem&);

public:

	//this is a singleton
	static FixProblem* Instance();

	virtual void Enter(Chidi* miner);

	virtual void Execute(Chidi* miner);

	virtual void Exit(Chidi* miner);

	virtual bool OnMessage(Chidi* agent, const Telegram& msg);
};


#endif