//
#ifndef HCalWLSTrackerHit_h
#define HCalWLSTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class HCalWLSTrackerHit : public G4VHit
{
  public:

      HCalWLSTrackerHit();
     ~HCalWLSTrackerHit();
      HCalWLSTrackerHit(const HCalWLSTrackerHit&);
      const HCalWLSTrackerHit& operator=(const HCalWLSTrackerHit&);
      G4int operator==(const HCalWLSTrackerHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetChamberNb(G4int chamb)      { chamberNb = chamb; };  
      void SetEdep     (G4double de)      { edep = de; };
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      
      G4int GetTrackID()    { return trackID; };
      G4int GetChamberNb()  { return chamberNb; };
      G4double GetEdep()    { return edep; };      
      G4ThreeVector GetPos(){ return pos; };
      
  private:
  
      G4int         trackID;
      G4int         chamberNb;
      G4double      edep;
      G4ThreeVector pos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<HCalWLSTrackerHit> HCalWLSTrackerHitsCollection;

extern G4Allocator<HCalWLSTrackerHit> HCalWLSTrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* HCalWLSTrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) HCalWLSTrackerHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void HCalWLSTrackerHit::operator delete(void *aHit)
{
  HCalWLSTrackerHitAllocator.FreeSingle((HCalWLSTrackerHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
