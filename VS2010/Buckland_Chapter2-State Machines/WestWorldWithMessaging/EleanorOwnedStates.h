#ifndef Eleanor_OWNED_STATES_H
#define Eleanor_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   EleanorOwnedStates.h
//
//  �����ʴ� ������ �׻� ���� ���θ� �մϴ�. ----------------------StudyEthics
//  ����Ŭ�� ������ ��û�� ������ ������, �̱����� �ൿ�� �մϴ�. ---DoSelfish
//  ġ�� ���� ġ���� ���� ������ �ݼ��մϴ�. ---------------------Regret
// 
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Eleanor;
struct Telegram;


class StudyEthics : public State<Eleanor>
{
private:

	StudyEthics() {}

	//copy ctor and assignment should be private
	StudyEthics(const StudyEthics&);
	StudyEthics& operator=(const StudyEthics&);

public:

	//this is a singleton
	static StudyEthics* Instance();

	virtual void Enter(Eleanor* miner);

	virtual void Execute(Eleanor* miner);

	virtual void Exit(Eleanor* miner);

	virtual bool OnMessage(Eleanor* agent, const Telegram& msg);

};

//------------------------------------------------------------------------

class DoSelfish : public State<Eleanor>
{
private:

	DoSelfish() {}

	//copy ctor and assignment should be private
	DoSelfish(const DoSelfish&);
	DoSelfish& operator=(const DoSelfish&);

public:

	//this is a singleton
	static DoSelfish* Instance();

	virtual void Enter(Eleanor* miner);

	virtual void Execute(Eleanor* miner);

	virtual void Exit(Eleanor* miner);

	virtual bool OnMessage(Eleanor* agent, const Telegram& msg);
};

//------------------------------------------------------------------------

class Regret : public State<Eleanor>
{
private:

	Regret() {}

	//copy ctor and assignment should be private
	Regret(const Regret&);
	Regret& operator=(const Regret&);

public:

	//this is a singleton
	static Regret* Instance();

	virtual void Enter(Eleanor* miner);

	virtual void Execute(Eleanor* miner);

	virtual void Exit(Eleanor* miner);

	virtual bool OnMessage(Eleanor* agent, const Telegram& msg);
};


#endif