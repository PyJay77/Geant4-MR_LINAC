#include "PhysicsList.hh"

PhysicsList::PhysicsList() {
    SetVerboseLevel(1);
    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
}
PhysicsList::~PhysicsList() {}
