#ifdef  MCMD_TETHER
#ifndef MC_TETHER_POTENTIAL_H
#define MC_TETHER_POTENTIAL_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <mcMd/potentials/tether/TetherPotential.h>  // base class

namespace McMd
{

   using namespace Util;

   class System;

   /**
   * A TetherPotential for MC simulations.
   *
   * \ingroup Tether_Module
   */
   class McTetherPotential : public TetherPotential 
   {

   #if 0
   public:

      /**   
      * Constructor.
      */
      McTetherPotential();

      /** 
      * Destructor.
      */
      virtual ~McTetherPotential();

      /**
      * Calculate the tether energy for a specified Atom.
      *
      * \param  atom Atom object of interest
      * \return tether potential energy of atom
      */
      virtual double atomEnergy(const Atom& atom) const = 0;
   #endif

   };

} 
#endif
#endif
