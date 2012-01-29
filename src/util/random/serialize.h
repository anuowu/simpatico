#ifndef RANDOM_SERIALIZE_H
#define RANDOM_SERIALIZE_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/random/mersenne/mtrand.h>
#include <util/random/Random.h>

namespace Util 
{

   /*
   * Serialize to/from an archive.
   */
   template <class Archive>
   void MTRand_int32::serialize(Archive& ar, const unsigned int version)
   {
      for (int i=0; i < n; ++i) {
         ar & state[i];
      }
      ar & p;
      ar & init;
   }

   /*
   * Serialize to/from an archive.
   */
   template <class Archive>
   void Random::serialize(Archive& ar, const unsigned int version)
   {
      ar & engine_;
      ar & seed_;
   }

}
#endif 
