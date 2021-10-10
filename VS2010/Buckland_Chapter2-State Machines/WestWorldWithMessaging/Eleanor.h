#ifndef Eleanor_H
#define Eleanor_H

//------------------------------------------------------------------------
//
//  Name:   Eleanor.h
//
//  Desc:   A class defining a Eleanor.
//
//
//------------------------------------------------------------------------


#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "EleanorOwnedStates.h"//¿¤¸®³Ê States Ãß°¡!
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;



class Eleanor : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Eleanor>* m_pStateMachine;

	location_type         m_Location;


public:

	Eleanor(int id) :m_Location(home),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Eleanor>(this);

		m_pStateMachine->SetCurrentState(StudyEthics::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Eleanor() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Eleanor>* GetFSM()const { return m_pStateMachine; }


	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }



};



#endif

