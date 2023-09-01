#include "StackingAction.hh"
#include "RunAction.hh"

#include <G4SystemOfUnits.hh>
#include "G4AnalysisManager.hh"

StackingAction::StackingAction() :
  G4UserStackingAction()
{;}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack (const G4Track*
 aTrack)
{

  // traccia elettroni generati da Sr
  if(aTrack->GetParentID() == 1 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 1, aTrack->GetKineticEnergy() / MeV);

  // traccia elettroni generati da Y
  if(aTrack->GetParentID() == 2 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 6, aTrack->GetKineticEnergy() / MeV);

  // Do not affect track classification. Just return what would have
  // been returned by the base class
  return G4UserStackingAction::ClassifyNewTrack(aTrack);
}
