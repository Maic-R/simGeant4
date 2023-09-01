#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Tubs.hh>
#include <G4Box.hh>
#include <G4SDManager.hh>

#include "DetectorConstruction.hh"
#include "SpectrumDetector.hh"

#include <sstream>

unsigned int DetectorConstruction::fNfoils = 0;


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Mondo fisico della simulazione
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeX = 1 * m;
    G4double worldSizeY = 1 * m;
    G4double worldSizeZ = 1 * m;

    // We have created the world volume for you
    // As with all volumes, it requires three steps: 
    // Solid volume, logical volume and physical volume

    // 1) Solid
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // 2) Logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, nist->FindOrBuildMaterial(*fMaterial), "world");
    G4VisAttributes* visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);
    worldLog->SetVisAttributes(visAttr);

    // 3) Physical volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    // Materials:
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
    G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* iron = nist->FindOrBuildMaterial("G4_Fe");

    G4Element* H = new G4Element("Hydrogen", "H", 1., 1.01*g/mole);
    G4Element* C = new G4Element("Carbon", "C", 6., 12.00*g/mole);
    G4Material* PVT = new G4Material("PVT", 1.032 * g/cm2, 2);
    PVT->AddElement(H, 9);
    PVT->AddElement(C, 10);


    // Collimator
    G4VSolid* collimatorBox = new G4Tubs("collimatorSolid", 
                                     fCollDiameter / 2.,
                                     5 * cm,
                                     1.5 * cm / 2.,
                                     0,
                                     2 * M_PI);

    
    G4LogicalVolume* collimatorLog = new G4LogicalVolume(collimatorBox, lead, "collimatorLog");

    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0.85*cm),
			  collimatorLog, "collimatorPhys", worldLog, 0, 0);

    G4VisAttributes* grey = new G4VisAttributes(G4Colour::Grey());
    grey->SetVisibility(true);
    grey->SetForceSolid(true);
    collimatorLog->SetVisAttributes(grey);

    // Backside disk
    G4VSolid* backsideBox = new G4Tubs("collimatorSolid", 
                                     0.0 * mm,
                                     5 * cm,
                                     1.5 * cm / 2.,
                                     0,
                                     2 * M_PI);

    
    G4LogicalVolume* backsideLog = new G4LogicalVolume(backsideBox, lead, "backsideLog");

    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -0.85*cm),
			  backsideLog, "backsidePhys", worldLog, 0, 0);

    backsideLog->SetVisAttributes(grey);

    // Anulus
    G4VSolid* anulusBox = new G4Tubs("anulusSolid", 
                                     fCollDiameter / 2.,
                                     5 * cm,
                                     0.2 * cm / 2.,
                                     0,
                                     2 * M_PI);

    
    G4LogicalVolume* anulusLog = new G4LogicalVolume(anulusBox, lead, "anulusLog");

    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0),
			  anulusLog, "anulusPhys", worldLog, 0, 0);

    anulusLog->SetVisAttributes(grey);

    


    // Diodo
    G4VSolid* diodeBox = new G4Box("diodeSolid", 8 * mm / 2, 8 * mm / 2, 300 * um / 2);
    G4LogicalVolume* diodeLog = new G4LogicalVolume(diodeBox, silicon, "diodeLog");
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 1.6*cm + 2.82 * cm + 300 * um / 2.0),
			  diodeLog, "diodePhys", worldLog, 0, 0);

    G4VisAttributes* yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    yellow->SetForceSolid(true);
    diodeLog->SetVisAttributes(yellow);

    G4double collThickness = 1.5 * mm;
    
    // Collimatore post diodo
    G4VSolid* postCollimatorBox = new G4Tubs("postCollimatorSolid",
                                     3.0 * mm / 2.,
                                     1.6 * cm,
                                     collThickness / 2.,
                                     0,
                                     2 * M_PI);

    
    G4LogicalVolume* postCollimatorLog = new G4LogicalVolume(postCollimatorBox, steel, "postCollimatorLog");

    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 1.6*cm + 2.82 * cm + 300 * um / 2.0 + 3 * mm / 2.),
			  postCollimatorLog, "postCollimatorPhys", worldLog, 0, 0);

    G4VisAttributes* whiteColl = new G4VisAttributes(G4Colour::White());
    whiteColl->SetVisibility(false);
    whiteColl->SetForceSolid(true);
    postCollimatorLog->SetVisAttributes(whiteColl);

    
    //G4double boxSizeX = 4.0 * cm;
    //G4double boxSizeY = 2.0 * cm;
    //G4double boxSizeZ = 0.3 * cm;
    //G4double holeRadius = 3 * mm;

    //G4Box* outerBox = new G4Box("OuterBox", boxSizeX/2., boxSizeY/2., boxSizeZ/2.);
    //G4LogicalVolume* outerLogical = new G4LogicalVolume(outerBox, steel, "OuterLogical");
    //new G4PVPlacement(0, G4ThreeVector(0,0,1.6*cm + 2.82 * cm + 300 * um / 2.0 + boxSizeZ / 2.), outerLogical, "OuterPhysical", worldLog, false, 0);

    //// Create the cylindrical hole
    //G4Tubs* hole = new G4Tubs("Hole", holeRadius/2., 4/2. * mm, boxSizeZ/2., 0, 360 * deg);
    //G4LogicalVolume* holeLogical = new G4LogicalVolume(hole, steel, "HoleLogical");
    //new G4PVPlacement(0, G4ThreeVector(0,0,1.6*cm + 2.82 * cm + 300 * um / 2.0 + boxSizeZ / 2.), holeLogical, "HolePhysical", worldLog, false, 0);

    // Place the steel ring inside the hole
    //G4Tubs* steelRing = new G4Tubs("SteelRing", (holeRadius - 0.1)/2. * mm, holeRadius/2., boxSizeZ/2., 0, 360 * deg);
    //G4LogicalVolume* steelLogical = new G4LogicalVolume(steelRing, steel, "SteelLogical");
    //new G4PVPlacement(0, G4ThreeVector(0,0,1.6*cm + 2.82 * cm + 300 * um / 2.0 + boxSizeZ / 2.), steelLogical, "SteelPhysical", worldLog, false, 0);


    // Fogli alluminio
    G4VSolid* aluminumBox = new G4Tubs("aluminumSolid", 
                                     0.,
                                     4.72 * cm / 2.,
                                     0.103 * mm / 2.,
                                     0,
                                     2 * M_PI);

    
    G4LogicalVolume* aluminumLog = new G4LogicalVolume(aluminumBox, aluminum, "aluminumLog");
    G4VisAttributes* white = new G4VisAttributes(G4Colour::White());
    white->SetVisibility(true);
    white->SetForceSolid(true);
    aluminumLog->SetVisAttributes(white);

    // primo piano di alluminio
    G4double Alluminio_basso = 1.6*cm + 2.82 * cm + 300 * um + 3.0 * cm - 0.103 * mm / 2.;

    for(unsigned int i = 0 ; i < fNfoils; ++i)
    {
        new G4PVPlacement(nullptr, G4ThreeVector(0, 0, Alluminio_basso - 0.103 * mm * i),
	    		  aluminumLog, "aluminumPhys", worldLog, i, 0);        
    }

    // Scint
    G4VSolid* scintBox = new G4Box("scintSolid", 4 * cm / 2, 1.0 * cm / 2, 0.5 * cm / 2);

    G4LogicalVolume* scintLog = new G4LogicalVolume(scintBox, PVT, "scintLog");
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 1.6*cm + 2.82 * cm + 300 * um + 3.0 * cm + 0.5 * cm / 2.),
			  scintLog, "scintPhys", worldLog, 0, 0);

    G4VisAttributes* cyan = new G4VisAttributes(G4Colour::Cyan());
    cyan->SetVisibility(true);
    cyan->SetForceSolid(true);
    scintLog->SetVisAttributes(cyan);

    
    
    // The Construct() method has to return the final (physical) world volume:
    return worldPhys;
}

void DetectorConstruction::ConstructSDandField()
{
    // Task 1c.1: Create the magnetic field messenger

/*
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    sdManager->SetVerboseLevel(2);  // Useful for 4c

    // Task 4c.1: Create 2 instances of G4MultiFunctionalDetector (for absorber and scintillator)
    SpectrumDetector* neutronDetector = new SpectrumDetector("neutronDetector", "SpectrumHC");

    G4SDManager* sdMan =G4SDManager::GetSDMpointer();
    sdMan->AddNewDetector(neutronDetector);

    SetSensitiveDetector("scorerLog", neutronDetector);
*/

    // Task 4c.1: Create 2 primitive scorers for the dose and assign them to respective detectors
    // G4VPrimitiveScorer* absorberScorer = ...

    // Task 4c.1 Assign multi-functional detectors to the logical volumes and register them to 
    //   the SDmanager
    // SetSensitiveDetector("....");
    // sdManager->AddNewDetector(...);

    // Task 4d.2: Comment out the attachment of previous sensitive detectors
    // Task 4d.2: Create and assign the custom sensitive detector. Do not forget to register them 
    //  to the SDmanager
    // EnergyTimeSD* absorberET = ...
}

