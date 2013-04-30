/*----------------------
   GATE version name: gate_v6

   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


/*!
  \class  GateHybridDoseActor
  \author fabien.baldacci@creatis.insa-lyon.fr
	  francois.smekens@creatis.insa-lyon.fr
  
 */

#ifndef GATEHYBRIDDOSEACTOR_HH
#define GATEHYBRIDDOSEACTOR_HH

#include "GateVImageActor.hh"
#include "GateActorManager.hh"
#include "G4UnitsTable.hh"
#include "GateHybridDoseActorMessenger.hh"
// #include "GateHybridMultiplicityActor.hh"
#include "GateImageWithStatistic.hh"
#include "GateMaterialMuHandler.hh"

class GateHybridDoseActor : public GateVImageActor
{
 public: 
  
  //-----------------------------------------------------------------------------
  // Actor name
  virtual ~GateHybridDoseActor();

  FCT_FOR_AUTO_CREATOR_ACTOR(GateHybridDoseActor)

  //-----------------------------------------------------------------------------
  // Constructs the sensor
  virtual void Construct();

  void EnableEdepImage(bool b) { mIsEdepImageEnabled = b; }
  void EnableDoseUncertaintyImage(bool b) { mIsDoseUncertaintyImageEnabled = b; }
  virtual void BeginOfRunAction(const G4Run*r);
  virtual void BeginOfEventAction(const G4Event * event);
  
  virtual void PreUserTrackingAction(const GateVVolume *, const G4Track* t);
  virtual void PostUserTrackingAction(const GateVVolume *, const G4Track* t);
  virtual void UserSteppingAction(const GateVVolume *, const G4Step*);
  virtual void UserSteppingActionInVoxel(const int index, const G4Step* step);
  virtual void UserPreTrackActionInVoxel(const int /*index*/, const G4Track* /*t*/) {}
  virtual void UserPostTrackActionInVoxel(const int /*index*/, const G4Track* /*t*/) {}

  void SetPrimaryMultiplicity(int m) { mPrimaryMultiplicity = m; }
  void SetSecondaryMultiplicity(int m) { mSecondaryMultiplicity = m; }
  int GetPrimaryMultiplicity() { return mPrimaryMultiplicity; }
  int GetSecondaryMultiplicity() { return mSecondaryMultiplicity; }
  
  void RayCast(const G4Step* step);
//   void SetHybridMultiplicityActor(GateHybridMultiplicityActor *a) { pHybridMultiplicityActor = a; }
 /// Saves the data collected to the file
  virtual void SaveData();
  virtual void ResetData();

  ///Scorer related
  //virtual G4bool ProcessHits(G4Step *, G4TouchableHistory*);
  virtual void clear(){ResetData();}
  virtual void Initialize(G4HCofThisEvent*){}
  virtual void EndOfEvent(G4HCofThisEvent*){}
  
protected:
  GateHybridDoseActor(G4String name, G4int depth=0);
  GateHybridDoseActorMessenger *pMessenger;
  
  GateImageWithStatistic mDoseImage;
  GateImageWithStatistic mPrimaryDoseImage;
  GateImageWithStatistic mSecondaryDoseImage;
  GateImageWithStatistic mEdepImage;
  GateImage mLastHitEventImage;

  GateMaterialMuHandler* mMaterialHandler;
  G4String mDoseFilename;
  G4String mPDoseFilename;
  G4String mSDoseFilename;
  G4String mEdepFilename;
  G4double ConversionFactor;
  G4double VoxelVolume;
  
//   GateHybridMultiplicityActor *pHybridMultiplicityActor;
  int mPrimaryMultiplicity;
  int mSecondaryMultiplicity;

  bool mIsEdepImageEnabled;
  bool mIsDoseUncertaintyImageEnabled;
  bool mIsLastHitEventImageEnabled;
  int mCurrentEvent;  
  G4RotationMatrix mRotationMatrix;
  G4AffineTransform worldToVolume;
  G4double outputEnergy;
  G4double totalEnergy;
};

MAKE_AUTO_CREATOR_ACTOR(HybridDoseActor,GateHybridDoseActor)

#endif /* end #define GATEHYBRIDDOSEACTOR_HH */
