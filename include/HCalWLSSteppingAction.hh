//
#ifndef HCalWLSSteppingAction_h
#define HCalWLSSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "HCalWLSAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HCalWLSSteppingAction : public G4UserSteppingAction
{
public:
  HCalWLSSteppingAction();
  ~HCalWLSSteppingAction(){};
  
  void UserSteppingAction(const G4Step*);
  void endOfEvent();
  G4double GCLAYER1DE,GCLAYER2DE,GCLAYER3DE,GCLAYER4DE,GCETOTAL;
  G4double CerDe;
  G4float Hodo_Edep[4];

  G4double GetLayer1DE() { return GCLAYER1DE/1000.0; }
  G4double GetLayer2DE() { return GCLAYER2DE/1000.0; }
  G4double GetLayer3DE() { return GCLAYER3DE/1000.0; }
  G4double GetLayer4DE() { return GCLAYER4DE/1000.0; }
  G4double GetCaloEtot() { return GCETOTAL = (GCLAYER1DE + GCLAYER2DE + GCLAYER3DE + GCLAYER4DE)/1000.0; }
  G4double GetCerDe()    { return CerDe/1000.0; }  
  G4float* GetHodoEdep() { return Hodo_Edep ;}
  
  void     Reset() { 
    GCLAYER1DE=0.0;
    GCLAYER2DE=0.0;
    GCLAYER3DE=0.0;
    GCLAYER4DE=0.0;
    GCETOTAL=0.0;
    CerDe=0.0;
    Hodo_Edep[0]=0.0;
    Hodo_Edep[1]=0.0;
    Hodo_Edep[2]=0.0;
    Hodo_Edep[3]=0.0;
  }

  HCalWLSAnalysisManager* analysisManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
