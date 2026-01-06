# Geant4-MR_LINAC
In this project I am simulating an MR LINAC , to see the effect of the magnetic field on the secondary electrons together with the absorbed dose. I am still working on hit. 


# Monte Carlo Simulation of a Clinical Electron Beam in a Magnetic Field (MR-Linac-like Scenario)

## Overview

This repository contains a **Geant4 Monte Carlo simulation** designed to study the transport of a clinical electron beam in the presence of a **confined static magnetic field**, representative of **MR-Linac systems** used in modern radiotherapy.

The simulation focuses on the impact of strong magnetic fields on electron trajectories and dose deposition in a **heterogeneous phantom**, highlighting key physical effects relevant to **medical physics and radiation therapy**.

---

## Scientific Background

The integration of **linear accelerators (Linacs)** with **magnetic resonance imaging (MRI)** systems has introduced new challenges in radiotherapy. Magnetic fields in the range of 1–3 T significantly alter the transport of charged particles, especially secondary electrons, leading to measurable modifications in dose distributions.

Monte Carlo simulations with **Geant4** provide a high-fidelity framework to model:
- Particle–matter interactions
- Complex heterogeneous geometries
- Electromagnetic fields

This makes Geant4 an ideal tool for investigating **MR-Linac-related dosimetric effects**.

---

## Objectives

The main goal of this project is to investigate how a **uniform, confined magnetic field** affects the dose distribution produced by a clinical electron beam in a heterogeneous phantom.

Specific objectives include:
- Studying electron beam deflection due to the **Lorentz force**
- Analyzing the **Electron Return Effect (ERE)** at material interfaces
- Evaluating changes in lateral and depth dose profiles
- Comparing dose distributions **with and without magnetic field**

---

## Simulation Geometry

The simulation uses a **Cartesian coordinate system**, with the **Z-axis aligned with the beam direction**.

### World Volume
- Shape: Box  
- Dimensions: 150 × 150 × 300 cm³  
- Material: Air (G4_AIR)  

The world volume fully contains the experimental setup, avoiding boundary effects.

---

### Collimation System

A simplified multi-layer collimation system is used to define the irradiation field and introduce realistic lateral scattering.

**Tungsten Collimator**
- Shape: Box  
- Dimensions: 10 × 10 × 3 cm³  
- Material: G4_W  
- Central cylindrical aperture:
  - Radius: 1.5 cm
  - Length: 3 cm

**Stainless Steel Collimator**
- Shape: Box  
- Dimensions: 10 × 10 × 2 cm³  
- Material: G4_STAINLESS-STEEL  
- Central cylindrical aperture:
  - Radius: 1.8 cm
  - Length: 2 cm

**Collimator position:** Z = −70 cm

---

### Magnetic Field Region

A dedicated region mimics the imaging volume of an MR-Linac system.

- Shape: Box  
- Dimensions: 50 × 50 × 50 cm³  
- Material: Air  
- Center: Z = +20 cm  

A **uniform static magnetic field** is applied only inside this region.

---

### Heterogeneous Phantom

The phantom is entirely contained within the magnetic field region.

**Main Phantom (Soft Tissue)**
- Shape: Box  
- Dimensions: 30 × 30 × 30 cm³  
- Material: G4_TISSUE_SOFT_ICRP  

**Lung Insert**
- Shape: Box  
- Dimensions: 10 × 10 × 10 cm³  
- Material: G4_LUNG_ICRP  
- Position: (0, 0, +10 cm)

**Bone Insert**
- Shape: Cylinder  
- Radius: 2 cm  
- Height: 10 cm  
- Material: G4_BONE_COMPACT_ICRU  
- Position: (+5 cm, 0, −5 cm)

---

## Magnetic Field Configuration

- Type: Uniform magnetic field  
- Intensity: **1.5 T**  
- Direction: X-axis  
- Applied only inside the magnetic field region  

The field induces electron trajectory curvature in the **Y–Z plane**, leading to lateral dose shifts.

---

## Primary Beam Characteristics

- Particle: Electrons (e⁻)
- Mean energy: **7 MeV**
- Energy spread: Gaussian, σ = 3%
- Spatial distribution: Gaussian, σ = 3 mm
- Angular divergence: Cone with 2° maximum opening
- Mean direction: +Z
- Source position: Z = −120 cm

---

## Physics Models and Simulation Parameters

- Physics list: `FTFP_BERT + G4EmStandardPhysics_option4`
- Production cuts:
  - 0.1 mm in the phantom
  - 1 mm in the rest of the geometry
- Magnetic field stepper: High-order **Dormand–Prince** integrator

---

## Scoring and Observables

The following quantities can be calculated using this simulation setup:
- 3D absorbed dose in the phantom (1 × 1 × 1 mm³ voxels)
- Percentage Depth Dose (PDD)
- Lateral dose profiles at multiple depths
- Dose behavior at air–tissue and tissue–bone interfaces

---

## Relevance and Applications

This simulation provides a controlled framework to study key dosimetric effects introduced by magnetic fields in radiotherapy. It is well-suited for:
- MR-Linac dosimetry studies
- Validation against published literature
- Extension toward more realistic clinical geometries

---

## Technologies Used

- **Geant4**
- **C++**
- Monte Carlo particle transport
- Medical physics–oriented geometry and scoring

---


Additional projects (including Physics-Informed Neural Networks developed in PyTorch) are available on my **GitHub profile**.
