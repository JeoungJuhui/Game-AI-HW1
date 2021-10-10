#ifndef Michael_H
#define Michael_H

//------------------------------------------------------------------------
//
//  Name:   Michael.h
//
//  Desc:   A class defining a Michael.
//
//
//------------------------------------------------------------------------


#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "MichaelOwnedStates.h"//마이클 States 추가!
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

const int Plan_Complete = 5;


class Michael : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Michael>* m_pStateMachine;

	location_type         m_Location;


public:

	Michael(int id) :m_Location(office),
		
		m_plan(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Michael>(this);

		m_pStateMachine->SetCurrentState(MakePlan::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Michael() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Michael>* GetFSM()const { return m_pStateMachine; }

	int                   m_plan;

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Planning()const;
	void          SetTrap() { m_plan = 0; }


};



#endif