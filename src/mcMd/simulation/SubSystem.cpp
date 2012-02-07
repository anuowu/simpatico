#ifndef SUB_SYSTEM_CPP
#define SUB_SYSTEM_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

// namespace McMd
#include "SubSystem.h"
#include "Simulation.h"
#include <mcMd/species/Species.h>

#include <fstream>

namespace McMd
{

   using namespace Util;

   /*
   * Constructor.
   */
   SubSystem::SubSystem(System& parent)
    : simulationPtr_(parent.simulationPtr_),
      systemPtr_(&parent),
      moleculeSetsPtr_(parent.moleculeSetsPtr_),
      boundaryPtr_(parent.boundaryPtr_),
      hasBonds_(parent.simulation().nBondType() > 0)
      #ifdef MCMD_ANGLE
      , hasAngles_(parent.simulation().nAngleType() > 0)
      #endif
      #ifdef MCMD_DIHEDRAL
      , hasDihedrals_(parent.simulation().nDihedralType() > 0)
      #endif
      #ifdef MCMD_LINK
      , hasLinks_(parent.simulation().nLinkType() > 0)
      #endif
      #ifdef MCMD_EXTERNAL
      , hasExternal_(parent.simulation().hasExternal())
      #endif
      #ifdef MCMD_TETHER
      , hasTethers_(parent.simulation().hasTether())
      #endif
   {}

   /*
   * Destructor.
   */
   SubSystem::~SubSystem()
   {}

   /*
   * Is this System empty (i.e., devoid of Molecules) ?
   */
   bool SubSystem::isEmpty() const
   {
      for (int i = 0; i < simulation().nSpecies(); ++i) {
         if (nMolecule(i) != 0) return false;
      }
      return true;
   }

   /*
   * Return the total number of atoms in this System.
   */
   int SubSystem::nAtom() const
   {
      int sum = 0;
      for (int i = 0; i < simulation().nSpecies(); ++i) {
         sum += nMolecule(i)*simulation().species(i).nAtom();
      }
      return sum;
   }

}
#endif