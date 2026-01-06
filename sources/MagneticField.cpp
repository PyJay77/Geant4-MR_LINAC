#include "MagneticField.hh"

MagneticField::MagneticField() {
    fB = G4ThreeVector(1.5*tesla, 0., 0.);
}
MagneticField::~MagneticField() {}

void MagneticField:: GetFieldValue(const double Point[4], double *Bfield) const {
    Bfield[0] = fB.x();
    Bfield[1] = fB.y();
    Bfield[2] = fB.z();
}
