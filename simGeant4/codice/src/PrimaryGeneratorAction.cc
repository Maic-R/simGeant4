#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>

// Task 2b.1 Include the proper header file for GPS
#include <G4GeneralParticleSource.hh>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGun = new G4ParticleGun();
    G4ParticleDefinition* electron = G4ParticleTable::GetParticleTable()->FindParticle("e-");

    fGun->SetParticleDefinition(electron);
    fGun->SetParticleEnergy(1. * MeV); // cioè stiamo generando elettroni da 1 MeV?
    fGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));  // along z
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{    

    // posizione iniziale
    G4double dx0 = 5.05 * mm / 2;
    G4double dist = G4UniformRand() * dx0;
    G4double angl = G4UniformRand() * 2 * M_PI;
    G4double x0 = dist * cos(angl);
    G4double y0 = dist * sin(angl);
    G4double z0 = 0.;

    //G4double x0 = 0.;
    //G4double y0 = 0.;
    //G4double z0 = 0.;

    fGun->SetParticlePosition({x0, y0, z0});
    
    fGun->GeneratePrimaryVertex(anEvent);

}
