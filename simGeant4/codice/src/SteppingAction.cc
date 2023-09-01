#include "SteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include <G4Step.hh>
#include <G4Electron.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

SteppingAction::SteppingAction(EventAction* evtAct, G4String* mat) :
  fEvtAct(evtAct), fMaterial(mat)
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  auto aTrack = aStep->GetTrack();
  
  // "materiale prima" e "materiale dopo" servono per vedere quando un elettrone
  // cambia materiale 
  G4Material* backMaterial = aStep->GetPreStepPoint()->GetMaterial();
  G4Material* nextMaterial = aStep->GetPostStepPoint()->GetMaterial();

  if(backMaterial == nullptr || nextMaterial == nullptr)
    return;


  // Sr
  // SE Prima aria && poi Si && è una traccia dello Sr && è un elettrone 
  // metti nell'ntupla l'energia di arrivo al diodo
  if(backMaterial->GetName() == *fMaterial && nextMaterial->GetName() == "G4_Si" &&
     aTrack->GetParentID() == 1 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 2, aTrack->GetKineticEnergy() / MeV);

  // SE materiale prima != materiale dopo && dopo è Al (se c'è) && è una traccia dello Sr && è un elettrone
  // metti nell'ntupla l'energia di arrivo allo scintillatore
  //bool thereIsAl = DetectorConstruction::GetNfoils() != 0 ? nextMaterial->GetName() == "G4_Al" : true ;

  //if(backMaterial != nextMaterial && nextMaterial->GetName() == "G4_Al" && 
     //aTrack->GetParentID() == 1 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
    if( ( (backMaterial->GetName() == *fMaterial && nextMaterial->GetName() == "PVT") || 
        (backMaterial->GetName() == "G4_Al" && nextMaterial->GetName() == "PVT") ) &&
        aTrack->GetParentID() == 1 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 4, aTrack->GetKineticEnergy() / MeV);


  // Y
  if(backMaterial->GetName() == *fMaterial && nextMaterial->GetName() == "G4_Si" &&
     aTrack->GetParentID() == 2 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 7, aTrack->GetKineticEnergy() / MeV);


  //if(backMaterial != nextMaterial && nextMaterial->GetName() == "G4_Al" &&
     //aTrack->GetParentID() == 2 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
    if( ( (backMaterial->GetName() == *fMaterial && nextMaterial->GetName() == "PVT") || 
          (backMaterial->GetName() == "G4_Al" && nextMaterial->GetName() == "PVT") ) &&
        aTrack->GetParentID() == 2 && aTrack->GetParticleDefinition()->GetParticleName() == "e-")
      G4AnalysisManager::Instance()->FillNtupleDColumn(1, 8, aTrack->GetKineticEnergy() / MeV);

  if(backMaterial->GetName() == "G4_Si")
    fEvtAct->AddEnergySilicon(aStep->GetTotalEnergyDeposit());

  if(backMaterial->GetName() == "PVT")
    fEvtAct->AddEnergyScintil(aStep->GetTotalEnergyDeposit());
}
