//
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  void ConstructParticle();
    
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void SetCutForProton(G4double);
        
  void AddPhysicsList(const G4String& name);
  void ConstructProcess();
  void List();
  void DoOptics(G4bool value ) { IsOptics=value; }
  void DoOpticsDebug(G4int value ) { OpticsDebug=value; }
  
private:

  void SetBuilderList0(G4bool flagHP = false);
  void SetBuilderList1(G4bool flagHP = false);
  void SetBuilderList2(G4bool flagHP = false);
  void SetBuilderList3(G4bool flagHP = false);
  void SetBuilderList4(G4bool flagHP = false);
  void SetBuilderList5(G4bool flagHP = false);
  void SetBuilderList6(G4bool flagHP = false);

  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4double cutForOpPhoton;

  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  particleList;
  std::vector<G4VPhysicsConstructor*>  hadronPhys;
    
  PhysicsListMessenger* pMessenger;
  G4bool dump;
  G4bool IsOptics;
  G4int  OpticsDebug;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

