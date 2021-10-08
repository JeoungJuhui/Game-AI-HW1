#ifndef CAT_H
#define CAT_H

//------------------------------------------------------------------------
//
//  Name:   Cat.h
//
//  Desc:   A class defining a cat.
//
//
//------------------------------------------------------------------------


#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "CatOwnedStates.h"    //고양이 States 추가!
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

const int Thirst_Cat = 5;


class Cat : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Cat>*  m_pStateMachine;

	location_type         m_Location;

	//int                   m_iThirst;   //로그 찍기 위해 아래 public으로 옮김

public:

	Cat(int id) :m_Location(yard),
		m_iThirst(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Cat>(this);

		m_pStateMachine->SetCurrentState(SleepAllDay::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Cat() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Cat>* GetFSM()const { return m_pStateMachine; }

	int                   m_iThirst;

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Thirsty()const;
	void          DrinkWater() { m_iThirst = 0; }

};



#endif

