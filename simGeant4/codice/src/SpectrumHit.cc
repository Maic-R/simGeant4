
#include "SpectrumHit.hh"

G4ThreadLocal G4Allocator<SpectrumHit>* SpectrumHitAllocator=0;


SpectrumHit::SpectrumHit()
 : G4VHit(),
   fEnergy(-1.),
   fParticleType(0)
{}

SpectrumHit::~SpectrumHit() {}

SpectrumHit::SpectrumHit(const SpectrumHit& right)
  : G4VHit()
{
  fEnergy         = right.fEnergy;
  fParticleType   = right.fParticleType;
}

const SpectrumHit& SpectrumHit::operator=(const SpectrumHit& right)
{
    fEnergy         = right.fEnergy;
    fParticleType   = right.fParticleType;

  return *this;
}

G4int SpectrumHit::operator==(const SpectrumHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SpectrumHit::Draw()
{
  // Not implemented
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SpectrumHit::Print()
{
  // Not implemented
}