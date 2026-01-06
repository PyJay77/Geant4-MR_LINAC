#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);
}
PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    // Sampling source position
    G4double sigma = 3.*mm;
    G4double X = G4RandGauss::shoot(0,sigma);
    G4double Y = G4RandGauss::shoot(0,sigma);
    G4double Z = -1200.*mm;
    G4ThreeVector position(X,Y,Z);

    //Sampling the energy
    G4double meanEnergy = 7.*MeV;
    G4double spread = 0.03;
    G4double stdE = meanEnergy * spread;
    G4double energy = G4RandGauss::shoot(meanEnergy,stdE);

    if (energy < 0) {
        energy = 0;
    };

    //Sampling the momentum
    G4double thetaMax = 2.*deg;
    G4double cosTheta = std::cos(thetaMax) + (1 - std::cos(thetaMax)) * G4UniformRand();
    G4double phi = 2 * pi * G4UniformRand();

    G4double momX = std::sqrt(1 - cosTheta * cosTheta) * std::cos(phi);
    G4double momY = std::sqrt(1 - cosTheta * cosTheta) * std::sin(phi);
    G4double momZ = cosTheta;
    G4ThreeVector momentum(momX,momY,momZ);

    fParticleGun->SetParticlePosition(position);
    fParticleGun->SetParticleMomentumDirection(momentum);
    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->GeneratePrimaryVertex(event);

}