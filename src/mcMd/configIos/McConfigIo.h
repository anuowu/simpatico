#ifndef MC_CONFIG_IO_H
#define MC_CONFIG_IO_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <mcMd/configIos/McMdConfigIo.h>
#include <util/global.h>

#include <iostream>

namespace McMd
{

   using namespace Util;

   class System;
   class Atom;
   
   /**
   * ConfigIo for MC simulations (no atom velocities).
   *
   * \ingroup ConfigIo_Module
   */
   class McConfigIo : public McMdConfigIo
   {
   
   public:

      /// Constructor. 
      McConfigIo(System& system);
 
      /// Destructor.   
      virtual ~McConfigIo();
 
   protected:

      /// Read data for one atom.
      virtual void readAtom(std::istream& out, Atom& atom);
     
      /// Write data for one atom.
      virtual void writeAtom(std::ostream& out, const Atom& atom);
     
   }; 

} 
#endif