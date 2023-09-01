#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include <G4VUserActionInitialization.hh>
#include <G4String.hh>

class ActionInitialization : public G4VUserActionInitialization
{
public:
    void Build() const override;

    ActionInitialization(G4String* mat) {fMaterial = mat;}

    void BuildForMaster() const override;   

private:
    G4String* fMaterial = nullptr;
};

#endif