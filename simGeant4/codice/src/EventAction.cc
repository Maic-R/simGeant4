#include "EventAction.hh"
#include "SpectrumHit.hh"

#include <G4AnalysisManager.hh>
#include <G4SDManager.hh>
#include <G4Event.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Neutron.hh>

void EventAction::BeginOfEventAction(const G4Event* ev)
{
  // Ntupla colonna 1 : ID dell'evento
  G4AnalysisManager::Instance()->FillNtupleIColumn(1, 0, ev->GetEventID());

  if( !(ev->GetEventID()%50000) )
    std::cout << "Event ID = " << ev->GetEventID() << std::endl;

  enInScintil = 0.;
  enInSilicon = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{

  // Ntupla colonne 3 e 5 : 
  G4AnalysisManager::Instance()->FillNtupleDColumn(1, 3, enInSilicon / MeV);
  G4AnalysisManager::Instance()->FillNtupleDColumn(1, 5, enInScintil / MeV);

  //G4cout << "enInSilicon: " << enInSilicon / MeV << G4endl;
  //G4cout << "enInScintil: " << enInScintil / MeV << G4endl;


  G4AnalysisManager::Instance()->AddNtupleRow(1);
  
}
