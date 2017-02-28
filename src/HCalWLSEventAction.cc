//
#include "HCalWLSEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "HCalWLSAnalysisManager.hh"
#include <iomanip>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
HCalWLSEventAction::HCalWLSEventAction(HCalWLSSteppingAction *st):StepAction(st)
{
  G4cout << "Init HCalWLSEventAction action" << G4endl;
  analysisManager = HCalWLSAnalysisManager::getInstance();

  analysisManager->mStripNumOfEnter[1] = 0;
  analysisManager->mStripNumOfEnter[2] = 0;
  analysisManager->mStripNumOfEnter[3] = 0;
  analysisManager->mStripNumOfEnter[4] = 0;
  analysisManager->mStripNumOfEnter[5] = 0;

  analysisManager->mStripNumOfLost[1] = 0;
  analysisManager->mStripNumOfLost[2] = 0;
  analysisManager->mStripNumOfLost[3] = 0;
  analysisManager->mStripNumOfLost[4] = 0;
  analysisManager->mStripNumOfLost[5] = 0;

  analysisManager->mStripNumOfPMTHits[1] = 0;
  analysisManager->mStripNumOfPMTHits[2] = 0;
  analysisManager->mStripNumOfPMTHits[3] = 0;
  analysisManager->mStripNumOfPMTHits[4] = 0;
  analysisManager->mStripNumOfPMTHits[5] = 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
HCalWLSEventAction::~HCalWLSEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void HCalWLSEventAction::BeginOfEventAction(const G4Event*)
{
  //  G4cout << " START OF A NEW EVENT " << G4endl;

  StepAction->Reset(); // reset all parameters to 0.0 for the next track
  
  analysisManager->fEtotal            = 0.0;
  analysisManager->fNumOfPhotonsTotal = 0;
  analysisManager->fNumOfPMTHits      = 0;
  analysisManager->fPmtTimeDist       = 0.0;
  analysisManager->fPmtTimeStart      = -100.0;
  analysisManager->fNumOfPhotonsTotal = 0;
  analysisManager->fNumberOfWLSHits   = 0;
  analysisManager->fPhotonStatus      = -1000;
  analysisManager->fPhotonStatus1     = -1000;
  analysisManager->fX_EnterLG         = -1000;
  analysisManager->fY_EnterLG         = -1000;

  analysisManager->fXZ                = -1000.0;
  analysisManager->fYZ                = -1000.0;
  analysisManager->fZP                = -1000.0;

  analysisManager->fX_PMTHit          = -1000.0;
  analysisManager->fY_PMTHit          = -1000.0;

  analysisManager->fStrip_Enter       = -1000;
  analysisManager->fStrip_Lost        = -1000;
  
  analysisManager->fX_PhotonLost      = -1000;
  analysisManager->fY_PhotonLost      = -1000;
  analysisManager->fZ_PhotonLost      = -1000;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void HCalWLSEventAction::EndOfEventAction(const G4Event* evt)
{
  //  HCalWLSAnalysisManager* analysis = HCalWLSAnalysisManager::getInstance();
  
  G4int event_id = evt->GetEventID();
  if ( ( event_id % 100 )==0 && ( event_id != 0)) G4cout << "Event = " << event_id << G4endl;
  
  // get number of stored trajectories
  //
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  
  // G4cout << " Energy deposite = "   << analysisManager->fEtotal << " MeV"
  // 	 << " Number of photons = " << analysisManager->fNumOfPhotonsTotal
  // 	 << " PMT hits = "          << analysisManager->fNumOfPMTHits
  // 	 << G4endl;

  // -- End of event, fille the tree

  analysisManager->FillTree();
  


  // periodic printing
  //
//   if (event_id < 100 || event_id%100 == 0) {
//     G4cout << ">>> Event " << evt->GetEventID() << G4endl;
//     G4cout << "    " << n_trajectories 
// 	   << " trajectories stored in this event." << G4endl;
//   }

//  G4cout << "Particle code = " << evt->GetPrimaryVertex()->GetPrimary()->GetPDGcode() << G4endl;
//  getchar();

  //  G4cout << " END OF AN EVENT " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
