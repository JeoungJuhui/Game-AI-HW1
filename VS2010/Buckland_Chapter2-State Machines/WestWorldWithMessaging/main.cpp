// B877033 JJH
// <Game AI Fall 2021 Homework#1>
// Make FSM based script

// Netflix drama GoodPlace S1
// Charactor: Eleanor, Chidi, Michael

#include <fstream>
#include <time.h>
#include <string.h>

#include "Locations.h"

#include "Eleanor.h"
#include "Chidi.h"
#include "Michael.h"

#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));


  Eleanor* mEleanor = new Eleanor(ent_Eleanor);
  Chidi* mChidi = new Chidi(ent_Chidi);
  Michael* mMichael = new Michael(ent_Michael);


  //register them with the entity manager

  EntityMgr->RegisterEntity(mEleanor);
  EntityMgr->RegisterEntity(mChidi);
  EntityMgr->RegisterEntity(mMichael);



  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 

    mEleanor->Update();
    mChidi->Update();
    mMichael->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }


  printf("\n\n\nEleanor: OMG! I knew it! this is the Badplace!\n\n");

  //tidy up

  delete mEleanor;
  delete mChidi;
  delete mMichael;


  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






