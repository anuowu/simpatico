#ifndef MPI_FILE_IO_CPP
#define MPI_FILE_IO_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiFileIo.h"

namespace Util
{

   /*
   * Constructor.
   *
   * Note: Default constructor for _indent string creates an empty string.
   */
   MpiFileIo::MpiFileIo() 
    : isIoProcessor_(true)
      #ifdef UTIL_MPI
      , communicatorPtr_(0)
      #endif
   {}

   /*
   * Copy constructor.
   */
   MpiFileIo::MpiFileIo(const MpiFileIo& other) 
    : isIoProcessor_(other.isIoProcessor_)
      #ifdef UTIL_MPI
      , communicatorPtr_(other.communicatorPtr_)
      #endif
   {}

   #ifdef UTIL_MPI

   void MpiFileIo::setCommunicator(MPI::Intracomm& communicator)
   {

      // Precondition
      if (communicatorPtr_ != 0) {
         UTIL_THROW("Communicator in MpiFileIo may only be set once")
      }

      communicatorPtr_ = &communicator; 
      if (communicator.Get_rank() == 0) {
         isIoProcessor_ = true;
      } else {
         isIoProcessor_ = false;
      }

   }

   void MpiFileIo::clearCommunicator()
   {  
      communicatorPtr_ = 0; 
      isIoProcessor_   = true;
   }

   #endif

} 
#endif
