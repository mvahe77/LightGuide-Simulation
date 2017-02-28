// --
#include "G4VProcess.hh"
#include <fstream>
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "HCalWLSMaterials.hh"
#include "G4Step.hh"
#include "G4NistManager.hh"

using namespace std;

HCalWLSMaterialManager* HCalWLSMaterialManager::instance = 0;

HCalWLSMaterialManager::HCalWLSMaterialManager()
{
  G4cout << " A single copy of Material class has been created " << G4endl;
  BuildMaterials();  
}
//------------------------------------------------------------------------------
HCalWLSMaterialManager::~HCalWLSMaterialManager() 
{
  G4cout << "Destructor for materials maneger is called" << G4endl;
}
//------------------------------------------------------------------------------
HCalWLSMaterialManager* HCalWLSMaterialManager::getInstance()
{
  if ( instance == 0 ) instance = new HCalWLSMaterialManager;
  G4cout << "Create Material manager " << G4endl;
  return instance;
}
//------------------------------------------------------------------------------
void  HCalWLSMaterialManager::BuildMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4double a, z;
  G4double density;
  G4int nel, natoms;

  G4Material* vacum       = man->FindOrBuildMaterial("G4_Galactic");   // vacuum
  G4Material* polystyrene = man->FindOrBuildMaterial("G4_POLYSTYRENE");
  G4Material* pterphenyle = man->FindOrBuildMaterial("G4_TERPHENYL");
  G4Material* Iron        = man->FindOrBuildMaterial("G4_Fe");

  //Elements
  G4Element* H  = new G4Element("Hidrogen"  , "H"  , z= 1.0 , a=  1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"    , "C"  , z= 6.0 , a= 12.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"    , "O"  , z= 8.0 , a= 16.00*g/mole);
  G4Element* Si = new G4Element("Silicon"   , "Si" , z=14.0 , a= 28.09*g/mole);
  G4Element* Na = new G4Element("Sodium"    , "Na" , z=11.0 , a= 22.99*g/mole);
  G4Element* I  = new G4Element("Iodine"    , "I"  , z=53.0 , a=126.90*g/mole);
  G4Element *Gd = new G4Element("Gadolinium", "Gd" , z=64.0 , a=157.25*g/mole);
  G4Element* Sb = new G4Element("Antimony"  , "Sb" , z=51.0 , a= 121.76*g/mole);
  G4Element* Cs = new G4Element("Cesium"    , "Cs" , z=55.0 , a= 132.91*g/mole);
  G4Element* K  = new G4Element("Potassium" , "K"  , z=19.0 , a= 39.0983*g/mole);
  G4Element* Fe = new G4Element("Iron"      , "Fe" , z=26.0 , a= 55.85*g/mole);

  //- Air
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");

  //- Steel

  G4Material* Steel = new  G4Material("Steel", density=7.85*g/cm3, nel=2);
  Steel->AddElement(Fe , 0.98);
  Steel->AddElement(C  , 0.02);

  //- EJ-232

  G4Material* EJ232 = new G4Material("EJ232",density=1.02*g/cm3, nel=2,kStateSolid,293.15*kelvin,1.0*atmosphere);
  EJ232->AddElement(H , natoms=11);
  EJ232->AddElement(C , natoms=10);

  //- EJ-280 Wave length shifter blue to green

  G4Material* EJ280 = new G4Material("EJ280",density=1.023*g/cm3, nel=2,kStateSolid,293.15*kelvin,1.0*atmosphere);
  EJ280->AddElement(H , natoms=11);
  EJ280->AddElement(C , natoms=10);


  //GSO  (added 7/6/2010 gbf)

  G4Material* GSiO = new G4Material("GSiO", density=6.71*g/cm3, nel=3);
  GSiO->AddElement(Gd, natoms=2);
  GSiO->AddElement(Si, natoms=1);
  GSiO->AddElement(O , natoms=5);
  GSiO->GetIonisation()->SetBirksConstant(5.25); 

  //Aluminum
  G4Material* Al = new G4Material("Al",z=13.,a=26.98*g/mole,density=2.7*g/cm3);

  //Glass
  G4Material* Glass = new G4Material("Glass", density=1.18*g/cm3,2);
  Glass->AddElement(C , 91.533*perCent);
  Glass->AddElement(H ,  8.467*perCent);

 // -- Bialkali photocathode K2CsSb 

  G4Material* BialkaliK2CsSb = new G4Material ("BialkaliK2CsSb" , density= 2.9 *g/cm3 , 3 ); // density need to be checked later 
  
  BialkaliK2CsSb->AddElement( K  , 2 );
  BialkaliK2CsSb->AddElement( Cs , 1 );
  BialkaliK2CsSb->AddElement( Sb , 1 );

  // Print all the materials defined.
  //
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  // -- Optical properties of materials

  // -- EJ232 optical properties 
  
  const G4int nEntriesEJ232 = 66;
  G4double PhotonWaveLength[nEntriesEJ232] = 
    {
      235, 240, 245, 250, 255, 260, 265, 270, 275, 280,
      285, 290, 295, 300, 305, 310, 315, 320, 325, 330,
      335, 340, 345, 350, 355, 360, 365, 370, 375, 380,
      385, 390, 395, 400, 405, 410, 415, 420, 425, 430,
      435, 440, 445, 450, 455, 460, 465, 470, 475, 480,
      485, 490, 495, 500, 505, 510, 515, 520, 525, 530,
      535, 540, 545, 550, 555, 560 
    };
  // -- milimters, converted to cm in the loop
  G4double ABSL_EJ232[nEntriesEJ232] = 
    {
      0.0038,0.0036,0.0033,0.0031,0.0027,0.0024,0.0020,0.0016,0.0014,0.0011,
      0.0010,0.0009,0.0008,0.0007,0.0007,0.0007,0.0007,0.0008,0.0010,0.0012,
      0.0018,0.0030,0.0062,0.0228,0.4880,0.9760,1.7080,6.8321,17.700,24.970,
      33.210,53.670,161.61,995.00,995.00,995.00,995.00,995.00,995.00,995.00,
      995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,
      995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,995.00,
      995.00,995.00,995.00,995.00,995.00,995.00
    };
  G4double FAST_EJ232[nEntriesEJ232] = 
    {
      0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
      0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.01,
      0.02, 0.05, 0.12, 0.36, 0.52, 0.52, 0.71, 0.92, 1.00, 0.88,
      0.83, 0.84, 0.77, 0.63, 0.53, 0.45, 0.39, 0.34, 0.30, 0.24,
      0.19, 0.14, 0.11, 0.08, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.01, 0.01, 0.00, 0.00, 0.00, 0.00, 0.00,
      0.00, 0.00, 0.00, 0.00, 0.00,0.00
    };
  G4double PhotonEnergyEJ232[nEntriesEJ232];
  G4double RefractiveIndexEJ232[nEntriesEJ232];
  for(int ii = 0; ii < nEntriesEJ232; ii++) {
    PhotonEnergyEJ232[ii] = 1240.0/(PhotonWaveLength[ii]) *eV;
    RefractiveIndexEJ232[ii] = 1.58;
    ABSL_EJ232[ii]           = ABSL_EJ232[ii]*mm;
  }

  G4MaterialPropertiesTable* MPT_EJ232 = new G4MaterialPropertiesTable();
  MPT_EJ232->AddProperty("RINDEX"       , PhotonEnergyEJ232 , RefractiveIndexEJ232 , nEntriesEJ232);
  MPT_EJ232->AddProperty("FASTCOMPONENT", PhotonEnergyEJ232 , FAST_EJ232           , nEntriesEJ232);
  MPT_EJ232->AddProperty("ABSLENGTH",     PhotonEnergyEJ232 , ABSL_EJ232           , nEntriesEJ232);

  MPT_EJ232->AddConstProperty("SCINTILLATIONYIELD", 8400.0/MeV);
  //  MPT_EJ232->AddConstProperty("SCINTILLATIONYIELD", 50.0/MeV);
  MPT_EJ232->AddConstProperty("RESOLUTIONSCALE", 1.0);
  MPT_EJ232->AddConstProperty("FASTTIMECONSTANT",1.40*ns);
  MPT_EJ232->AddConstProperty("SLOWTIMECONSTANT",1.40*ns);
  MPT_EJ232->AddConstProperty("YIELDRATIO",1.0);

  EJ232->SetMaterialPropertiesTable(MPT_EJ232);
  //  EJ232->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  EJ232->GetIonisation()->SetBirksConstant(0.000001*mm/MeV); // -- no saturation

  G4double sigalpha;

  // -- EJ280 optical properties 

  // -- units are cm, will be converted in the loop
  const G4int nEntriesEJ280 = 66;
  G4double AbsWLSfiberEJ280[nEntriesEJ280] =
    {
      0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,
      0.275,0.214,0.164,0.123,0.095,0.075,0.061,0.050,0.043,0.036,
      0.032,0.029,0.026,0.024,0.024,0.025,0.026,0.030,0.036,0.045,
      0.060,0.084,0.135,0.270,0.710,5.400,96.00,178.0,178.0,178.0,
      178.0,178.0,178.0,178.0,178.0,178.0,178.0,178.0,178.0,178.0,
      178.0,178.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,
      13496.0,13496.0,13496.0,13496.0,13496.0,13496.0
    };

  // G4double AbsWLSfiberEJ280[nEntriesEJ280] =
  //   {
  //     0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,0.329,
  //     0.275,0.214,0.164,0.123,0.095,0.075,0.061,0.050,0.043,0.036,
  //     0.032,0.029,0.026,0.024,0.024,0.025,0.026,0.030,0.036,0.045,
  //     0.060,0.084,0.135,0.270,0.710,5.400,96.00,245.0,450.0,964.0,
  //     3374.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,
  //     13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,13496.0,
  //     13496.0,13496.0,13496.0,13496.0,13496.0,13496.0
  //   };
  G4double EmissionFibEJ280[nEntriesEJ280] =
    {
      0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,
      0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,
      0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.016,0.060,
      0.141,0.423,0.786,0.853,0.756,0.754,0.899,1.000,0.920,0.740,
      0.610,0.549,0.514,0.460,0.395,0.300,0.228,0.198,0.173,0.145,
      0.120,0.092,0.075,0.060,0.050,0.042,0.033,0.029,0.022,0.016,
      0.013,0.011,0.000,0.000,0.000,0.000
    };
  G4double PhotonEnergyEJ280[nEntriesEJ280];
  G4double RefractiveIndexEJ280[nEntriesEJ280];

  for(int ii = 0; ii < nEntriesEJ280; ii++) {
    PhotonEnergyEJ280[ii]    = 1240.0/(PhotonWaveLength[ii]) *eV;
    RefractiveIndexEJ280[ii] = 1.58;
    AbsWLSfiberEJ280[ii]     = AbsWLSfiberEJ280[ii]*cm;        
  }
  G4MaterialPropertiesTable* MPT_EJ280 = new G4MaterialPropertiesTable();

  MPT_EJ280->AddProperty("RINDEX"              , PhotonEnergyEJ280 , RefractiveIndexEJ280 , nEntriesEJ280);
  MPT_EJ280->AddProperty("WLSABSLENGTH"        , PhotonEnergyEJ280 , AbsWLSfiberEJ280     , nEntriesEJ280);
  MPT_EJ280->AddProperty("WLSCOMPONENT"        , PhotonEnergyEJ280 , EmissionFibEJ280     , nEntriesEJ280);
  MPT_EJ280->AddConstProperty("WLSTIMECONSTANT", 1.5*ns);

  EJ280->SetMaterialPropertiesTable(MPT_EJ280);

  // -- Foil surface
  //
  G4double Foil_refl[nEntriesEJ232] = 
    {
      0.931, 0.932, 0.932, 0.932, 0.931, 0.930, 0.929, 0.928, 0.926, 0.924,
      0.922, 0.920, 0.918, 0.916, 0.913, 0.911, 0.909, 0.906, 0.904, 0.901,
      0.899, 0.896, 0.894, 0.892, 0.890, 0.887, 0.885, 0.883, 0.881, 0.880,
      0.878, 0.876, 0.874, 0.873, 0.872, 0.870, 0.869, 0.868, 0.867, 0.866,
      0.865, 0.864, 0.863, 0.863, 0.862, 0.862, 0.861, 0.861, 0.861, 0.860,
      0.860, 0.860, 0.860, 0.860, 0.860, 0.860, 0.860, 0.860, 0.860, 0.860,
      0.860, 0.860, 0.860, 0.860, 0.860, 0.861      
    };
  G4double Foil_AirGap[nEntriesEJ232] = 
    {
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0
    };

  G4double Zero_refl[nEntriesEJ232];

  G4double Foil_efficiency[nEntriesEJ232];
  for(int ii = 0; ii < nEntriesEJ280; ii++) {
    Foil_efficiency[ii] = 0.2;
    Zero_refl[ii]       = 0.0;
  }
  //  G4OpticalSurface * OpFoilSurface = new G4OpticalSurface("FoilSurface", unified , polished , dielectric_metal );

  G4double aRindx[] = { 1.00 , 1.00 };
  G4double aRefl[]  = { 0.90 , 0.90 };
  G4double aSpike[] = { 1.00 , 1.00 };
  G4double aLobe[]  = { 0.00 , 0.00 };
  G4double aBack[]  = { 0.00 , 0.00 };
  G4double aEner[]  = { 2*eV , 6*eV };

  G4OpticalSurface * OpFoilSurface = new G4OpticalSurface( "FoilSurface", unified , polishedbackpainted , dielectric_dielectric , 0.0 *degree );

  G4MaterialPropertiesTable *foil_mpt = new G4MaterialPropertiesTable();
  //  foil_mpt->AddProperty("REFLECTIVITY", PhotonEnergyEJ280 , Foil_refl   , nEntriesEJ232 );
  //  foil_mpt->AddProperty("RINDEX"      , PhotonEnergyEJ280 , Foil_AirGap , nEntriesEJ232 );

  foil_mpt->AddProperty("RINDEX"               , aEner , aRindx  , 2 );
  foil_mpt->AddProperty("REFLECTIVITY"         , aEner , aRefl   , 2 );
  foil_mpt->AddProperty("SPECULARSPIKECONSTANT", aEner , aSpike  , 2 );
  foil_mpt->AddProperty("SPECULARLOBECONSTANT" , aEner , aLobe   , 2 );
  foil_mpt->AddProperty("BACKSCATTERCONSTANT"  , aEner , aBack   , 2 );

  OpFoilSurface->SetMaterialPropertiesTable(foil_mpt);

  fOpticalSurfaceMap[G4String("Foil")] = OpFoilSurface;
  Al->SetMaterialPropertiesTable(foil_mpt);  
  Al->GetMaterialPropertiesTable()->DumpTable();

  G4double PEn[] = { 2 *eV , 6 *eV };
  G4double NoRefl[] = { 1.0 , 1.0 };

  G4OpticalSurface * NoReflSurf = new G4OpticalSurface( "NoReflSurf", unified , polished , dielectric_dielectric );
  G4MaterialPropertiesTable *NoReflSurf_mpt = new G4MaterialPropertiesTable();
  NoReflSurf_mpt->AddProperty("REFLECTIVITY", PEn , NoRefl , nEntriesEJ232 );
  NoReflSurf->SetMaterialPropertiesTable(NoReflSurf_mpt);
  fOpticalSurfaceMap[G4String("NoReflSurf")] = NoReflSurf;

  // -- Surface between far end of WLS and light absorber 
  G4double Absorber_reflectivity[nEntriesEJ232];
  G4double Absorber_efficiency[nEntriesEJ232];
  for(int ii = 0; ii < nEntriesEJ280; ii++) {
    Absorber_efficiency[ii]   = 1.0;
    Absorber_reflectivity[ii] = 0.0;
  }

  G4OpticalSurface * AbsorberSurface = new G4OpticalSurface("AbsorberSurface", unified , polished , dielectric_metal);
  
  G4MaterialPropertiesTable *Absorber_mpt = new G4MaterialPropertiesTable();
  
  Absorber_mpt->AddProperty("REFLECTIVITY", PhotonEnergyEJ280 , Absorber_reflectivity , nEntriesEJ232 );

  AbsorberSurface->SetMaterialPropertiesTable(Absorber_mpt);

  fOpticalSurfaceMap[G4String("Absorber")] = AbsorberSurface;

  // -- Surface between WLS and air
  G4double WLS_AirGapRefrIndex[nEntriesEJ232];
  G4double WLS_reflectivity[nEntriesEJ232];
  G4double WLS_SpecularLobe[nEntriesEJ232];
  G4double WLS_SpecularSpike[nEntriesEJ232];
  G4double WLS_Backscatter[nEntriesEJ232];
  
  for(int ii = 0; ii < nEntriesEJ280; ii++) {
    WLS_AirGapRefrIndex[ii] = 1.0;
    WLS_reflectivity[ii]    = 0.0;
    WLS_SpecularLobe[ii]    = 0.01;
    WLS_SpecularSpike[ii]   = 0.99;
    WLS_Backscatter[ii]     = 0.0;
  }

  //  G4OpticalSurface *osWLSToAir = new G4OpticalSurface("osWLSToAir" , unified , groundbackpainted , dielectric_dielectric);
  //  G4OpticalSurface *osWLSToAir = new G4OpticalSurface("osWLSToAir" , unified , polishedbackpainted  , dielectric_dielectric);
  G4OpticalSurface *osWLSToAir = new G4OpticalSurface("osWLSToAir" , unified , polished , dielectric_dielectric );
  //  G4OpticalSurface *osWLSToAir = 
  //    new G4OpticalSurface("osWLSToAir" , unified , ground , dielectric_dielectric , sigalpha=0.1*deg);

  G4MaterialPropertiesTable *osWLSToAir_mpt = new G4MaterialPropertiesTable();
  
  //  osWLSToAir_mpt->AddProperty("RINDEX"                 , PhotonEnergyEJ280 , WLS_AirGapRefrIndex , nEntriesEJ280);
  //  osWLSToAir_mpt->AddProperty("REFLECTIVITY"           , PhotonEnergyEJ280 , Foil_refl           , nEntriesEJ280); // wrapped 
  // -- Test if this works right
  //  osWLSToAir_mpt->AddProperty("REFLECTIVITY"           , PhotonEnergyEJ280 , WLS_reflectivity    , nEntriesEJ280); // wrapped 
  osWLSToAir_mpt->AddProperty("SPECULARLOBECONSTANT"   , PhotonEnergyEJ280 , WLS_SpecularLobe    , nEntriesEJ280);
  osWLSToAir_mpt->AddProperty("SPECULARSPIKECONSTANT"  , PhotonEnergyEJ280 , WLS_SpecularSpike   , nEntriesEJ280);
  osWLSToAir_mpt->AddProperty("BACKSCATTERCONSTANT"    , PhotonEnergyEJ280 , WLS_Backscatter     , nEntriesEJ280);
  
  osWLSToAir->SetMaterialPropertiesTable(osWLSToAir_mpt);
  
  fOpticalSurfaceMap[G4String("osWLSToAir")] = osWLSToAir;

  // -- Surface between Air to air


  // -- Air optical properties

  G4double RefractiveIndexAir[nEntriesEJ232] =
    { 
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00
    };
  G4MaterialPropertiesTable* MPT_Air = new G4MaterialPropertiesTable();
  MPT_Air->AddProperty("RINDEX", PhotonEnergyEJ232 , RefractiveIndexAir , nEntriesEJ232);
  Air->SetMaterialPropertiesTable(MPT_Air);

  // -- Scin is wrapped in Al foil
  G4OpticalSurface *OpAlSurface = new G4OpticalSurface("AlSurface" , unified , polished , dielectric_metal );

  G4MaterialPropertiesTable *OpSurfaceProperty = new G4MaterialPropertiesTable();

  OpSurfaceProperty->AddProperty("REFLECTIVITY", PhotonEnergyEJ280 , Foil_refl       , nEntriesEJ232);
  OpSurfaceProperty->AddProperty("EFFICIENCY"  , PhotonEnergyEJ280 , Foil_efficiency , nEntriesEJ232);
  
  OpAlSurface -> SetMaterialPropertiesTable(OpSurfaceProperty);
  fOpticalSurfaceMap[G4String("ScinFoilSurf")] = OpAlSurface;

  // -- Optical surface between scintillator and air gap
  G4double SCIN_reflectivity[nEntriesEJ232];
  G4double SCIN_SpecularLobe[nEntriesEJ232];
  G4double SCIN_SpecularSpike[nEntriesEJ232];
  G4double SCIN_Backscatter[nEntriesEJ232];
  
  for(int ii = 0; ii < nEntriesEJ280; ii++) {
    SCIN_reflectivity[ii]    = 1.0;
    SCIN_SpecularLobe[ii]    = 0.01;
    SCIN_SpecularSpike[ii]   = 0.99;
    SCIN_Backscatter[ii]     = 0.0;
  }
  
  G4OpticalSurface *osScinToAirGap = 
    //    new G4OpticalSurface("osScinToAirGap" , unified , ground , dielectric_dielectric, sigalpha=1.3*deg);
    new G4OpticalSurface("osScinToAirGap" , unified , polished , dielectric_dielectric);

  G4MaterialPropertiesTable *ScinToAirGap_mpt = new G4MaterialPropertiesTable();
  ScinToAirGap_mpt->AddProperty("REFLECTIVITY"           , PhotonEnergyEJ280 , SCIN_reflectivity  , nEntriesEJ280);
  ScinToAirGap_mpt->AddProperty("SPECULARLOBECONSTANT"   , PhotonEnergyEJ280 , SCIN_SpecularLobe  , nEntriesEJ280);
  ScinToAirGap_mpt->AddProperty("SPECULARSPIKECONSTANT"  , PhotonEnergyEJ280 , SCIN_SpecularSpike , nEntriesEJ280);
  ScinToAirGap_mpt->AddProperty("BACKSCATTERCONSTANT"    , PhotonEnergyEJ280 , SCIN_Backscatter   , nEntriesEJ280);

  osScinToAirGap->SetMaterialPropertiesTable(ScinToAirGap_mpt);

  fOpticalSurfaceMap[G4String("ScinToAirGap")] = osScinToAirGap;

  // -- Cathode optical properties

  // -- Glass optical properties

  G4double Glass_RIND[nEntriesEJ232] =
    { 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 
    };

  // G4double Glass_RIND[nEntriesEJ232] =
  //   { 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 
  //   };

  // G4double Glass_AbsLength[nEntriesEJ232]=
  //   { 
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm ,
  //     4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm , 4200.0*cm 
  //   };


  G4double Glass_AbsLength[nEntriesEJ232]=
    { 
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm ,
      420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm , 420000.0*cm 
    };

  G4MaterialPropertiesTable *Glass_mt = new G4MaterialPropertiesTable();
  Glass_mt->AddProperty("ABSLENGTH", PhotonEnergyEJ280 , Glass_AbsLength , nEntriesEJ232 );
  Glass_mt->AddProperty("RINDEX"   , PhotonEnergyEJ280 , Glass_RIND      , nEntriesEJ232 );
  Glass->SetMaterialPropertiesTable(Glass_mt);

  
  G4Material* PMMAGlass = new G4Material("PMMAGlass",density=1.18*g/cm3, nel=3 , kStateSolid ,293.15*kelvin ,1.0*atmosphere);
  PMMAGlass->AddElement(C , natoms=5);
  PMMAGlass->AddElement(O , natoms=2);
  PMMAGlass->AddElement(H , natoms=8);

  // G4double RefractiveIndexPMMAGlass[] = 
  //   {
  //     7.3695,6.6629,6.0365,5.4807,4.9874,4.5495,4.1611,3.8166,3.5115,3.2416,
  //     3.0034,2.7935,2.6093,2.4479,2.3071,2.1848,2.0789,1.9876,1.9093,1.8423,
  //     1.7853,1.7371,1.6963,1.6621,1.6334,1.6094,1.5895,1.5730,1.5593,1.5480,
  //     1.5387,1.5311,1.5248,1.5197,1.5156,1.5122,1.5094,1.5072,1.5054,1.5039,
  //     1.5027,1.5017,1.5009,1.5002,1.4996,1.4991,1.4987,1.4983,1.4980,1.4977,
  //     1.4974,1.4971,1.4968,1.4965,1.4962,1.4960,1.4957,1.4954,1.4951,1.4948,
  //     1.4945,1.4942,1.4939,1.4936,1.4933,1.4930
  //   };

  G4double RefractiveIndexPMMAGlass[] = 
    { 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 
      1.49 , 1.49 , 1.49 , 1.49 , 1.49 , 1.49 
    };
  // G4double RefractiveIndexPMMAGlass[] = 
  //   { 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 
  //     1.58 , 1.58 , 1.58 , 1.58 , 1.58 , 1.58 
  //   };
  
  G4double ABSL_PMMAGlass[] = 
    {
      1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
      1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
      1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 8.7e-02*cm, 1.2e-01*cm, 2.2e-01*cm,
      5.6e-01*cm, 8.9e-01*cm, 1.2e+00*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
      2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
      2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
      2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm
    };

  // G4double ABSL_PMMAGlass[] = 
  //   {
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 8.7e-02*cm, 1.2e-01*cm, 2.2e-01*cm,
  //     5.6e-01*cm, 8.9e-01*cm, 1.2e+00*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm,
  //     1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm,
  //     1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm,
  //     1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm, 1.5e+02*cm
  //   };

  // G4double ABSL_PMMAGlass[] = 
  //   {
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm,
  //     1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 1.0e-05*cm, 8.7e-02*cm, 1.2e-01*cm, 2.2e-01*cm,
  //     5.6e-01*cm, 8.9e-01*cm, 1.2e+00*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
  //     2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
  //     2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm,
  //     2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm, 2.5e+02*cm
  //   };


  G4MaterialPropertiesTable* MPT_PMMAGlass = new G4MaterialPropertiesTable();
  MPT_PMMAGlass->AddProperty("RINDEX"       , PhotonEnergyEJ280 , RefractiveIndexPMMAGlass , nEntriesEJ232);
  MPT_PMMAGlass->AddProperty("ABSLENGTH"    , PhotonEnergyEJ280 , ABSL_PMMAGlass           , nEntriesEJ232);
  PMMAGlass->SetMaterialPropertiesTable(MPT_PMMAGlass);

  // -- Optical surface between volumes

  // -- End optical surface between volumes


  // Print all the materials defined.

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl; 
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;  
  G4cout << G4endl << "End defined materials " << G4endl << G4endl; 
}
