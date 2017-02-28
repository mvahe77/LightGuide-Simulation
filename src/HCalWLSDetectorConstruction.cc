//
#include "HCalWLSDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4NistManager.hh"
#include "G4Sphere.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "HCalWLS.hh"
#include "HCalWLSMaterials.hh"

//#include "G4GDMLParser.hh"
#include "HCalWLSPmtSD.hh"
#include "G4SDManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
HCalWLSDetectorConstruction::HCalWLSDetectorConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 solidLayer(0),logicLayer(0),physiLayer(0), 
 LayerMater(0)
{
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
HCalWLSDetectorConstruction::~HCalWLSDetectorConstruction()
{
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* HCalWLSDetectorConstruction::Construct()
{
  G4cout << "Start detector construction" << G4endl;
  //------------------------------ 
  // World
  //------------------------------ 

  HCalWLSMaterialManager* matManager = HCalWLSMaterialManager::getInstance();

  G4Material* air = G4Material::GetMaterial(G4String("G4_AIR"));
  G4Material* vacum = G4Material::GetMaterial(G4String("G4_Galactic"));

  G4double HalfWorldLengthX =  30.0*cm;
  G4double HalfWorldLengthY =  30.0*cm;
  G4double HalfWorldLengthZ =  100.0*cm;
  
  solidWorld = new G4Sphere( "sSphere" , 0 , 3600 *mm , 0 , 360 *degree , 0 , 180 *degree) ;

  logicWorld = new G4LogicalVolume( solidWorld , air , "World", 0 , 0 , 0 );
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 logicWorld,      // its logical volume
				 "World",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0);              // copy number





  //  G4GDMLParser parser;
  //  parser.Read("LGuide/Lguide_vahe.gdml");
  //  parser.Read("LGuide/FastradModel.gdml");
  //  physiWorld = parser.GetWorldVolume();

  //  G4LogicalVolume *logWorldLG = LGuide->GetLogicalVolume();
 

  ///  G4LogicalVolume *logLGuide = parser.ParseST( "LGuide/Lguide_vahe" , Air , Glass );

  //  parser.Write("aa.geom" , LGuide );

   ///////////////////////////////////////////////////////////////////////
   //
   // Example how to retrieve Auxiliary Information for sensitive detector
   //
   // const G4GDMLAuxMapType* auxmap = parser.GetAuxMap();
   // std::cout << "Found " << auxmap->size()
   //           << " volume(s) with auxiliary information."
   //           << G4endl << G4endl;
   // for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
   //     iter!=auxmap->end(); iter++) 
   //   {
   //     G4cout << "Volume " << ((*iter).first)->GetName()
   // 	      << " has the following list of auxiliary information: "
   // 	      << G4endl << G4endl;
   //     for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
   // 	    vit!=(*iter).second.end(); vit++)
   // 	 {
   // 	   std::cout << "--> Type: " << (*vit).type
   // 		     << " Value: " << (*vit).value << std::endl;
   // 	 }
   //   }
   // G4cout << G4endl;

  //--------- Sensitive detector -------------------------------------

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //-- Make the PMT sensitive detector
  HCalWLSPmtSD* PmtSD = new HCalWLSPmtSD(G4String("PmtSD"));
  SDman->AddNewDetector(PmtSD);
  // G4LogicalVolume* logPMT = parser.GetVolume("lPMT");
  // logPMT->SetSensitiveDetector(PmtSD);
  // G4LogicalVolume* logWLS = parser.GetVolume("lWLSGDML");
  // logWLS->GetMaterial()->GetMaterialPropertiesTable()->DumpTable();

  // G4LogicalVolume* logElement9 = parser.GetVolume("Element_Step_6");

  // G4LogicalVolume* logElement0 = parser.GetVolume("Element_Step_0");
  // G4LogicalVolume* logElement1 = parser.GetVolume("Element_Step_1");
  // G4LogicalVolume* logElement2 = parser.GetVolume("Element_Step_2");
  // G4LogicalVolume* logElement3 = parser.GetVolume("Element_Step_3");

  // G4LogicalVolume* logWLSToLGPlane = parser.GetVolume("lBoxWtoLGPlane");

  // G4LogicalVolume* logSeg10 = parser.GetVolume("lSeg10");
  // G4LogicalVolume* logSeg11 = parser.GetVolume("lSeg11");

  // G4LogicalVolume* logSeg13 = parser.GetVolume("lSeg13");
  // G4LogicalVolume* logSeg14 = parser.GetVolume("lSeg14");
  // G4LogicalVolume* logSeg15 = parser.GetVolume("lSeg15");
  // G4LogicalVolume* logSeg16 = parser.GetVolume("lSeg16");
  

  //-- Visualization properties
  //  G4VisAttributes *logTargetEnclVis = new G4VisAttributes(G4Colour::Magenta());
  //   logTargetEnclVis->SetForceWireframe(true);
  // logTargetEnclVis->SetForceAuxEdgeVisible(true);
  //  logTargetEnclVis->SetForceLineSegmentsPerCircle(202);

  // logTargetEnclVis->SetForceSolid(true);
  //  logSeg13->SetVisAttributes(logTargetEnclVis);
  //  logSeg16->SetVisAttributes(logTargetEnclVis);
  // logElement0->SetVisAttributes(logTargetEnclVis);
  // logElement1->SetVisAttributes(logTargetEnclVis);
  // logElement2->SetVisAttributes(logTargetEnclVis);
  // logElement3->SetVisAttributes(logTargetEnclVis);

  //  G4LogicalVolume* logWLSEnd = parser.GetVolume("lWLSEnd");

  //------------------------------

  G4double Z_position = 0.0;
  //
  HCalWLS* DetWLS = new HCalWLS();

  G4VPhysicalVolume* physDetWLS = DetWLS->ConstructWLS( logicWorld , physiWorld , G4ThreeVector( 0.0 , 0.0 , 0.0 ) );

// //--------- Visualization attributes -------------------------------------------

  // G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  // logicWorld->SetVisAttributes(BoxVisAtt);  
  // logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

  // logWLS->SetVisAttributes(G4Color::Green());

  // logSeg10->SetVisAttributes(G4Color::Cyan());
  // logSeg11->SetVisAttributes(G4Color::Cyan());
  // logSeg14->SetVisAttributes(G4Color::Green());
  // logSeg15->SetVisAttributes(G4Color::Green());
  // //  logWLSEnd->SetVisAttributes(G4Color::Cyan());
  // //  logElement9->SetVisAttributes(G4Color::Cyan());

  // logPMT->SetVisAttributes(G4Color::Red());
  // logWLSToLGPlane ->SetVisAttributes(G4Color::Blue());
 
//--------- example of User Limits -------------------------------

  // below is an example of how to set tracking constraints in a given
  // logical volume(see also in N02PhysicsList how to setup the processes
  // G4StepLimiter or G4UserSpecialCuts).
    
  // Sets a max Step length in the tracker region, with G4StepLimiter
  //
  //  G4double maxStep = 0.5*ChamberWidth; 
  //  logicTracker->SetUserLimits(new G4UserLimits(maxStep));
  
  // Set additional contraints on the track, with G4UserSpecialCuts
  //
  // G4double maxLength = 2*fTrackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //                                               minEkin));
  
  return physiWorld;
}
