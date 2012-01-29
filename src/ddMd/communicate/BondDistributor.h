#ifndef BOND_DISTRIBUTOR_H
#define BOND_DISTRIBUTOR_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "GroupDistributor.h"       // base class template

namespace DdMd
{

   /**
   * Class for distributing Bond objects among processors.
   */
   class BondDistributor : public GroupDistributor<2>
   {

   public:

      /**
      * Read cacheCapacity, allocate memory and initialize object.
      *
      * \param in input stream from which parameter is read.
      */
      virtual void readParam(std::istream& in);

   };

}
#endif
