#ifndef Chidi_H
#define Chidi_H

//------------------------------------------------------------------------
//
//  Name:   Chidi.h
//
//  Desc:   A class defining a Chidi.
//
//
//------------------------------------------------------------------------


#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "ChidiOwnedStates.h"//치디 States 추가!
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;



class Chidi : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Chidi>* m_pStateMachine;

	location_type         m_Location;


public:

	Chidi(int id) :m_Location(home),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Chidi>(this);

		m_pStateMachine->SetCurrentState(WritingThesis::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Chidi() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Chidi>* GetFSM()const { return m_pStateMachine; }

	int                   m_iThirst;

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }



};



#endif