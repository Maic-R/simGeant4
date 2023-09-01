#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include <G4UserSteppingAction.hh>
#include <G4String.hh>

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    //! constructor
    SteppingAction(EventAction* , G4String*);

    void UserSteppingAction(const G4Step*) override;

private:
    EventAction* fEvtAct = nullptr;
    G4String* fMaterial = nullptr;

};

#endif
