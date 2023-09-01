#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4SystemOfUnits.hh>

class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    // Main method that has to be overridden in all detectors
    // You will edit this method in Tasks 1a & 1b
    G4VPhysicalVolume* Construct() override;

    DetectorConstruction(G4String* mat) {fMaterial = mat;}

    // Task 1c.1: Uncomment the declaration of this method
    void ConstructSDandField() override;

    static unsigned int fNfoils;

    static unsigned int GetNfoils() { return fNfoils;}

private:

    G4double fCollDiameter = 5.05 * mm;
    G4String* fMaterial = nullptr;
};

#endif