//
#ifndef HCalWLSStackingAction_H
#define HCalWLSStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//-----------------------------------------------------------------------------

class HCalWLSStackingAction : public G4UserStackingAction
{
  public:
    HCalWLSStackingAction();
   ~HCalWLSStackingAction();

  public:
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int cerCounter;
};

//-----------------------------------------------------------------------------

#endif

