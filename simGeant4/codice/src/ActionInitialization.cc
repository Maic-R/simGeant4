#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
//! Optional user classes
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
// Task 4a.2: Include the header for SteppingAction
// Task 4c.2: Include the header for EventAction

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
    
    auto evtAct = new EventAction();

    /* These two classes are used only in task3-4.*/
    SetUserAction(new RunAction());
    SetUserAction(evtAct);
    SetUserAction(new SteppingAction(evtAct, fMaterial));
    SetUserAction(new StackingAction());
}

void ActionInitialization::BuildForMaster() const
{
  // By default, don't do anything. This applies only in MT mode:
  SetUserAction(new RunAction());
}
