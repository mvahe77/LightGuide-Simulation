// Author: Vahe Mamyan
// -------------------------------------------------------------------
#ifndef HCalWLSAnalysis_hh
#define HCalWLSAnalysis_hh
#include <vector>
#include "G4ThreeVector.hh"
#include "HCalWLS.hh"
#include <fstream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <map>

class HCalWLSConfig;

using namespace std;

//-----------------------------------------------------------------------------

class HCalWLSAnalysisManager
{
public:
  virtual ~HCalWLSAnalysisManager();

  // method to call to create an instance of this class
  static HCalWLSAnalysisManager* getInstance();

  void SetCrystal( HCalWLS *fDet ) { fDetCrystal = fDet; }

  void  InitTree();
  void  FillTree();
  //  void  FillTree( G4double *pOutVars );

  G4double fInitialEnergy;

  G4int    fNumOfCrystalReg;
  G4double fPmtTimeDist;
  G4double fPmtTimeStart;
  G4double fPmtTimeLastHit;
  G4int    fNumberOfWLSHits;
  G4int    fPhotonStatus;
  G4int    fPhotonStatus1;

  G4int    fNumOfLGuideEnter;
  G4int    fNumOfLGuideEnter1;
  G4int    fNumOfLGPMTEnter;

  TFile *fout;
  TH2F  *h2;
  TH1F  *hE;
  
  TH1F  *hEscin;
  TH1F  *hEWLS;
  TH1F  *hEWLSPMT;
  TH1F  *hEWLSTIME;
  TH1F  *hTrackL;
  TH1F  *hSPETime;

  G4int     fNumbOfLayers;
  G4double *fECaloPlate;
  G4double  fEtotal;
  G4int     fNumOfPMTHits;
  G4int     fNumOfPhotonsTotal;

  G4double  fIncX;
  G4double  fIncY;

  G4double  fXZ;
  G4double  fYZ;
  G4double  fZP;

  G4double  fX_EnterLG;
  G4double  fY_EnterLG;
  
  G4double  fX_PMTHit;
  G4double  fY_PMTHit;

  G4int     fStrip_Enter;
  G4int     fStrip_Lost;

  G4double  fX_PhotonLost;
  G4double  fY_PhotonLost;
  G4double  fZ_PhotonLost;

  map<G4int,G4int> mStripNumOfEnter;
  map<G4int,G4int> mStripNumOfLost;
  map<G4int,G4int> mStripNumOfPMTHits;

private:
  //private constructor in order to create a singleton
  
  HCalWLSAnalysisManager();
  static HCalWLSAnalysisManager* instance;
  HCalWLSConfig* configCaloManager;

  //---------------------------------------------------------------------------



  // -- Detector info

  HCalWLS *fDetCrystal;

  TTree    *fOutTree;

  // -- Crystal

};

#endif
