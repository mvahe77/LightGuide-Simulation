//
#ifndef HCalWLSRunAction_h
#define HCalWLSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "HCalWLSAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class HCalWLSRunAction : public G4UserRunAction
{
  public:
    HCalWLSRunAction();
   ~HCalWLSRunAction();
  HCalWLSAnalysisManager *analysisManager;
  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





