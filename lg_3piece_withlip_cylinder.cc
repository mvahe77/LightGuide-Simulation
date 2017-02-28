// -- 
#include "HCalWLSDetectorConstruction.hh"
#include "PhysicsList.hh"
#include "HCalWLSPrimaryGeneratorAction.hh"
#include "HCalWLSRunAction.hh"
#include "HCalWLSEventAction.hh"
#include "HCalWLSSteppingAction.hh"
#include "HCalWLSSteppingVerbose.hh"
#include "HCalWLSStackingAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4UI_USE_ROOT
#include "G4UIRoot.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE_QT
#include "G4UIQt.hh"
#include "G4Qt.hh"
#endif

#include "HCalWLSAnalysisManager.hh"
#include "HCalWLSConfig.hh"

// ---------------------------------------------------------------------------

int main(int argc,char** argv)
{
  // -- Initialize calorimeter geometry
  // 
  HCalWLSConfig* caloconfig = HCalWLSConfig::getInstance();

  // Choose the Random Engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  // Seed the random number generator manually
  G4long mySeed = time(NULL);
  CLHEP::HepRandom::setTheSeed(mySeed);
  //  G4cout << "Random seed set to " << mySeed << G4endl;
  
  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new HCalWLSSteppingVerbose;
  //  G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

 // User Initialization classes (mandatory)
  //
  HCalWLSDetectorConstruction* detector = new HCalWLSDetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  //  G4VUserPhysicsList* physics = new HCalWLSPhysicsList;
  //  runManager->SetUserInitialization(physics);

  runManager->SetUserInitialization( new PhysicsList());

#ifdef G4VIS_USE
  // Visualization, if you choose to have it!
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

#endif
   

  //-----------------------------------------------------------------------------------
  HCalWLSAnalysisManager* analysis = HCalWLSAnalysisManager::getInstance();
  // Output to a root file

  G4VUserPrimaryGeneratorAction* gen_action = new HCalWLSPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //
  G4UserRunAction* run_action = new HCalWLSRunAction;
  runManager->SetUserAction(run_action);
  //
  G4UserSteppingAction* stepping_action = new HCalWLSSteppingAction;
  runManager->SetUserAction(stepping_action);
  //
  G4UserEventAction* event_action = new HCalWLSEventAction( (HCalWLSSteppingAction*)stepping_action );
  runManager->SetUserAction(event_action);
  //
  //-----------------------------------------------------------------------------------
  
  //  G4UserStackingAction* stacking_action = new HCalWLSStackingAction;
  //  runManager->SetUserAction(stacking_action);

  // Initialize G4 kernel
  //
      
  // Get the pointer to the User Interface manager
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();      
  
  if (argc!=1) {  
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);    
  } else { // interactive mode : define visualization UI terminal   
    G4UIsession* session = 0;
     
    // If the enviroment variable for the TCSH terminal is active, it is used and the
    // defaultMacro.mac file is executed

    // The program search for the
    // G4UI_USE_QT variable. It starts a graphical user interface based on the QT libraries
    // In the following case the GUI.mac file is also executed
   
#if defined(G4UI_USE_QT)
    session = new G4UIQt(argc,argv);
    UI->ApplyCommand("/control/execute macro/GUI.mac");      
    G4cout << "Start QT " << G4endl;
#elif defined(G4UI_USE_TCSH)
    session = new G4UIterminal(new G4UItcsh);      
    UI->ApplyCommand("/control/execute cis.mac");  
    G4cout << "G4UI_USE_TCSH " << G4endl;
    // As final option, the simpler user interface terminal is opened
#else
    session = new G4UIterminal();
    UI->ApplyCommand("/control/execute vis.mac");
    G4cout << "defaultMacro " << G4endl;
#endif
    session->SessionStart();
    delete session;
   }

  //  runManager->Initialize();

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete analysis;
#ifdef G4VIS_USE
  delete visManager;
#endif

  delete caloconfig;
  delete runManager;
  delete verbosity;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

