#pragma once
#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class MagneticField : public G4MagneticField {
public : 
    MagneticField();
    ~MagneticField() override;
    void GetFieldValue(const double Point[4], double *Bfield) const override;
private:
    G4ThreeVector fB;
};