//
#ifndef HCalWLSEventAction_h
#define HCalWLSEventAction_h 1

#include "G4UserEventAction.hh"
#include "HCalWLSSteppingAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HCalWLSEventAction : public G4UserEventAction
{
public:
  HCalWLSEventAction( HCalWLSSteppingAction *);
  ~HCalWLSEventAction();
  
public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

private:
  HCalWLSSteppingAction* StepAction;
  HCalWLSAnalysisManager* analysisManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
