//
#ifndef HCalWLSDetectorConstruction_h
#define HCalWLSDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class HCalWLSDetectorMessenger;
class G4Tubs;
class G4Sphere;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HCalWLSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
     HCalWLSDetectorConstruction();
    ~HCalWLSDetectorConstruction();

  public:
  
     G4VPhysicalVolume* Construct();     
     
     void setChamberMaterial(G4String);
     
  private:

     G4Sphere*          solidWorld;    // pointer to the solid envelope 
     G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
     G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope

     G4Box*             solidLayer;  // pointer to the solid Layer
     G4LogicalVolume*   logicLayer;  // pointer to the logical Layer
     G4VPhysicalVolume* physiLayer;  // pointer to the physical Layer

     G4Box*             solidCalo;  // pointer to the solid Chamber
     G4LogicalVolume*   logicCalo;  // pointer to the logical Chamber
     G4VPhysicalVolume* physiCalo;  // pointer to the physical Chamber

     G4Tubs*            solidTubs;     // pointer to the solid Chamber
     G4LogicalVolume*   logicTubs;     // pointer to the logical Chamber
     G4VPhysicalVolume* physiTubs;     // pointer to the physical Chamber

     G4Box*             solidBlock;    // pointer to the solid Chamber
     G4LogicalVolume*   logicBlock;    // pointer to the logical Chamber
     G4VPhysicalVolume* physiBlock;    // pointer to the physical Chamber

     G4Box*             solidBlockBox;    // pointer to the solid Chamber
     G4LogicalVolume*   logicBlockBox;    // pointer to the logical Chamber
     G4VPhysicalVolume* physiBlockBox;    // pointer to the physical Chamber

     G4Box*             solidMylar;    // pointer to the solid Chamber
     G4LogicalVolume*   logicMylar;    // pointer to the logical Chamber
     G4VPhysicalVolume* physiMylar;    // pointer to the physical Chamber

     G4Box*             solidTedlar;    // pointer to the solid Chamber
     G4LogicalVolume*   logicTedlar;    // pointer to the logical Chamber
     G4VPhysicalVolume* physiTedlar;    // pointer to the physical Chamber
     
     G4Material*         LayerMater; // pointer to the chamber material     
     
     HCalWLSDetectorMessenger* detectorMessenger;  // pointer to the Messenger
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
