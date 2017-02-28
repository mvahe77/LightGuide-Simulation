//
#ifndef HCalWLS_h
#define HCalWLS_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include <vector>

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class HCalWLSDetectorMessenger;
class G4Tubs;
class G4IntersectionSolid;
class G4SubtractionSolid;
class HCalWLSAnalysisManager;
class G4SubtractionSolid;
class G4Trap;
class G4BooleanSolid;
class HCalWLSConfig;
class G4PVPlacement;
class HCalWLSMaterialManager;
class G4VSolid;

//-----------------------------------------------------------------------------------
class HCalWLS
{
  public:
  HCalWLS();
  ~HCalWLS();

  public:
  
  G4VPhysicalVolume*   ConstructWLS(G4LogicalVolume* , G4VPhysicalVolume*, G4ThreeVector);
  G4SubtractionSolid*  ConstructScinSolid();
  G4SubtractionSolid*  ConstructScinSolidWrap();

  void ConstrucLGPart1( G4LogicalVolume *logicWorld , const G4double PosZ0 , const G4double D , const G4double YShift );
  void ConstrucLGPart2( G4LogicalVolume *logicWorld , const G4double PosZ0 , const G4double D , const G4double YShift , const G4double D1 );
  
  // Some get methods for later need
  //
  //
  void      Init();

  //-- Some get methods
  G4BooleanSolid* ConstructLightGuide();
  G4double   VOLUME;

  private:
  
  G4double StripThickArr[3];
  G4double StripPMTCenterShift[4];

  G4VPhysicalVolume*  physWorld;  

  G4SubtractionSolid* solScin;
  G4LogicalVolume*    logScin;
  G4VPhysicalVolume*  phyScin;

  G4Box*              solScinBox;
  G4LogicalVolume*    logScinBox;
  G4VPhysicalVolume*  phyScinBox;

  G4SubtractionSolid* solScinWr;
  G4LogicalVolume*    logScinWr;
  G4VPhysicalVolume*  phyScinWr;

  G4Box*              solAirGap;
  G4LogicalVolume*    logAirGap;
  G4VPhysicalVolume*  phyAirGap;

  G4Box*              solWall;
  G4LogicalVolume*    logWall;
  G4VPhysicalVolume*  phyWall;

  G4Box*              solWLS;
  G4LogicalVolume*    logWLS;
  G4VPhysicalVolume*  phyWLS;
 
  G4Box*              solModule;
  G4LogicalVolume*    logModule;
  G4VPhysicalVolume*  phyModule;

  G4Box*              solLightG;
  G4LogicalVolume*    logLightG;
  G4VPhysicalVolume*  phyLightG;

  G4Tubs*            solidScinPMT;    // pointer to the solid Chamber
  G4LogicalVolume*   logicScinPMT;    // pointer to the logical Chamber
  G4VPhysicalVolume* physScinPMT;     // pointer to the physical Chamber

  G4Tubs*            solPMT;
  G4LogicalVolume*   logPMT;
  G4VPhysicalVolume* phyPMT;

  G4Tubs*            solCathod;      // pointer to the solid Chamber
  G4LogicalVolume*   logCathod;      // pointer to the logical Chamber
  G4VPhysicalVolume* phyCathod;       // pointer to the physical Chamber

  G4Tubs*            solPmtShell;
  G4LogicalVolume*   logPmtShell;
  G4VPhysicalVolume* phyPmtShell;

  G4Box*             solAirPln;
  G4LogicalVolume*   logAirPln;
  G4VPhysicalVolume* phyAirPln;

  G4Box*             solAirPln1;
  G4LogicalVolume*   logAirPln1;
  G4VPhysicalVolume* phyAirPln1;

  G4Box*             solBlack;
  G4LogicalVolume*   logBlack;
  G4VPhysicalVolume* phyBlack;

  G4Box*             solBoxWtoLG;
  G4LogicalVolume*   logBoxWtoLG;
  G4VPhysicalVolume* phyBoxWtoLG;

  G4Box*             solBoxWtoLGPlane;
  G4LogicalVolume*   logBoxWtoLGPlane;
  G4VPhysicalVolume* phyBoxWtoLGPlane;

  G4Box*             solBoxWtoLGPlane1;
  G4LogicalVolume*   logBoxWtoLGPlane1;
  G4VPhysicalVolume* phyBoxWtoLGPlane1;

  G4Tubs*            solAcrylicTube;
  G4LogicalVolume*   logAcrylicTube;
  G4VPhysicalVolume* phyAcrylicTube;

  //
  // ---------------------------------------------------------------------------------------------------------
  //

  G4Tubs*                     solSeg1;
  G4LogicalVolume*            logSeg1;
  G4VPhysicalVolume*          phySeg1;

  G4Tubs*                     solSeg2;
  G4LogicalVolume*            logSeg2;
  G4VPhysicalVolume*          phySeg2;

  G4Tubs*                     solSeg3;
  G4LogicalVolume*            logSeg3;
  G4VPhysicalVolume*          phySeg3;

  G4Tubs*                     solSeg4;
  G4LogicalVolume*            logSeg4;
  G4VPhysicalVolume*          phySeg4;

  G4Tubs*                     solSeg5;
  G4LogicalVolume*            logSeg5;
  G4VPhysicalVolume*          phySeg5;

  G4Tubs*                     solSeg6;
  G4LogicalVolume*            logSeg6;
  G4VPhysicalVolume*          phySeg6;

  G4Tubs*                     solSeg7;
  G4LogicalVolume*            logSeg7;
  G4VPhysicalVolume*          phySeg7;

  G4Tubs*                     solSeg8;
  G4LogicalVolume*            logSeg8;
  G4VPhysicalVolume*          phySeg8;

  G4Tubs*                     solSeg9;
  G4LogicalVolume*            logSeg9;
  G4VPhysicalVolume*          phySeg9;

  G4Tubs*                     solSeg10;
  G4LogicalVolume*            logSeg10;
  G4VPhysicalVolume*          phySeg10;

  G4Tubs*                     solSeg11;
  G4LogicalVolume*            logSeg11;
  G4VPhysicalVolume*          phySeg11;

  G4Tubs*                     solSeg12;
  G4LogicalVolume*            logSeg12;
  G4VPhysicalVolume*          phySeg12;

  G4Box*                      solMiddleBox;
  G4LogicalVolume*            logMiddleBox;
  G4VPhysicalVolume*          phyMiddleBox;

  G4Tubs*                     solSeg13;
  G4LogicalVolume*            logSeg13;
  G4VPhysicalVolume*          phySeg13;

  G4Tubs*                     solSeg14;
  G4LogicalVolume*            logSeg14;
  G4VPhysicalVolume*          phySeg14;

  G4Tubs*                     solSeg15;
  G4LogicalVolume*            logSeg15;
  G4VPhysicalVolume*          phySeg15;

  G4Tubs*                     solSeg16;
  G4LogicalVolume*            logSeg16;
  G4VPhysicalVolume*          phySeg16;

  G4Tubs*                     solSeg17;
  G4LogicalVolume*            logSeg17;
  G4VPhysicalVolume*          phySeg17;

  G4Tubs*                     solSeg18;
  G4LogicalVolume*            logSeg18;
  G4VPhysicalVolume*          phySeg18;

  G4Tubs*                     solSeg19;
  G4LogicalVolume*            logSeg19;
  G4VPhysicalVolume*          phySeg19;

  G4Tubs*                     solSeg20;
  G4LogicalVolume*            logSeg20;
  G4VPhysicalVolume*          phySeg20;

  G4Tubs*                     solSeg21;
  G4LogicalVolume*            logSeg21;
  G4VPhysicalVolume*          phySeg21;

  G4Tubs*                     solSeg22;
  G4LogicalVolume*            logSeg22;
  G4VPhysicalVolume*          phySeg22;

  G4Tubs*                     solSeg23;
  G4LogicalVolume*            logSeg23;
  G4VPhysicalVolume*          phySeg23;

  G4Tubs*                     solSeg24;
  G4LogicalVolume*            logSeg24;
  G4VPhysicalVolume*          phySeg24;
  
  G4Tubs*                     solSeg13Foil;
  G4LogicalVolume*            logSeg13Foil;
  G4VPhysicalVolume*          phySeg13Foil;

  G4Tubs*                     solSeg14Foil;
  G4LogicalVolume*            logSeg14Foil;
  G4VPhysicalVolume*          phySeg14Foil;

  G4Tubs*                     solSeg15Foil;
  G4LogicalVolume*            logSeg15Foil;
  G4VPhysicalVolume*          phySeg15Foil;

  G4Tubs*                     solSeg16Foil;
  G4LogicalVolume*            logSeg16Foil;
  G4VPhysicalVolume*          phySeg16Foil;

  G4Tubs*                     solSeg17Foil;
  G4LogicalVolume*            logSeg17Foil;
  G4VPhysicalVolume*          phySeg17Foil;

  G4Tubs*                     solSeg18Foil;
  G4LogicalVolume*            logSeg18Foil;
  G4VPhysicalVolume*          phySeg18Foil;

  G4Tubs*                     solSeg19Foil;
  G4LogicalVolume*            logSeg19Foil;
  G4VPhysicalVolume*          phySeg19Foil;

  G4Tubs*                     solSeg20Foil;
  G4LogicalVolume*            logSeg20Foil;
  G4VPhysicalVolume*          phySeg20Foil;

  G4Tubs*                     solSeg21Foil;
  G4LogicalVolume*            logSeg21Foil;
  G4VPhysicalVolume*          phySeg21Foil;

  G4Tubs*                     solSeg22Foil;
  G4LogicalVolume*            logSeg22Foil;
  G4VPhysicalVolume*          phySeg22Foil;

  G4Tubs*                     solSeg23Foil;
  G4LogicalVolume*            logSeg23Foil;
  G4VPhysicalVolume*          phySeg23Foil;

  G4Tubs*                     solSeg24Foil;
  G4LogicalVolume*            logSeg24Foil;
  G4VPhysicalVolume*          phySeg24Foil;


  // ---------------------------------------------------------------------------------------------------------
  // -- WLS parameters

  G4double  ScintRad;
  G4double  ScinThick;
  G4double  ScinSection;
  G4double  ScinToPMTFace;
  G4double  LGuideL;
  G4double  LGuideWidth, LGuideHigh;
  G4double  ScinToWLSAirGap;
  // -- PMT
  G4double  PMTRadiusOut;
  G4double  PMTRadiusIn;
  G4double  PMTLength;
  G4double  PMTFrontThick;
  // --
  G4double CathodRadius;
  G4double CathodThick;

  HCalWLSAnalysisManager *analysisManager;   // For data management 
  HCalWLSConfig          *configManager;
  HCalWLSMaterialManager *materialManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
