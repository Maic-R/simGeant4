
#ifndef SpectrumHit_h
#define SpectrumHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"


class G4ParticleDefinition;

/// Detector hit class
///
/// It defines data members to store the trackID, particle type,
/// mean kinetic energy, energy deposit, initial energy, track length,
/// electronic energy, physical volume and voxel index

class SpectrumHit : public G4VHit
{
  public:
    SpectrumHit();
    SpectrumHit(const SpectrumHit&);
    virtual ~SpectrumHit();

    // Operators
    const SpectrumHit& operator=(const SpectrumHit&);
    G4int operator==(const SpectrumHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // Methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetTrackEnergy    (G4double en)      { fEnergy = en; }
    void SetPartType   (const G4ParticleDefinition* part)
    { fParticleType = part; }


    // Get methods
    G4double GetTrackEnergy() const       { return fEnergy; }
    const G4ParticleDefinition* GetPartType() const
    { return fParticleType; }




  private:

      // Variables
      G4double              fEnergy;
      const G4ParticleDefinition*
                            fParticleType;
};

// Definition of a HitColletion
typedef G4THitsCollection<SpectrumHit> SpectrumHitsCollection;

// Definition of the Allocator
extern G4ThreadLocal G4Allocator<SpectrumHit>* SpectrumHitAllocator;


inline void* SpectrumHit::operator new(size_t)
{
  if(!SpectrumHitAllocator)
      SpectrumHitAllocator = new G4Allocator<SpectrumHit>;
  return (void *) SpectrumHitAllocator->MallocSingle();
}

inline void SpectrumHit::operator delete(void *hit)
{
  SpectrumHitAllocator->FreeSingle((SpectrumHit*) hit);
}

#endif //SpectrumHit_h
