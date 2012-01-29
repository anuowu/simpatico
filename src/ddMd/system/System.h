#ifndef SYSTEM_H
#define SYSTEM_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComposite.h>           // base class
#include <ddMd/boundary/Boundary.h>              // member 
#include <ddMd/potentials/PairPotential.h>       // member 
#include <ddMd/storage/AtomStorage.h>            // member 
#include <ddMd/communicate/Domain.h>             // member 
#include <ddMd/communicate/Buffer.h>             // member 
#include <ddMd/communicate/Exchanger.h>          // member 
#include <util/random/Random.h>                  // member 

namespace DdMd
{

   class Interaction;
   class Integrator;
   class ConfigIo;

   using namespace Util;

   /**
   * Main object for a domain-decomposition MD simulation.
   *
   * A DdMd::System contains and coordinates all the components of a parallel
   * MD simulation. 
   */
   class System : public ParamComposite
   {

   public:

      #ifdef UTIL_MPI

      /**
      * Default constructor.
      *
      * \param communicator MPI communicator for MD processors.
      */
      System(MPI::Intracomm& communicator = MPI::COMM_WORLD);

      #else

      /**
      * Default constructor.
      */
      System();

      #endif

      // Mutators

      /**
      * Read parameters, allocate memory and initialize.
      */
      virtual void readParam(std::istream& in);

      /**
      * Read configuration file on master and distribute atoms.
      *
      * \param filename name of configuration file.
      */
      void readConfig(std::string filename);

      /**
      * Set random velocities chosen from Boltzmann distribution.
      *  
      * \param temperature absolute temperature kT, in energy units. 
      */
      void setBoltzmannVelocities(double temperature);

      /**
      * Is exchange of atoms among processors needed?
      *
      * This method returns true if any atom in the AtomStorage has moved
      * a distance skin/2 or greater since the last snapshot (i.e., the
      * last time atoms were exchanged and pair list was rebuilt).
      *
      * Reduce-to-all operation: Must be called on all nodes and returns 
      * same result on all node.
      * 
      * \return true if exchange / reneighboring is needed, false otherwise.
      */
      bool needExchange();

      /**
      * Calculate total kinetic energy.
      * 
      * Reduce operation: Must be called on all nodes but returns correct
      * total value only on grid communicator master.
      *
      * \return total kinetic energy for all nodes on master, 0.0 otherwise.
      */
      double kineticEnergy();

      /**
      * Calculate total nonbonded pair potential energy.
      * 
      * Reduce operation: Must be called on all nodes but returns correct
      * total value only on grid communicator master.
      *
      * \return total pair potential for all nodes on master, 0.0 otherwise.
      */
      double pairPotentialEnergy();

      /**
      * Integrate equations of motion. 
      */
      void integrate(int nStep);

      // Accessors (members by non-const reference)

      /**
      * Get the Domain by reference.
      */
      Domain& domain();

      /**
      * Get the AtomStorage by reference.
      */
      AtomStorage& atomStorage();
   
      /**
      * Get the Boundary by reference.
      */
      Boundary& boundary();
   
      /**
      * Get the PairPotential by reference.
      */
      PairPotential& pairPotential();
   
      /**
      * Get the Interaction by reference.
      */
      Interaction& interaction();
   
      /**
      * Get the Integrator by reference.
      */
      Integrator& integrator();
   
      /**
      * Get the Random number generator by reference.
      */
      Random& random();

      /**
      * Get the Exchanger by reference.
      */
      Exchanger& exchanger();
   
      /**
      * Return total number of atoms on all processors.
      *
      * Reduce operation: Must be called on all nodes but returns
      * correct total value only on grid communicator master.
      */
      int nAtomTotal() const;

      /**
      * Return total number of ghosts on all processors.
      *
      * Reduce operation: Must be called on all nodes but returns
      * correct total value only on grid communicator master.
      */
      int nGhostTotal() const;

      /**
      * Return true if this System is valid, or throw an Exception.
      */
      bool isValid();

   private:

      /// Container for all atoms and ghosts.
      AtomStorage       atomStorage_;

      /// Periodic system boundary.
      Boundary      boundary_;

      /// Periodic system boundary.
      PairPotential pairPotential_;

      /// Processor grid.
      Domain        domain_;

      /// Communication buffer for sending atoms.
      Buffer        buffer_;

      /// Exchanges atoms and ghosts for domain decomposition algorithm.
      Exchanger     exchanger_;

      /// Random number generator.
      Random        random_;

      /// Maximum boundary (used to allocate memory for the cell list).
      Boundary      maxBoundary_;

      #ifdef UTIL_MPI
      MPI::Intracomm* communicatorPtr_;
      #endif

      /// Pointer to force/energy evaluator.
      Interaction*  interactionPtr_;

      /// Pointer to MD integrator.
      Integrator*   integratorPtr_;

      /// Pointer to configuration file reader/writer.
      ConfigIo*     configIoPtr_;

      /// Number of distinct atom types.
      int           nAtomType_;

      /// Is this the master node for file Io?
      bool isMaster_;

   };

   // Inline method definitions

   inline Boundary& System::boundary()
   { return boundary_; }

   inline Domain& System::domain()
   { return domain_; }

   inline AtomStorage& System::atomStorage()
   { return atomStorage_; }

   inline Exchanger& System::exchanger()
   { return exchanger_; }

   inline PairPotential& System::pairPotential()
   { return pairPotential_; }

   inline Interaction& System::interaction()
   { 
      assert(interactionPtr_); 
      return *interactionPtr_; 
   }

   inline Integrator& System::integrator()
   {
      assert(integratorPtr_); 
      return *integratorPtr_; 
   }

   inline Random& System::random()
   { return random_; }

}
#endif
