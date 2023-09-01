#include <G4UserEventAction.hh>
#include "globals.hh"


class EventAction : public G4UserEventAction
{
public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void AddEnergySilicon(G4double en) {enInSilicon += en;}
  void AddEnergyScintil(G4double en) {enInScintil += en;}

private:

  G4double enInSilicon = 0;
  G4double enInScintil = 0;
};