#ifndef MCMD_ATOM_H
#define MCMD_ATOM_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2014, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Mask.h"
#include <util/space/Vector.h>
#ifdef MCMD_SHIFT
#include <util/space/IntVector.h>
#endif
#include <util/global.h>

namespace Util {
   template <class Data> class RArray;
}

namespace McMd
{

   using namespace Util;

   class Molecule;

   /**
   * A point particle within a Molecule.
   *
   * Each Atom has a position Vector, an integer atom type Id, and a global 
   * integer id that is unique in the Simulation. Each Atom has a force and
   * velocity, for use in Md simulations. Each atom has a pointer to its
   * parent Molecule, and has an associated Mask object. A Mask contains a
   * list of other atoms for which pair interactions with this Atom are
   * suppressed. 
   *
   * Each atom also has an isActive() flag that can be used by Monte Carlo
   * moves to mark an atom as temporarily "inactive" during a deletion or 
   * regrowth of part of a molecule. The isActive flag is initialized to
   * true by the Atom::allocate function.
   *
   * \section Allocate Allocation and Deallocation
   *
   * Atom objects can only be created by the static Atom::allocate()
   * function. This function allocates a static member array containing all
   * of the Atom objects available in a program. The global index that is 
   * returned by the id() function is the index of an Atom within this array. 
   * This array of all Atoms must be allocated and deallocated using the
   * following pattern:
   * \code
   * RArray<Atom> atoms;          
   * int          atomCapacity;   // number of Atoms to be allocated
   *
   * Atom::allocate(atomCapacity, atoms)
   *
   * // ... code that uses elements of the RArray atoms ...
   *
   * Atom::deallocate();
   * \endcode
   * Access to the array of Atom objects is provided by an RArray<Atom> 
   * array container (called "atoms" in the above example) that is
   * passed to Atom::allocate by reference as its second parameter. After 
   * Atom::allocate() returns, this container holds the address and 
   * capacity of the underlying C array, and may thereafter be used to
   * access individual atoms. 
   *
   * This interface is designed to allow an implementation of the Atom 
   * class in which some logical attributes of an Atom are not actually 
   * C++ member variables, but are instead stored in separate private 
   * arrays. These additional arrays are private static members of the 
   * Atom class that can be directly accessed by the accessor and setter 
   * functions for the associated attributes, as if they were normal 
   * non-static class members. 
   *
   * \ingroup McMd_Chemistry_Module
   */
   class Atom
   {

   public:

      // Non-static Methods

      // Private default and copy constructors.

      // Default destructor.
      
      /// \name Mutators
      //@{

      /**
      * Set the parent molecule.
      *  
      * \param molecule Molecule containing this Atom
      */
      void setMolecule(Molecule& molecule);

      /**
      * Set the atomic type index.
      *  
      * \param typeId integer index that identifies atom type
      */
      void setTypeId(int typeId);

      /**
      * Set the atom as active (true) or inactive (false).
      *  
      * \param isActive set true for active, false for inactive.
      */
      void setIsActive(bool isActive);

      //@}
      /// \name Accessors
      //@{

      /// Get global index for this Atom within the Simulation.
      int   id() const;

      /// Get local index for this Atom within the parent molecule;
      int   indexInMolecule() const;

      /// Get type index for this Atom.
      int   typeId() const;

      /// Get the parent Molecule by reference.
      Molecule& molecule() const;

      /// Get the position Vector by const reference.
      const Vector& position() const;

      /// Get position Vector by reference.
      Vector& position();

      /// Get the associated Mask by reference.
      Mask& mask();

      /// Get the associated Mask by const reference.
      const Mask& mask() const;

      /// Get atomic velocity Vector by reference.
      Vector& velocity();

      /// Get the atomic velocity Vector by const reference.
      const Vector& velocity() const;

      /// Get atomic force Vector by reference.
      Vector& force();

      /// Get atomic force Vector by const reference.
      const Vector& force() const;

      /// Get the isActive flag.
      bool isActive() const;

      #ifdef MCMD_SHIFT
      /// Get the shift IntVector by reference.
      IntVector& shift();

      /// Get the shift IntVector by const reference.
      const IntVector& shift() const;
      #endif

      //@}
      ///\name Allocation and de-allocation (static members)
      //@{

      /**
      * Method to guarantee initialization of static data.
      */
      static void initStatic();
     
      /** 
      * Allocate a static array of Atom objects.
      *
      * Upon return, the parameter atoms is associated with a new private
      * static array of Atom objects, and every Atom has an id set equal
      * to its index within this array.
      *
      * Atom::allocate creates a static array that contains all of the Atom 
      * objects available for use in a program. Atom::deallocate() releases 
      * the memory allocated by Atom::allocate. Atom::allocate() cannot be
      * called more than once without first calling Atom::deallocate().
      *
      * \param capacity total number of Atoms to be allocated in the array.
      * \param atoms    on return, atoms is associated with the new array.
      */
      static void allocate(int capacity, RArray<Atom>& atoms);

      /**
      * Delete all static arrays.
      *
      * Deletes all memory allocated previously by allocate.
      */
      static void deallocate();

      /**
      * Get total number of atoms (capacity of the static atom array.)
      */
      static int capacity();

      //@}

   private:

      // Static members
      
      /// Null (unknown) value for any non-negative integer index.
      static const int NullIndex = -1;

      /// Array containing all Atom objects in this simulation.
      static Atom* atoms_;

      /// Array of Mask objects
      static Mask* masks_;

      /// Array of pointers to Molecules
      static Molecule** moleculePtrs_;

      /// Array of atomic force vectors
      static Vector* forces_;

      /// Array of atomic velocity vectors
      static Vector* velocities_;

      /// Array of bool "isActive" flags
      static bool* isActives_;

      #ifdef MCMD_SHIFT
      /// Array of boundary condition shifts
      static IntVector* shifts_;
      #endif

      /// Total number of atoms allocated
      static int capacity_;

      // Non-static member variables
 
      /// Position of atom.
      Vector position_;                           

      /// Integer index of atom type.             
      int typeId_;                         

      /// Integer index for Atom within Simulation.
      int id_;                                   

      // Private non-static member functions

      /// Constructor. Private to prevent public instantiation.
      Atom();

      /// Copy constructor. Private to prevent copying, not implemented.
      Atom(const Atom& other);

   }; 

   // Inline member functions

   // Set type index for Atom.
   inline void Atom:: setTypeId(int typeId) 
   {  typeId_ = typeId; }

   // Set the atom as active (true) or inactive (false).
   inline void Atom::setIsActive(bool isActive)
   {  isActives_[id_] = isActive; }

   // Get global id for Atom.
   inline int  Atom::id() const
   {  return id_; }

   // Get type Id.
   inline int Atom::typeId() const
   {  return typeId_; }

   // Get const reference to position.
   inline const Vector& Atom::position() const
   {  return position_; }

   // Get reference to position.
   inline Vector& Atom::position()
   {  return position_; }

   // Get const reference to velocity.
   inline const Vector& Atom::velocity() const
   {  return velocities_[id_]; }

   // Get reference to velocity.
   inline Vector& Atom::velocity()
   {  return velocities_[id_]; }

   // Get const reference to force.
   inline const Vector& Atom::force() const
   {  return forces_[id_]; }

   // Get reference to force.
   inline Vector& Atom::force()
   {  return forces_[id_]; }

   // Get the associated mask.
   inline Mask& Atom::mask()
   {  return masks_[id_]; }

   // Get a const reference to the mask.
   inline const Mask& Atom::mask() const
   {  return masks_[id_]; }

   // Get a reference to the parent Molecule.
   inline Molecule& Atom::molecule() const
   {  return *moleculePtrs_[id_]; }

   // Get the isActive flag (true == active).
   inline bool Atom::isActive() const
   {  return isActives_[id_]; }

   #ifdef MCMD_SHIFT
   // Get the shift IntVector by reference.
   inline IntVector& Atom::shift()
   {  return shifts_[id_]; }

   // Get the shift IntVector by const reference.
   inline const IntVector& Atom::shift() const
   {  return shifts_[id_]; }
   #endif

}
#endif
