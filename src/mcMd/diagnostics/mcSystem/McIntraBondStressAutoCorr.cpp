#ifndef MC_INTRA_BOND_STRESS_AUTO_CORR_CPP
#define MC_INTRA_BOND_STRESS_AUTO_CORR_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <mcMd/diagnostics/mcSystem/McIntraBondStressAutoCorr.h>
#include <mcMd/potentials/bond/BondPotential.h>
#include <mcMd/diagnostics/system/IntraBondStressAutoCorr_inc.h>

namespace McMd
{

   using namespace Util;
  
   /*
   * Constructor.
   */
   McIntraBondStressAutoCorr::McIntraBondStressAutoCorr(McSystem &system)
    : IntraBondStressAutoCorr<McSystem>(system)
   {}

   /*
   * Destructor.
   */
   McIntraBondStressAutoCorr::~McIntraBondStressAutoCorr()
   {}

}
#endif

