//
#include "HCalWLSPrimaryGeneratorAction.hh"
#include "HCalWLSDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "CLHEP/Random/RandFlat.h"

#include "TMath.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "HCalWLSConfig.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HCalWLSPrimaryGeneratorAction::HCalWLSPrimaryGeneratorAction(HCalWLSDetectorConstruction* myDC)
:myDetector(myDC)
{
  G4cout << "Call HCalWLSPrimaryGeneratorAction" << G4endl;
  analysisManager = HCalWLSAnalysisManager::getInstance();
  configManager   = HCalWLSConfig::getInstance();

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

// default particle

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  //  G4ParticleDefinition* particle = particleTable->FindParticle("mu-");

  G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");

  //  G4ParticleDefinition* particle = particleTable->FindParticle("neutron");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

  G4cout << "Constructor of HCalWLSPrimaryGeneratorAction called" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HCalWLSPrimaryGeneratorAction::~HCalWLSPrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HCalWLSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  static int nev = 0;

  G4double Pmom = 3.0*GeV;
  G4double posX , posY , posZ , nPx , nPy , nPz;

  Pmom = 5.0 *eV;

  posX = 0.1*cm * CLHEP::RandFlat::shoot(-1.0 , 1.0);
  posY = 0.1*cm * CLHEP::RandFlat::shoot(-1.0 , 1.0);
  posZ = 20.0*cm;

  G4double ScinR   = configManager->ScintRad;
  G4double Section = configManager->ScinSection;

  G4double RCut = sqrt(pow(ScinR,2) - pow(Section/2.0,2));

  G4double xrnd;
  G4double yrnd;
  G4double zrnd;

  while(1) {
    zrnd = CLHEP::RandFlat::shoot(-ScinR , ScinR);
    yrnd = CLHEP::RandFlat::shoot(-RCut  , ScinR);
    if( xrnd*xrnd + yrnd*yrnd < (ScinR-0.1)*(ScinR-0.1) ) break;
  }

  posX = 0.0  *cm;
  posY = 2.7497 *cm + yrnd *cm;
  posZ = (configManager->ScinToPMTFace - configManager->LGuideL/2) *cm + zrnd *cm;
  posZ = 40.0 *cm + zrnd *cm;

  posX = 0.0  *cm;
  posY = 10*cm;
  posZ = 40.0 *cm + zrnd *cm;  

  //  posX = 0.0  *cm;
  //  posY =  0.4*cm;
  //  posZ = 40.0 *cm + zrnd *cm;  


  analysisManager->fIncX = posX;
  analysisManager->fIncY = posY;

  // posX = 0.0;
  // posY = (configManager->LGuideHigh + 
  // 	  sqrt( pow(configManager->ScintRad,2)-pow(configManager->ScinSection/2.0,2 )) 
  // 	  + configManager->ScinToWLSAirGap)/4.0*cm;
  // posZ = configManager->LGuideL/2.0*cm - configManager->ScinThick/2.0*cm -1.0*cm;
  
  //  posX = -10.0;
  //  posY = 0.5/2.0*cm;
  //  posZ = 0.0*cm;

  nPx =  0.0;
  nPy = -1.0;
  nPz =  0.0;

  //---------------------

  // posX = -6.425  *cm;
  // posY = 0.25*cm;
  // posZ = -2.3  *cm;

  // nPx =  TMath::Sin(45.0*3.141592/180) ;
  // nPy =  0.0;
  // nPz = -TMath::Cos(45.0*3.141592/180) ;

  //  nPx = 1.0;
  //  nPy = 0.0;
  //  nPz = 0.0;
  // const G4double rad = pi/180.0;

  // nPx =  sin(30.0*rad);
  // nPy = -cos(30.0*rad);
  // nPz =  0.0;

  // nPx =  0.0;
  // nPy = -cos(30.5*rad);
  // nPz = -sin(30.5*rad);


  G4cout.setf ( ios::showpoint | ios::fixed );
  
  particleGun->SetParticleEnergy(Pmom);
  particleGun->SetParticlePosition( G4ThreeVector(posX,posY,posZ) );
  particleGun->SetParticleMomentumDirection( G4ThreeVector(nPx,nPy,nPz) );
  particleGun->GeneratePrimaryVertex(anEvent);

  nev++;
  //  G4cout << "Event = " << nev << G4endl;  
  // -- 

  analysisManager->fInitialEnergy = Pmom;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
