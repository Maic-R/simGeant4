
#ifndef SpectrumDetector_h
#define SpectrumDetector_h 1

#include "G4VSensitiveDetector.hh"

#include "SpectrumHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class SpectrumDetector : public G4VSensitiveDetector
{
  public:
    SpectrumDetector(const G4String& name,
                const G4String& hitsCollectionName);
    virtual ~SpectrumDetector();
  
    // Methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    SpectrumHitsCollection* fHitsCollection;

};

#endif //SpectrumDetector
