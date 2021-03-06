#ifndef MCMD_EWALD_COULOMB_PAIR_CPP
#define MCMD_EWALD_COULOMB_PAIR_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2012, David Morse (morse012@umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "EwaldCoulombPair.h"
#include <util/math/Constants.h>

namespace McMd
{

   /*
   * Set pointer to array of AtomTypes.
   */
   void EwaldCoulombPair::setAtomTypes(const Array<AtomType>& atomTypes)
   {  atomTypesPtr_ = &atomTypes; }

   /*
   * Set internal constants.
   */
   void EwaldCoulombPair::set(double epsilon, double alpha, double rCutoff) 
   {
      double pi = Constants::Pi;
      c_ = 1.0/(epsilon*4.0*pi);
      d_ = 2.0*alpha/sqrt(pi);
      alpha_ = alpha;
      alphaSq_ = alpha*alpha;
      rCutoffSq_ = rCutoff*rCutoff;
   }

}
#endif
