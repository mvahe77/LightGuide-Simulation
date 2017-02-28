// Author: Vahe Mamyan
// -------------------------------------------------------------------
#ifndef HCalWLSConfig_hh
#define HCalWLSConfig_hh
#include <vector>
#include "G4ThreeVector.hh"
#include "HCalWLS.hh"
#include <fstream>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TSpline.h>

//-----------------------------------------------------------------------------

class HCalWLSConfig
{
public:
  virtual ~HCalWLSConfig();

  // method to call to create an instance of this class
  static HCalWLSConfig* getInstance();

  void  Init();
  
  G4double  ScintRad;
  G4double  ScinThick;
  G4double  ScinSection;
  G4double  ScinToPMTFace;
  G4double  LGuideL;
  G4double  LGuideWidth, LGuideHigh;
  G4double  ScinToWLSAirGap;

  TSpline *fSPE; // -- pointer to measured single photoelectron spectrum 
private:
  //private constructor in order to create a singleton
  
  HCalWLSConfig();
  static HCalWLSConfig* instance;
  //---------------------------------------------------------------------------
};

#endif
