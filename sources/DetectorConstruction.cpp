#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}
G4VPhysicalVolume* DetectorConstruction::Construct() {

    /*
    MATERIAL DEFINITION
        air --> G4_AIR
        tungsten --> G4_W
        stainless steel --> G4_STAINLESS-STEEL
        soft tissue --> G4_TISSUE_SOFT_ICRP
        lung --> G4_LUNG_ICRP 
        bone --> G4_BONE_COMPACT_ICRU
    */ 

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
    G4Material* stainless_steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* soft_tissue = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
    G4Material* lung = nist->FindOrBuildMaterial("G4_LUNG_ICRP");
    G4Material* bone = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");

    G4Box* solidWorld = new G4Box("solidWorld",75.*cm,75.*cm,150.*cm);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,air,"logicWorld");
    G4VPhysicalVolume* physicalWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physicalWorld",0,false,0,true);

    // COLLIMATOR
    G4double xLenghtCollimator = 5.*cm;
    G4double yLenghtCollimator = 5.*cm;
    G4double zLengthW = 1.5*cm;
    G4double zLengthSS = 1.*cm;

    G4Box* solidWColimator = new G4Box("solidBoxW",xLenghtCollimator, yLenghtCollimator,zLengthW);
    G4Box* solidSSColimator = new G4Box("solidBoxSS",xLenghtCollimator, yLenghtCollimator,zLengthSS);

    G4double rW = 1.5*cm;
    G4double rSS = 1.8*cm;

    G4Tubs* tubeW = new G4Tubs("tubeW",0.*cm,rW, zLengthW, 0*deg, 360*deg);
    G4Tubs* tubeSS = new G4Tubs("tubeSS",0*cm,rSS,zLengthSS, 0*deg, 360*deg);

    G4VSolid* solidW = new G4SubtractionSolid("solidW", solidWColimator,tubeW,0,G4ThreeVector(0.,0.,0.));
    G4VSolid* solidSS = new G4SubtractionSolid("solidSS", solidSSColimator,tubeSS,0,G4ThreeVector(0.,0.,0.));

    G4LogicalVolume* logicW = new G4LogicalVolume(solidW,tungsten,"logicW");
    G4LogicalVolume* logicSS = new G4LogicalVolume(solidSS,stainless_steel,"logicSS");

    new G4PVPlacement(0,G4ThreeVector(0.,0.,-70.*cm),logicW,"physicalW",logicWorld,false,0,true);
    new G4PVPlacement(0,G4ThreeVector(0.,0.,-67.5*cm),logicSS,"physicalSS",logicWorld,false,0,true);

    //VOLUME WITH MAGNETIC FIELD
    G4double sideMF = 25*cm;
    G4Box* solidMF = new G4Box("solidMF",sideMF,sideMF,sideMF);
    G4LogicalVolume* logicMF = new G4LogicalVolume(solidMF,air,"logicMF");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,20.*cm),logicMF,"physicalMF",logicWorld,false,0,true);

    logicalVolumeMF = logicMF;

    // PHANTOM
    G4double sidePhantom = 15*cm;
    G4Box* solidPhantom = new G4Box("solidPhantom",sidePhantom,sidePhantom,sidePhantom);
    G4LogicalVolume* logicPhantom = new G4LogicalVolume(solidPhantom,soft_tissue,"logicPhantom");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,0),logicPhantom,"physicalPhantom",logicMF,false,0,true);

    //LUNG
    G4double sideLung = 5*cm;
    G4Box* solidLung = new G4Box("solidLung",sideLung,sideLung,sideLung);
    G4LogicalVolume* logicLung = new G4LogicalVolume(solidLung,lung,"logicLung");
    new G4PVPlacement(0,G4ThreeVector(0.,0.,8*cm),logicLung,"physicalLung",logicPhantom,false,0,true);

    //ARM
    G4double halfLenghtArm = 5.*cm;
    G4double rArm = 2.*cm;

    G4Tubs* solidArm = new G4Tubs("solidArm",0,rArm,halfLenghtArm,0.*deg,360.*deg);
    G4LogicalVolume* logicArm = new G4LogicalVolume(solidArm,bone,"logicArm");
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateY(90.*deg);
    rot->rotateX(90.*deg);
    new G4PVPlacement(rot,G4ThreeVector(+5.*cm,0.,-5*cm),logicArm,"physicalArm",logicPhantom,false,0,true);

    this->ConstructSDandField();
    return physicalWorld;


}

void DetectorConstruction::ConstructSDandField() {
    MagneticField* magneticField = new MagneticField();
    G4FieldManager* localFieldManager = new G4FieldManager();
    localFieldManager->SetDetectorField(magneticField);
    auto equation = new G4Mag_UsualEqRhs(magneticField);
    auto stepper = new G4ClassicalRK4(equation);
    auto chordFinder = new G4ChordFinder(magneticField, 1e-3*mm, stepper);
    localFieldManager->SetChordFinder(chordFinder);
    logicalVolumeMF->SetFieldManager(localFieldManager, true);
}
