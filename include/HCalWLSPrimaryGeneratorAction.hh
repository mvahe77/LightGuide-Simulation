// 
#ifndef HCalWLSPrimaryGeneratorAction_h
#define HCalWLSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "HCalWLSAnalysisManager.hh"

class HCalWLSDetectorConstruction;
class G4ParticleGun;
class G4Event;
class HCalWLSConfig;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class HCalWLSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  HCalWLSPrimaryGeneratorAction(HCalWLSDetectorConstruction*);    
  ~HCalWLSPrimaryGeneratorAction();

  void HCalWLSReadTransportMatrix();
  void HCalWLSTransportToCrystal( G4double &x , G4double &y , G4double &z , G4double &px , G4double &py , G4double &pz , G4double &Pmom );
  
public:
  void GeneratePrimaries(G4Event*);
  void ReadGeneratedEvents(G4int);
private:
  G4ParticleGun* particleGun;
  HCalWLSDetectorConstruction* myDetector;
  HCalWLSAnalysisManager* analysisManager;
  HCalWLSConfig* configManager;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


