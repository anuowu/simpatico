#ifndef CONST_GHOST_ITERATOR_H
#define CONST_GHOST_ITERATOR_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ConstPArrayIterator.h>

namespace DdMd
{

   using namespace Util;
   class Atom;

   /**
   * Iterator for all ghost atoms in a System.
   */
   class ConstGhostIterator : public ConstPArrayIterator<Atom>
   {};

}
#endif
