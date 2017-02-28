//
#include "HCalWLSSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4TrackStatus.hh"
#include "G4Track.hh"
#include "G4OpBoundaryProcess.hh"
#include <fstream>
#include <vector>
#include <TMath.h>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HCalWLSSteppingAction::HCalWLSSteppingAction()
{ 
  G4cout << " #####  Stepping class created ! " << G4endl;
  analysisManager = HCalWLSAnalysisManager::getInstance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HCalWLSSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  if(aStep == NULL) return;
  G4double EdepStep = aStep->GetTotalEnergyDeposit();
  G4Track* aTrack   = aStep->GetTrack();
  G4String volname  = aTrack->GetVolume()->GetName();
  G4String str      = aTrack->GetDefinition()->GetParticleName();
  G4double trackL   = aTrack->GetTrackLength();

  static G4OpBoundaryProcess* boundary=NULL;
  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm 
      = aStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
	boundary = (G4OpBoundaryProcess*)(*pv)[i];
	break;
      }
    }
  }
  //  G4cout << "Volume=  " << volname << "  " << str << G4endl;

  if(aTrack->GetNextVolume() == 0) return;
  G4StepPoint* prePoint  = aStep->GetPreStepPoint();
  G4StepPoint* postPoint = aStep->GetPostStepPoint();

  // --------------------------------------------------------------------------
  if(aTrack->GetParentID() == 0) {
    if(postPoint->GetStepStatus() == fGeomBoundary) {
      G4TouchableHandle  touchPost = postPoint->GetTouchableHandle();
      G4TouchableHandle  touchPre  = prePoint ->GetTouchableHandle();
      G4VPhysicalVolume* volume = touchPre->GetVolume();
      if(volume != NULL) {
	G4String name = volume->GetName();
	if(name == "AirPln") {
	  analysisManager->fPmtTimeStart = aTrack->GetGlobalTime();
	} else if(name == "Scin") {
	  //	  aTrack->SetTrackStatus(fStopAndKill);
	}
      }
    }
  }  
  //-------------------------------------------------------------------------------------
  // Total energy deposition in crystal
  if( volname == G4String("Scin") ) { 
    analysisManager->fEtotal += EdepStep;
  } else if( volname == G4String("AirPln1") ){
    if( str != "opticalphoton") {
      //      G4cout << "Secondary -> " << str << G4endl;
      //      aTrack->SetTrackStatus(fStopAndKill);
    }
  }
  //------------------------------------------------------------------------------------
  //-- Number of photons that enter WLS
  if(postPoint->GetStepStatus() == fGeomBoundary) {
    G4TouchableHandle  touchPre  = prePoint ->GetTouchableHandle();
    G4TouchableHandle  touchPost = postPoint->GetTouchableHandle();
    G4VPhysicalVolume* volume = aTrack->GetNextVolume();
    if(volume != NULL) {
      G4String name = volume->GetName();
      if(name == "WLS") {
	if( str == "opticalphoton") {
	  if( analysisManager->fPhotonStatus != aTrack->GetTrackID() ) {
	    analysisManager->fNumberOfWLSHits++;
	    //	    G4cout << "First step " << touchPre->GetVolume()->GetName() << "  " << aTrack->GetTrackID() 
	    //		   << " copy numbers = " << copyn << " " << copyn
	    //		   << G4endl;
	    //	    analysisManager->fPhotonStatus = aTrack->GetTrackID();
	  }
	}
      }
    }
  }
  if( str == "opticalphoton") 
    {
      if( volname.substr(0,3) == "Seg") 
	{
	  // G4cout << volname << " "
	  // 	 << aTrack->GetNextVolume()->GetName()
	  // 	 << G4endl;
	  // G4cout <<  postPoint->GetProcessDefinedStep()->GetProcessName() <<G4endl;
	}
    }
    //------------------------------------------------------------------------------------
  //-- Number of photons that enter WLS
  if(postPoint->GetStepStatus() == fGeomBoundary) {
    G4TouchableHandle  touchPre  = prePoint ->GetTouchableHandle();
    G4TouchableHandle  touchPost = postPoint->GetTouchableHandle();
    //    G4VPhysicalVolume* volume = aTrack->GetNextVolume();
    G4VPhysicalVolume* preVolume  = touchPre->GetVolume();
    G4VPhysicalVolume* postVolume = touchPost->GetVolume();
    G4ThreeVector Pmom        = aTrack->GetMomentum();

    if( postVolume != NULL) {
      G4String namePre  = preVolume ->GetName();
      G4String namePost = postVolume->GetName();

      //      if(namePre == "BoxWtoLGPlane" && (namePost.substr(0,3) == "Seg" || namePost.substr(0,3) == "Middle"  )) 
      if(namePre == "BoxWtoLGPlane" )
	{
	  if( str == "opticalphoton" && Pmom[2] < 0 ) 
	    {
	      if( analysisManager->fPhotonStatus != aTrack->GetTrackID() ) 
		{
		  analysisManager->fNumOfLGuideEnter++;
		  analysisManager->fPhotonStatus = aTrack->GetTrackID();

		  G4double XZ_angle = TMath::ATan(Pmom[2]/Pmom[0]) * 180.0/3.141592654;
		  G4double YZ_angle = TMath::ATan(Pmom[2]/Pmom[1]) * 180.0/3.141592654;
		  
		  G4double PZ_angle = 90.0-TMath::ACos( TMath::Abs(Pmom[2]) / 
							TMath::Sqrt( Pmom[0]*Pmom[0] + Pmom[1]*Pmom[1] + Pmom[2]*Pmom[2] )) * 180.0/3.141592654;

		  analysisManager->fX_EnterLG = aTrack->GetPosition().x()/cm;
		  analysisManager->fY_EnterLG = aTrack->GetPosition().y()/cm;

		  // G4cout << "Photon entered the LG " << namePost << "  "
		  // 	 << " XZ_angle = " << XZ_angle 
		  // 	 << " YZ_angle = " << YZ_angle 
		  // 	 << " PZ_angle = " << PZ_angle 
		  // 	 << G4endl;
		  if( Pmom[0] >= 0.0 )
		    analysisManager->fXZ = -XZ_angle;
		  else 
		    analysisManager->fXZ =  XZ_angle;
		  if( Pmom[1] >= 0.0 )
		    analysisManager->fYZ = -YZ_angle;
		  else
		    analysisManager->fYZ =  YZ_angle;
		  analysisManager->fZP   =  PZ_angle;
		  //--
		}
	    }
	}
      if(namePre == "BoxWtoLGPlane1"  ) {	
	if( str == "opticalphoton") {
	  if( analysisManager->fPhotonStatus1 != aTrack->GetTrackID() ) {
	    analysisManager->fNumOfLGuideEnter1++;
	    analysisManager->fPhotonStatus1 = aTrack->GetTrackID();
	    //	    G4cout << "Photon entered the plane1 " << G4endl;
	  }
	}
      }
    }
  }
  
  //Check to see if the partcile was actually at a boundary
  //Otherwise the boundary status may not be valid
  //Prior to Geant4.6.0-p1 this would not have been enough to check
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
  G4StepPoint* thePrePoint  = aStep->GetPreStepPoint();
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;

  G4TouchableHandle  thePreTouch  = thePrePoint ->GetTouchableHandle();
  G4TouchableHandle  thePostTouch = thePostPoint->GetTouchableHandle();

  G4String PreVolName  = thePreTouch ->GetVolume()->GetName();
  G4String PostVolName = thePostTouch->GetVolume()->GetName();

  boundaryStatus=boundary->GetStatus();
  if(thePostPoint->GetStepStatus()==fGeomBoundary)
    {
      switch(boundaryStatus)
	{
	case Absorption:
	  //	    break;
	case Detection: 
	case FresnelReflection:
	  //G4cout << "F. Reflection: " << volname << " to " << aTrack->GetNextVolume()->GetName() << "  "<< G4endl;
	case FresnelRefraction:
	  if( analysisManager->fStrip_Enter > -100 && PreVolName != "PMT" )
	    {
	      if( PreVolName.substr( 0 , 3 ) == "Seg" && PostVolName != "PMT" )
		{
		  if( PreVolName.size() == 4 )
		    analysisManager->fStrip_Lost = atoi( PreVolName.substr( 3 , 1 ).c_str() );
		  else 
		    analysisManager->fStrip_Lost = atoi( PreVolName.substr( 3 , 2 ).c_str() );
		}
	      else if( PreVolName == "Middle" )
		{
		  analysisManager->fStrip_Lost = 0;
		}		
	      analysisManager->fX_PhotonLost = aTrack->GetPosition().x()/cm;
	      analysisManager->fY_PhotonLost = aTrack->GetPosition().y()/cm;
	      analysisManager->fZ_PhotonLost = aTrack->GetPosition().z()/cm;
#define ADEBUG1
#ifdef ADEBUG
	      G4cout << "FresnelRefraction: " << PreVolName << " -> " << PostVolName << "  " 
		     << " lost from x,y,z: " 
		     << analysisManager->fX_PhotonLost << "  "
		     << analysisManager->fY_PhotonLost << "  "
		     << analysisManager->fZ_PhotonLost << "  "
		     << G4endl;
#endif
	    }
	case TotalInternalReflection:
	  //	  G4cout << "Internal Reflection: " << volname << " to " << aTrack->GetNextVolume()->GetName() << "  "		   << G4endl;
	case SpikeReflection:
	  //	trackInformation->IncReflections();
	case StepTooSmall:
	  //	    G4cout << " *** StepTooSmall *** " << G4endl;
	case SameMaterial:
	  if( PreVolName == "BoxWtoLGPlane" )
	    {
	      if( PostVolName == "Middle") 
		{
		  analysisManager->fStrip_Enter = 0;
#ifdef ADEBUG
		  G4cout << " Photon entered from the Middle" << G4endl;
#endif
		}
	      else 
		{
		  analysisManager->fStrip_Enter = atoi( PostVolName.substr( 3 , 1 ).c_str() );
#ifdef ADEBUG
		  G4cout << " Photon entered from the " << PostVolName << G4endl;
		  //		  G4cout << " *** SameMaterial *** " << PreVolName << " -> " << PostVolName << " " << PostVolName.substr( 3 , 1 ) << G4endl;
#endif
		}
	    }
	default:
	  break;
	}
      //      if(thePostPV->GetName()=="sphere") trackInformation->AddTrackStatusFlag(hitSphere);
    }
  //-------------------------------------------------------------------------------------
  // Energy distribution of photons produced in scintilator 
  const  G4TrackVector* fSecondary = aStep->GetSecondary();
  int fSecN = (*fSecondary).size();

  for( int ii = 0; ii < fSecN; ii++ ) {
    G4Track* secTrack = (*fSecondary)[ii];
    G4String secondaryParticleName = secTrack->GetDefinition()->GetParticleName();
    //    G4double secondaryParticleKineticEnergy = secTrack->GetKineticEnergy();
    //    G4ThreeVector secpos3D = secTrack->GetPosition();
    //    G4ThreeVector secdir3D = secTrack->GetMomentumDirection();
    //    G4cout <<  postPoint->GetProcessDefinedStep()->GetProcessName() <<G4endl;

    if( secondaryParticleName == "opticalphoton" ) {
      G4String volumeName = secTrack->GetVolume()->GetName();
      if(volname == "Scin") { 
	analysisManager->hEscin->Fill( 1240.0/(secTrack->GetTotalEnergy()*1.0e+6) );
	analysisManager->fNumOfPhotonsTotal += 1;	
      }
      if(volname == "WLS")  analysisManager->hEWLS ->Fill( 1240.0/(secTrack->GetTotalEnergy()*1.0e+6) );
      G4ThreeVector secdir3D = secTrack->GetMomentumDirection();
      //      if( secdir3D[2] > 0.0 ) secTrack->SetTrackStatus(fStopAndKill);      
      //      if( analysisManager->fEtotal <= 0.0 ) secTrack->SetTrackStatus(fStopAndKill); // 
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HCalWLSSteppingAction::endOfEvent() 
{
  G4cout << "END OF TRACK" << G4endl;
}
