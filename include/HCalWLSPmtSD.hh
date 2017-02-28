//
#ifndef HCalWLSPmtSD_h
#define HCalWLSPmtSD_h 1
#include "HCalWLSAnalysisManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Navigator.hh"
#include "HCalWLSConfig.hh"

//#include "HCalWLSPmtHit.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HCalWLSPmtSD : public G4VSensitiveDetector
{
public:
  HCalWLSPmtSD(G4String);
  ~HCalWLSPmtSD();
  
  void     Initialize( G4HCofThisEvent* );
  G4bool   ProcessHits( G4Step* , G4TouchableHistory* );
  void     EndOfEvent( G4HCofThisEvent* );
  HCalWLSAnalysisManager* analysisManager;
  HCalWLSConfig* configManager;

private:
  G4double nHits;
  G4double fADC_pmt1;
  G4double fADC_pmt2;

  //      HCalWLSPmtHitsCollection* trackerCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

