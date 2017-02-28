//
#include "G4VProcess.hh"
#include <fstream>
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "HCalWLSAnalysisManager.hh"
#include "G4Step.hh"
#include "HCalWLSConfig.hh"

using namespace std;

HCalWLSAnalysisManager* HCalWLSAnalysisManager::instance = 0;

HCalWLSAnalysisManager::HCalWLSAnalysisManager()
{
  G4cout << " A single copy of Analysis class has been created " << G4endl;
  configCaloManager = HCalWLSConfig::getInstance();

  fout = new TFile("WLS.root", "RECREATE");

  h2 = new TH2F("h2" , "" , 100 , 0.0 , 35.0 , 600 , 0.0 , 600.0 );
  hE = new TH1F("hE" , "" , 100 , 0.0 , 40.0 );

  hEscin    = new TH1F("hEscin"   , "" , 200  , 200.0 , 600.0 );
  hEWLS     = new TH1F("hWLS"     , "" , 200  , 200.0 , 600.0 );
  hEWLSPMT  = new TH1F("hWLSPMT"  , "" , 200  , 200.0 , 600.0 );
  hEWLSTIME = new TH1F("hWLSTIME" , "" , 2000 ,   0.0 ,  60.0 );
  hTrackL   = new TH1F("hTrackL"  , "" , 500  ,   0.0 , 500.0 );

  hSPETime  = new TH1F("hSPETime" , "" , 2000 ,  -5.0 ,  60.0 );
  hSPETime->Sumw2();

  InitTree();
  fNumOfLGuideEnter  = 0;
  fNumOfLGuideEnter1 = 0;
  fNumOfLGPMTEnter   = 0;
}
//------------------------------------------------------------------------------
HCalWLSAnalysisManager::~HCalWLSAnalysisManager() 
{
  G4cout << "Destructor for analysis maneger is called" << G4endl;
  h2->Write();
  hE->Write();
  fOutTree->Write();
  hEscin->Write();
  hEWLS->Write();
  hEWLSPMT->Write();
  hEWLSTIME->Write();
  hTrackL->Write();
  hSPETime->Write();
  fout->Close();
}
//------------------------------------------------------------------------------
HCalWLSAnalysisManager* HCalWLSAnalysisManager::getInstance()
{
  if ( instance == 0 ) instance = new HCalWLSAnalysisManager;
  return instance;
}
//------------------------------------------------------------------------------
void  HCalWLSAnalysisManager::InitTree()
{
  fOutTree = new TTree( "T" , Form("Scin to PMT = %5.2f cm",configCaloManager->ScinToPMTFace) );

  fOutTree->Branch("et"    , &fEtotal       ,     "Total energy/D");
  fOutTree->Branch("npt"   , &fNumOfPhotonsTotal ,"Number of produced photons/I");
  fOutTree->Branch("npr"   , &fNumOfPMTHits ,     "Number of PMT hits/I");
  fOutTree->Branch("td"    , &fPmtTimeDist  ,     "Photon collection time/D");
  fOutTree->Branch("npwls" , &fNumberOfWLSHits ,  "Number of photons that enter WLS/I");

  fOutTree->Branch("xin" , &fIncX , "Incident X/D");
  fOutTree->Branch("yin" , &fIncY , "Incident Y/D");

  fOutTree->Branch("xent" , &fX_EnterLG , "X_EnterLG/D");
  fOutTree->Branch("yent" , &fY_EnterLG , "Y_EnterLG/D");

  fOutTree->Branch("xz" , &fXZ , "Angle_XZ/D");
  fOutTree->Branch("yz" , &fYZ , "Angle_YZ/D");
  fOutTree->Branch("zp" , &fZP , "Angle_ZP/D");

  fOutTree->Branch("xhit" , &fX_PMTHit , "PMTHIT_X/D");
  fOutTree->Branch("yhit" , &fY_PMTHit , "PMTHIT_Y/D");

  fOutTree->Branch("enter" , &fStrip_Enter , "EnterStrip/I");
  fOutTree->Branch("lost"  , &fStrip_Lost  , "LostStrip/I");

  fOutTree->Branch("xlost" , &fX_PhotonLost , "X_PhotonLost/D");
  fOutTree->Branch("ylost" , &fY_PhotonLost , "Y_PhotonLost/D");
  fOutTree->Branch("zlost" , &fZ_PhotonLost , "Z_PhotonLost/D");
}
void  HCalWLSAnalysisManager::FillTree()
{
  if( fStrip_Enter > -100 )
    fOutTree->Fill();
}
