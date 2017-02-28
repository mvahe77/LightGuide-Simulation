//
#include "G4VProcess.hh"
#include <fstream>
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "HCalWLSConfig.hh"
#include "G4Step.hh"

using namespace std;

HCalWLSConfig* HCalWLSConfig::instance = 0;

HCalWLSConfig::HCalWLSConfig()
{
  G4cout << " A single copy of HCalWLSConfig class has been created " << G4endl;
  Init();
}
//------------------------------------------------------------------------------
HCalWLSConfig::~HCalWLSConfig() 
{
  G4cout << "Destructor for HCalWLSConfig is called" << G4endl;
}
//------------------------------------------------------------------------------
HCalWLSConfig* HCalWLSConfig::getInstance()
{
  if ( instance == 0 ) instance = new HCalWLSConfig;
  return instance;
}
//------------------------------------------------------------------------------
void  HCalWLSConfig::Init()
{
  G4cout << "-----------------------------------------------------" << G4endl;
  G4cout << "----------------   WLS properties   -----------------" << G4endl;
  G4cout << "-----------------------------------------------------" << G4endl;
  
  string::size_type loc_beg;
  string line;  
  string subline;

  ifstream fin("wls_config.dat" , ios::in);
  if( !fin.is_open() ) { G4cerr << "Can't open file wls_config.dat " << G4endl; exit(1);}

  getline( fin , line );
  getline( fin , line );
  getline( fin , line );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  ScintRad = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );
  
  getline( fin , line );
  loc_beg = line.find(":" , 0);
  ScinThick = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  ScinSection = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  ScinToPMTFace = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  LGuideL = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  subline = line.substr( loc_beg + 1 , ( line.size() - loc_beg ) );
  sscanf( subline.c_str() , "%lf, %lf" , &LGuideWidth , &LGuideHigh );

  getline( fin , line );
  loc_beg = line.find(":" , 0);
  ScinToWLSAirGap = atof( (line.substr( loc_beg + 1 , ( line.size() - loc_beg ) )).c_str() );

  G4cout << "Scintilator radius: "           << ScintRad      << G4endl
	 << "Scintilator thickness: "        << ScinThick     << G4endl
	 << "Scintilator section: "          << ScinSection   << G4endl
	 << "Scintilator to PMT face: "      << ScinToPMTFace << G4endl
	 << "Light guide length: "           << LGuideL       << G4endl
	 << "Light guide width and high: "   << LGuideWidth   << " " << LGuideHigh << G4endl
	 << "Air gap between SCIN and WLS: " << ScinToWLSAirGap
	 << G4endl;

  // -- Read single photoelectron form

  TFile *ff = new TFile("spe_spl.root");
  if(!ff->IsOpen()) { G4cerr << "Can't open file spe_spl.root" << G4endl; exit(1);};
  fSPE = dynamic_cast<TSpline*>(ff->Get("spe"));
}
