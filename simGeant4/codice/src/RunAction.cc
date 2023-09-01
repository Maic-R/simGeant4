#include "RunAction.hh"

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

// Task 4c.3: Include the necessary Analysis.hh

RunAction::RunAction() :
  G4UserRunAction()
{}


void RunAction::BeginOfRunAction(const G4Run*)
{
  auto man = G4AnalysisManager::Instance();

  // Ntuple with output.
  man->SetFirstNtupleId(1);
  man->CreateNtuple("dataOut", "DataOut");
  man->CreateNtupleIColumn("evID");
  man->CreateNtupleDColumn("enGen"); 
  man->CreateNtupleDColumn("enDiode");
  man->CreateNtupleDColumn("enDepSi");
  man->CreateNtupleDColumn("enScint");
  man->CreateNtupleDColumn("enDepScint");

  man->CreateNtupleDColumn("enGen_Y");
  man->CreateNtupleDColumn("enDiode_Y");
  man->CreateNtupleDColumn("enScint_Y");
  man->FinishNtuple();

  man->OpenFile("../../simAnalysis/sim_1_5mmCol.root");

}

void RunAction::EndOfRunAction(const G4Run*)
{
  // Write and save file properly.
  auto man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();
  
}

RunAction::~RunAction()
{}