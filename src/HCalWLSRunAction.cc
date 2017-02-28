
#include "HCalWLSRunAction.hh"

#include "G4Run.hh"


HCalWLSRunAction::HCalWLSRunAction()
{
  analysisManager = HCalWLSAnalysisManager::getInstance();
}

HCalWLSRunAction::~HCalWLSRunAction()
{}

void HCalWLSRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void HCalWLSRunAction::EndOfRunAction(const G4Run* aRun)
{ 
  
  G4double Ratio = analysisManager->fNumOfLGPMTEnter/G4double( analysisManager->fNumOfLGuideEnter );
  G4double Ratio1 = analysisManager->fNumOfLGuideEnter1/G4double( analysisManager->fNumOfLGuideEnter );

  G4cout << "Initial photons = " << G4double( analysisManager->fNumOfLGuideEnter ) 
	 << ",  Hit photons = "  << analysisManager->fNumOfLGPMTEnter
	 << G4endl;  
  G4cout << "Light guide part1 efficiency = " << Ratio1 << G4endl;  
  G4cout << "Light guide efficiency = " << Ratio << G4endl;  
  G4cout << "### Run " << aRun->GetRunID() << " stop" << G4endl;
}
