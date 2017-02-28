//////////////////////////////////////////////////////////////////
//
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronQElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4QStoppingPhysics.hh"
#include "G4LHEPStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmProcessOptions.hh"

#include "HadronPhysicsFTFP_BERT_TRV.hh"
//#include "HadronPhysicsFTFP.hh"
#include "HadronPhysicsFTFP_BERT.hh"
#include "HadronPhysicsFTF_BIC.hh"
#include "HadronPhysicsLHEP.hh"
#include "HadronPhysicsLHEP_EMV.hh"
#include "G4HadronInelasticQBBC.hh"
//#include "HadronPhysicsQGSC.hh"
#include "HadronPhysicsQGSC_BERT.hh"
#include "HadronPhysicsQGSC_CHIPS.hh"
//#include "HadronPhysicsQGSC_QGSC.hh"
#include "HadronPhysicsQGSP.hh"
#include "HadronPhysicsQGSP_BERT.hh"
#include "HadronPhysicsQGSP_BERT_HP.hh"
#include "HadronPhysicsQGSP_BIC.hh"
#include "HadronPhysicsQGSP_BIC_HP.hh"
#include "HadronPhysicsQGSP_FTFP_BERT.hh"
#include "HadronPhysicsQGS_BIC.hh"

#include "G4HadronInelasticQLHEP.hh"
#include "G4IonPhysics.hh"

#include "G4LossTableManager.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"

#include "G4OpticalPhysics.hh"
#include "G4UserSpecialCuts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 0.5*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;
  cutForProton    = defaultCutValue;
  cutForOpPhoton  = 0.01*mm;
  dump            = false;
  verboseLevel    = 1;
  IsOptics        = false;
  OpticsDebug     = 0;

  pMessenger = new PhysicsListMessenger(this);

  // Particles
  particleList = new G4DecayPhysics("decays");

  // EM physics
  emPhysicsList = new G4EmStandardPhysics();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

PhysicsList::~PhysicsList()
{
  delete pMessenger;
  delete particleList;
  delete emPhysicsList;
  for(size_t i=0; i<hadronPhys.size(); i++) {
    delete hadronPhys[i];
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::ConstructParticle()
{
  particleList->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  for(size_t i=0; i<hadronPhys.size(); i++) {
    hadronPhys[i]->ConstructProcess();
  }
  if(IsOptics){
    G4OpticalPhysics *opticalPhysicsList = new G4OpticalPhysics(2);
    opticalPhysicsList->ConstructParticle();
    opticalPhysicsList->ConstructProcess();
    opticalPhysicsList->SetWLSTimeProfile(G4String("exponential"));
    
    G4OpBoundaryProcess* opBoundaryProcc = opticalPhysicsList->GetOpBoundaryProcess();
    opBoundaryProcc->SetVerboseLevel(OpticsDebug);
    //    opBoundaryProcc->SetVerboseLevel(3);
    //    G4ProcessManager* pmanager = G4OpticalPhoton::Definition()->GetProcessManager();
    //    pmanager->AddProcess(new G4UserSpecialCuts(),-1,-1,1);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>0)
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;

  if (name == "emstandard_opt2") {

    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option2();

  } else if (name == "emstandard_opt3") {

    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option3();

  } else if (name == "emstandard_opt1") {

    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt0") {

    delete emPhysicsList;
    emPhysicsList = new G4EmStandardPhysics();

  } else if (name == "emlivermore") {

    delete emPhysicsList;
    emPhysicsList = new G4EmLivermorePhysics();

  } else if (name == "penelope") {

    delete emPhysicsList;
    emPhysicsList = new G4EmPenelopePhysics();

  } else if (name == "FTFP_BERT_EMV") {

    AddPhysicsList("emstandard_opt1");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT_EMX") {

    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT") {

    SetBuilderList1();
    hadronPhys.push_back( new HadronPhysicsFTFP_BERT("hadron",true));
    dump = true;

  } else if (name == "FTFP_BERT_TRV") {

    SetBuilderList1();
    hadronPhys.push_back( new HadronPhysicsFTFP_BERT_TRV("hadron",true));
    dump = true;

  } else if (name == "FTF_BIC") {

    SetBuilderList0();
    hadronPhys.push_back( new HadronPhysicsFTF_BIC("hadron",true));
    dump = true;

  } else if (name == "LHEP") {

    SetBuilderList2();
    hadronPhys.push_back( new HadronPhysicsLHEP("hadron"));
    dump = true;

  } else if (name == "LHEP_EMV") {

    AddPhysicsList("emstandard_opt1");
    SetBuilderList3();
    hadronPhys.push_back( new HadronPhysicsLHEP_EMV("hadron"));
    dump = true;

  } else if (name == "QBBC") {

    //    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("emlivermore");
    
    SetBuilderList6();
    hadronPhys.push_back( new G4HadronInelasticQBBC("QBBC",verboseLevel));

  } else if (name == "QBBC_XGG") {

    //    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("emlivermore");
    SetBuilderList6();
    hadronPhys.push_back( new G4HadronInelasticQBBC("QBBC_XGG",verboseLevel));

  } else if (name == "QBBC_XGGSN") {

    AddPhysicsList("emstandard_opt2");
    SetBuilderList6();
    hadronPhys.push_back( new G4HadronInelasticQBBC("QBBC_XGG",verboseLevel));


  } else if (name == "QGSC_BERT") {

    SetBuilderList4();
    hadronPhys.push_back( new HadronPhysicsQGSC_BERT("hadron",true));
    dump = true;

  } else if (name == "QGSC_CHIPS") {

    AddPhysicsList("emlivermore");
    SetBuilderList4();
    hadronPhys.push_back( new HadronPhysicsQGSC_CHIPS("hadron",true));
    dump = true;

  } else if (name == "QGSP_BERT") {

    SetBuilderList1();
    hadronPhys.push_back( new HadronPhysicsQGSP_BERT("hadron",true));
    dump = true;

  } else if (name == "QGSP_FTFP_BERT") {

    SetBuilderList1();
    hadronPhys.push_back( new HadronPhysicsQGSP_FTFP_BERT("hadron",true));
    dump = true;

  } else if (name == "QGSP_BERT_EMV") {

    AddPhysicsList("emstandard_opt1");
    AddPhysicsList("QGSP_BERT");

  } else if (name == "QGSP_BERT_EMX") {

    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("QGSP_BERT");

  } else if (name == "QGSP_BERT_HP") {

    SetBuilderList1(true);
    hadronPhys.push_back( new HadronPhysicsQGSP_BERT_HP("hadron",true));

  } else if (name == "QGSP_BIC") {

    AddPhysicsList("emlivermore");
    SetBuilderList0();
    hadronPhys.push_back( new HadronPhysicsQGSP_BIC("hadron",true));
    dump = true;

  } else if (name == "QGSP_BIC_EMY") {

    AddPhysicsList("emstandard_opt3");
    SetBuilderList0();
    hadronPhys.push_back( new HadronPhysicsQGSP_BIC("hadron",true));
    dump = true;

  } else if (name == "QGS_BIC") {

    SetBuilderList0();
    hadronPhys.push_back( new HadronPhysicsQGS_BIC("hadron",true));
    dump = true;

  } else if (name == "QGSP_BIC_HP") {

    AddPhysicsList("emlivermore");
    SetBuilderList0(true);
    hadronPhys.push_back( new HadronPhysicsQGSP_BIC_HP("hadron",true));
    dump = true;

  } else if (name == "QGSP_BIC_EMY") {

    AddPhysicsList("emstandard_opt3");
    AddPhysicsList("QGSP_BIC");

  } else if (name == "OFF") {
    G4cout << "No hadronic processes" << G4endl;
    AddPhysicsList("emlivermore");
    //    AddPhysicsList("penelope");
  } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList0(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronElasticPhysics("elastic",verboseLevel,
						    flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
  hadronPhys.push_back( new G4NeutronTrackingCut("nTackingCut",verboseLevel));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList1(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronHElasticPhysics(verboseLevel,flagHP));
  //  hadronPhys.push_back( new G4HadronElasticPhysics("elastic",verboseLevel,flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonPhysics("ion"));
  hadronPhys.push_back( new G4NeutronTrackingCut("nTackingCut",verboseLevel));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList2(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronElasticPhysics("LElastic",verboseLevel,
						    flagHP));
  hadronPhys.push_back( new G4IonPhysics("ion"));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList3(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronElasticPhysics("LElastic",verboseLevel,
						    flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonPhysics("ion"));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList4(G4bool)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronQElasticPhysics("elastic",verboseLevel));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonPhysics("ion"));
  hadronPhys.push_back( new G4NeutronTrackingCut("nTackingCut",verboseLevel));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList5(G4bool flagHP)
{
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4HadronDElasticPhysics(verboseLevel,flagHP));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
  hadronPhys.push_back( new G4NeutronTrackingCut("nTackingCut",verboseLevel));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetBuilderList6(G4bool)
{
  G4EmExtraPhysics *extra = new G4EmExtraPhysics("extra EM");
  G4String newState = "on";
  extra->GammaNuclear( newState );
  hadronPhys.push_back( extra );
  hadronPhys.push_back( new G4HadronHElasticPhysics(verboseLevel,false));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
  hadronPhys.push_back( new G4NeutronTrackingCut("nTackingCut",verboseLevel));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetCuts()
{

  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  SetCutValue(cutForProton, "proton");
  SetCutValue(cutForOpPhoton, "opticalphoton");

  if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void PhysicsList::SetCutForGamma(G4double cut)
{
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForElectron(G4double cut)
{
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForPositron(G4double cut)
{
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForProton(G4double cut)
{
  cutForProton = cut;
  SetParticleCuts(cutForProton, G4Proton::Proton());
}

void PhysicsList::List()
{
  G4cout << "### PhysicsLists available: FTFP_BERT FTFP_BERT_EMV FTFP_BERT_EMX FTFP_BERT_TRV FTF_BIC"
	 << G4endl;
  G4cout << "                            LHEP LHEP_EMV QBBC QBBC_XGG QBBC_XGGSN"
	 << G4endl; 
  G4cout << "                            QGSC_BERT QGSC_CHIPS QGSP_BERT QGSP_BERT_EMV QGSP_BIC_EMY"
	 << G4endl; 
  G4cout << "                            QGSP_BERT_EMX QGSP_BERT_HP QGSP_BIC QGSP_BIC_HP" 
	 << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

