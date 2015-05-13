#include "globals.hh"
#include "G4Gamma.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "G4SystemOfUnits.hh"

int main() {
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);

  G4Material* meat  = man->FindOrBuildMaterial("G4_MUSCLE_SKELETAL_ICRP");

  G4PhotoNuclearCrossSection* photoCrossSection = new G4PhotoNuclearCrossSection();
  G4DynamicParticle gamma(G4Gamma::GammaDefinition(), 10*MeV, G4ThreeVector(10*MeV,0.,0.));
  G4cout << "gamma mass: " << gamma.GetMass() << std::endl;

  std::vector<double> energies;
  for(double e=0.; e<=15.; e+=0.1) energies.push_back(e);
  std::vector<double> xsections;
  xsections.resize(energies.size());

  for (size_t iel=0; iel<meat->GetNumberOfElements(); ++iel)
  {
    const G4Element* element = meat->GetElement(iel);
    G4double abundance = meat->GetFractionVector()[iel];
    for (size_t ie=0; ie<energies.size(); ++ie)
    {
      gamma.SetKineticEnergy(energies[ie]*MeV);
      G4double xs = photoCrossSection->GetElementCrossSection(&gamma, element->GetZ(), meat);
      xsections[ie] += xs*abundance;
    }

    /*
    for (size_t iiso=0; iiso<element->GetNumberOfIsotopes(); ++iiso)
    {
      const G4Isotope* isotope = element->GetIsotope(iiso);
      G4int ZZ = isotope->GetZ();
      G4int AA = ZZ+isotope->GetN();
      G4double xs = photoCrossSection->GetIsoCrossSection(&gamma, ZZ, AA, 0, 0, 0);

      G4cout << ZZ << ", " << AA << " : " << xs << std::endl;
    }
    */
  }

  for (size_t ie=0; ie<energies.size(); ++ie)
  {
    G4cout << energies[ie] << ", " << xsections[ie]/millibarn << std::endl;
  }

  return EXIT_SUCCESS;
}
