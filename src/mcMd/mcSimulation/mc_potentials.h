#ifndef MC_POTENTIALS_H
#define MC_POTENTIALS_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

/**
* \file mc_potentials.h
*
* \brief Include this file to include all MC potential energy classes at once.
*/

#ifndef MCMD_NOPAIR
#include <mcMd/potentials/pair/McPairPotential.h>
#endif
#include <mcMd/potentials/bond/BondPotential.h>
#ifdef MCMD_ANGLE
#include <mcMd/potentials/angle/AnglePotential.h>
#endif
#ifdef MCMD_DIHEDRAL
#include <mcMd/potentials/dihedral/DihedralPotential.h>
#endif
#ifdef MCMD_EXTERNAL
#include <mcMd/potentials/external/ExternalPotential.h>
#endif
#ifdef MCMD_TETHER
#include <mcMd/potentials/tether/TetherPotential.h>
#endif

#endif
