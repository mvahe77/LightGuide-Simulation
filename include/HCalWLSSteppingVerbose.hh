//
class HCalWLSSteppingVerbose;

#ifndef HCalWLSSteppingVerbose_h
#define HCalWLSSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HCalWLSSteppingVerbose : public G4SteppingVerbose 
{
 public:
   
  HCalWLSSteppingVerbose();
 ~HCalWLSSteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
