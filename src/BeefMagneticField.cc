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
// $Id: BeefMagneticField.cc 77656 2013-11-27 08:52:57Z gcosmo $
//
/// \file BeefMagneticField.cc
/// \brief Implementation of the BeefMagneticField class

#include "BeefMagneticField.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BeefMagneticField::BeefMagneticField()
: G4MagneticField(), fMessenger(0), fBz(1.0*tesla)
{
    // define commands for this class
    DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BeefMagneticField::~BeefMagneticField()
{ 
    delete fMessenger; 
}

void BeefMagneticField::GetFieldValue(const G4double [4],double *bField) const
{

    const G4Run* run  = G4RunManager::GetRunManager()->GetCurrentRun();
    G4int numEvents = run->GetNumberOfEventToBeProcessed();

    G4int eID = 0;
    const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
    if(evt) eID = evt->GetEventID();
   
    G4float fieldIncrement = 2*fBz/numEvents;
    bField[0] = 0.;
    bField[1] = 0;
    bField[2] = fBz - fieldIncrement*eID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BeefMagneticField::DefineCommands()
{
    // Define /Beef/field command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this, 
                                        "/Beef/field/", 
                                        "Field control");

    // fieldValue command 
    G4GenericMessenger::Command& valueCmd
      = fMessenger->DeclareMethodWithUnit("value","tesla",
                                  &BeefMagneticField::SetField, 
                                  "Set field strength.");
    valueCmd.SetParameterName("field", true);
    valueCmd.SetDefaultValue("1.");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
