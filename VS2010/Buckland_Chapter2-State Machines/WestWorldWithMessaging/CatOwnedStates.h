#ifndef CAT_OWNED_STATES_H
#define CAT_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   CatOwnedStates.h
//
//  고양이는 계속 잠을 잡니다.그러다 목이 마르면 집에 들어가 물을 마십니다.
//  집에 들어갈때, 엘사에게 인사를 합니다. 
//  물을 마셔 갈증이 해소되었다면, 다시 마당에 나가 잠을 잡니다.
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Cat;
struct Telegram;


class SleepAllDay : public State<Cat>   
{
private:

	SleepAllDay() {}

	//copy ctor and assignment should be private
	SleepAllDay(const SleepAllDay&);
	SleepAllDay& operator=(const SleepAllDay&);

public:

	//this is a singleton
	static SleepAllDay* Instance();

	virtual void Enter(Cat* miner);

	virtual void Execute(Cat* miner);

	virtual void Exit(Cat* miner);

	virtual bool OnMessage(Cat* agent, const Telegram& msg);

};

//------------------------------------------------------------------------

class VisitHomeGetWater : public State<Cat>
{
private:

	VisitHomeGetWater() {}

	//copy ctor and assignment should be private
	VisitHomeGetWater(const VisitHomeGetWater&);
	VisitHomeGetWater& operator=(const VisitHomeGetWater&);

public:

	//this is a singleton
	static VisitHomeGetWater* Instance();

	virtual void Enter(Cat* miner);

	virtual void Execute(Cat* miner);

	virtual void Exit(Cat* miner);

	virtual bool OnMessage(Cat* agent, const Telegram& msg);
};




#endif