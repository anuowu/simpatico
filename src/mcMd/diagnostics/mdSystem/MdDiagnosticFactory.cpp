#ifndef MD_DIAGNOSTIC_FACTORY
#define MD_DIAGNOSTIC_FACTORY

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "MdDiagnosticFactory.h" // Class header

#include <mcMd/mdSimulation/MdSimulation.h>

// Diagnostics for MdSystem only
#include "MdEnergyOutput.h"
#include "MdPotentialEnergyAverage.h"
#include "MdKineticEnergyAverage.h"
#include "MdPressureAverage.h"
#include "MdIntraBondStressAutoCorr.h"
#include "MdIntraBondTensorAutoCorr.h"
#include "MdPairEnergyCoefficients.h"
#include "MdWriteRestart.h"

namespace McMd
{

   using namespace Util;

   /*
   * Constructor.
   */
   MdDiagnosticFactory::MdDiagnosticFactory(MdSimulation& simulation, 
                                            MdSystem& system)
    : systemFactory_(simulation, system),
      simulationPtr_(&simulation),
      systemPtr_(&system)
   {}

   /* 
   * Return a pointer to an instance of Diagnostic subclass className.
   */
   Diagnostic* MdDiagnosticFactory::factory(const std::string &className) const
   {
      Diagnostic* ptr = 0;

      // Try subfactories first (if any)
      ptr = trySubfactories(className);
      if (ptr) return ptr;

      // MdSystem Diagnostics
      if (className == "MdEnergyOutput") {
         ptr = new MdEnergyOutput(system());
      } else
      if (className == "MdPotentialEnergyAverage") {
         ptr = new MdPotentialEnergyAverage(system());
      } else
      if (className == "MdKineticEnergyAverage") {
         ptr = new MdKineticEnergyAverage(system());
      } else
      if (className == "MdPressureAverage") {
         ptr = new MdPressureAverage(system());
      } else 
      if (className == "MdIntraBondStressAutoCorr") {
         ptr = new MdIntraBondStressAutoCorr(system());
      } else 
      if (className == "MdIntraBondTensorAutoCorr") {
         ptr = new MdIntraBondTensorAutoCorr(system());
      } else 
      if (className == "MdWriteRestart") {
         ptr = new MdWriteRestart(simulation());
      } 
      #ifndef MCMD_NOPAIR
      else
      if (className == "MdPairEnergyCoefficients") {
         ptr = new MdPairEnergyCoefficients(system());
      }
      #endif

      // If none of the above, try the SystemDiagnosticFactory
      if (!ptr) {
         ptr = systemFactory_.factory(className);
      } 

      return ptr;
   }

}

#endif
