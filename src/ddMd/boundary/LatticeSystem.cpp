#ifndef LATTICE_SYSTEM_CPP
#define LATTICE_SYSTEM_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "LatticeSystem.h"    // class header
#include <util/global.h>      // uses UTIL_THROW

namespace DdMd
{

   using namespace Util;

   /* 
   * Extract a LatticeSystem from an istream as a string.
   */
   std::istream& operator>>(std::istream& in, LatticeSystem& lattice)
   {
      std::string buffer;
      in >> buffer;
      if (buffer == "Cubic" || buffer == "cubic") {
         lattice = Cubic;
      } else 
      if (buffer == "Tetragonal" || buffer == "tetragonal") {
         lattice = Tetragonal;
      } else 
      if (buffer == "Orthorhombic" || buffer == "orthorhombic") {
         lattice = Orthorhombic;
      } else 
      if (buffer == "Monoclinic" || buffer == "monoclinic") {
         lattice = Monoclinic; 
      } else 
      if (buffer == "Triclinic" || buffer == "triclinic") {
         lattice = Triclinic; 
      } else 
      if (buffer == "Rhombohedral" || buffer == "rhombohedral") {
         lattice = Rhombohedral;
      } else 
      if (buffer == "Hexagonal" || buffer == "hexagonal") {
         lattice = Hexagonal; 
      } else {
         UTIL_THROW("Invalid LatticeSystem value input");
      }
      return in;
   }
   
   /* 
   * Insert a LatticeSystem to an ostream as a string.
   */
   std::ostream& operator<<(std::ostream& out, LatticeSystem lattice) 
   {
      if (lattice == Cubic) {
         out << "cubic";
      } else 
      if (lattice == Tetragonal) {
         out << "tetragonal";
      } else
      if (lattice == Orthorhombic) {
         out << "orthorhombic";
      } else
      if (lattice == Monoclinic) {
         out << "monoclinic";
      } else
      if (lattice == Triclinic) {
         out << "triclinic";
      } else
      if (lattice == Rhombohedral) {
         out << "rhombohedral";
      } else
      if (lattice == Hexagonal) {
         out << "hexagonal";
      } else {
         UTIL_THROW("This should never happen");
      } 
      return out; 
   }

}
#endif
