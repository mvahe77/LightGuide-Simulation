// Author: Vahe Mamyan
// -------------------------------------------------------------------
#ifndef HCalWLSMaterialManager_hh
#define HCalWLSMaterialManager_hh

#include <vector>
#include <map>
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"

//-----------------------------------------------------------------------------
#include <fstream>

class HCalWLSMaterialManager
{
public:
  virtual ~HCalWLSMaterialManager();

  // method to call to create an instance of this class
  static HCalWLSMaterialManager* getInstance();

  void  print() { G4cout << " Material Manager" << G4endl; }
  void  BuildMaterials();
  G4Material* FindMaterial( const G4String name ) { 
    return HCalWLSMaterialManager::fMaterialMap[name]; }
  G4OpticalSurface* FindOpticalSurface( const G4String name ) { 
    return HCalWLSMaterialManager::fOpticalSurfaceMap[name]; 
  }
private:
  //private constructor in order to create a singleton
  
  HCalWLSMaterialManager();
  static HCalWLSMaterialManager*   instance;
  std::map<G4String,G4Material*> fMaterialMap;
  std::map<G4String,G4OpticalSurface*> fOpticalSurfaceMap;
};

#endif
