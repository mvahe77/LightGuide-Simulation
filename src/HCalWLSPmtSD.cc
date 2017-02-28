//
#include "HCalWLSPmtSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGauss.h"
#include <TF1.h>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------------

HCalWLSPmtSD::HCalWLSPmtSD(G4String name)
:G4VSensitiveDetector(name)
{
  analysisManager = HCalWLSAnalysisManager::getInstance();
  configManager   = HCalWLSConfig::getInstance();

  //  G4String HCname;
  //  collectionName.insert(HCname="PmtCollection");
}

//-----------------------------------------------------------------------------------

HCalWLSPmtSD::~HCalWLSPmtSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HCalWLSPmtSD::Initialize(G4HCofThisEvent* HCE)
{
  //  trackerCollection = new HCalWLSPmtHitsCollection
       //                    (SensitiveDetectorName,collectionName[0]); 
//   static G4int HCID = -1;
//   if(HCID<0)
//   { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
//   HCE->AddHitsCollection( HCID, trackerCollection ); 

  nHits = 0.0;

  //  G4cout << " Initialize PmtSD " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool HCalWLSPmtSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4Track *aTrack = aStep->GetTrack();
  if( !aTrack ) return false;

  // static TF1 *fQERCL8575 = new TF1("fQERCL8575","gaus(0)+pol4(3)",260.0,600.0);
  // fQERCL8575->SetParameters(1.01149e+01,-2.05963e+04,2.13349e+03,-5.98428e+02,4.84850e+00,-1.31851e-02,1.48563e-05,-5.94898e-09);

  G4String str = aTrack->GetDefinition()->GetParticleName();

  if( str == G4String("opticalphoton") ) 
    {
      //   G4double ephoton = aTrack->GetTotalEnergy();
      //   G4double pmtqe = fQERCL8575->Eval(1240.0/(ephoton*1.0e+6))/100.0; // Quantum effitiency of RCA8575
      //   G4double rand  = CLHEP::RandFlat::shoot(0.0,1.0);
      //   G4double rand1 = CLHEP::RandFlat::shoot(0.0,1.0);
      
      //   G4double randexp = -std::log(rand1)*2.0;
      
      //   //    if( rand < pmtqe ) {
      //   if( rand < 1.0 ) {
      //     analysisManager->fPmtTimeLastHit = aTrack->GetGlobalTime();
      //     analysisManager->hEWLSPMT->Fill(1240.0/(ephoton*1.0e+6));
      //     G4double time1 = analysisManager->fPmtTimeStart;
      //     G4double time2 = analysisManager->fPmtTimeLastHit;
      //     G4double dtime = time2-time1;
      //     time2 = time2 + randexp;
      //     analysisManager->hEWLSTIME->Fill(time2 - time1);
      //     analysisManager->hTrackL->Fill(aTrack->GetTrackLength());
      //     nHits++;

      //     // -- Get the time distribution based on single photo electron spectrum 
      //     // -- fSPE is the single photoelectron respoance function
      //     G4double xmin = -5.0;
      //     G4double xmax = 35.0;
      //     G4double dx   = (xmax-xmin)/10000.0;
      //     for(int ii = 0; ii < 10000; ii++) {
      // 	G4double xval = xmin + dx/2.0 + dx*ii;
      // 	analysisManager->hSPETime->Fill( xval + dtime , configManager->fSPE->Eval(xval) );
      //     }
      //   }
      //   aTrack->SetTrackStatus(fStopAndKill); // don't need to track this one any more      
      if( analysisManager->fX_PMTHit == -1000 && analysisManager->fY_PMTHit == -1000 )
      //      if( analysisManager->fX_PMTHit == 0 && analysisManager->fY_PMTHit == 0 )
	{
	  analysisManager->fX_PMTHit = aTrack->GetPosition().x()/cm;
	  analysisManager->fY_PMTHit = (aTrack->GetPosition().y()-4.0)/cm;
	  //	  G4cout << "PMT hit = " << analysisManager->fX_PMTHit << "  " << analysisManager->fY_PMTHit << G4endl;
	}
    }
  analysisManager->fNumOfLGPMTEnter++;
  aTrack->SetTrackStatus(fStopAndKill);  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HCalWLSPmtSD::EndOfEvent(G4HCofThisEvent*)
{
//   if (verboseLevel>0) { 
//      G4int NbHits = trackerCollection->entries();
//      G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
//             << " hits in the tracker chambers: " << G4endl;
//      for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
//     }   

  analysisManager->fPmtTimeDist  = analysisManager->fPmtTimeLastHit - analysisManager->fPmtTimeStart;
  analysisManager->fNumOfPMTHits = nHits;
  //  G4cout << "Total PMT hits = " << nHits << G4endl;

  //  G4cout << "End of event, time = " << analysisManager->fPmtTimeDist << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
