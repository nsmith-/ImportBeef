//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm11/src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
// $Id: SteppingAction.cc 74997 2013-10-25 10:52:13Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "Run.hh"
#include "HistoManager.hh"

#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* event)
:G4UserSteppingAction(),fDetector(det), fEventAction(event)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
 G4double edep = step->GetTotalEnergyDeposit();
 const G4Track* track = step->GetTrack();
 if (edep <= 0.) return;
 
 //total energy deposit in absorber
 //
 fEventAction->AddEdep(edep); 
 
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();     
 
 //longitudinal profile of deposited energy
 //randomize point of energy deposotion
 //
 G4StepPoint* prePoint  = step->GetPreStepPoint();
 G4StepPoint* postPoint = step->GetPostStepPoint(); 
 G4ThreeVector P1 = prePoint ->GetPosition();
 G4ThreeVector P2 = postPoint->GetPosition();
 G4ThreeVector point = P1 + G4UniformRand()*(P2 - P1);

 G4int iabs = prePoint->GetTouchableHandle()->GetCopyNumber(1);
 // Record only last absorber information
 if ( iabs == fDetector->GetNbOfAbsor() ) { 
   G4double xshifted = point.x() - fDetector->GetXfront(iabs);  
   G4double r = sqrt(pow(point.y(),2)+pow(point.z(),2));
   analysisManager->FillH1(1, xshifted, edep);
   analysisManager->FillH1(9, r, edep);
   analysisManager->FillH1(10, point.y(), edep);

   analysisManager->FillH2(0, xshifted, point.y(), edep);
 } else if ( iabs == fDetector->GetNbOfAbsor()-1 ) {
   G4int inextabs = postPoint->GetTouchableHandle()->GetCopyNumber(1);
   if ( inextabs > iabs ) {
     analysisManager->FillH1(11, track->GetTotalEnergy());
   }
 }

   
 //step size of primary particle or charged secondaries
 //
 G4double steplen = step->GetStepLength();
 if      (track->GetTrackID() == 1) analysisManager->FillH1(4, track->GetTrackLength(), edep);
 else if (track->GetDefinition()->GetPDGCharge() != 0.)
                                    analysisManager->FillH1(7, steplen); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


