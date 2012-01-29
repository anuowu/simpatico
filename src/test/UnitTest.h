#ifndef UNIT_TEST_H
#define UNIT_TEST_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "TestException.h"

#include <fstream>
#include <string>
#ifdef TEST_MPI
#include <mpi.h>
#endif

/**
* UnitTest is a base class for unit test classes.
*
* A unit test class for a particular class should be derived 
* from UnitTest, and should define several test methods. The  
* names of the tests are arbitrary. The tests should use the
* TEST_ASSERT(expression) macro to assert the truth of logical
* expressions.
*
* The tests defined in a unit test named TestA must be added 
* to an associated TestRunner class that is created using the
* UnitTestRunner template. The run() method of such a
* TestRunner class calls all of the associated test methods 
* in the order in which they were added, and counts the number
* of successful and failed tests.
*
* Preprocessor macros that are defined in UnitTestRunner.h 
* file can be used to create the boiler-plate code necessary 
* to define a unit test runner and to add test methods to 
* it. See the class documentation for UnitTestRunner for 
* more details. 
*/
class UnitTest
{

public:

   /**
   * Constructor
   */
   UnitTest() :
      #ifdef TEST_MPI      
      communicatorPtr_(0),
      mpiRank_(-1),
      #endif
      verbose_(0),
      isIoProcessor_(true)
   {
      #ifdef TEST_MPI
      // Set the communicator to COMM_WORLD by default.
      setCommunicator(MPI::COMM_WORLD);
      #endif
   }

   /**
   * Destructor.
   */
   virtual ~UnitTest() 
   {}

   /**
   * Set up before each test method (empty default implementation).
   */
   virtual void setUp()
   {}

   /**
   * Tear down after each test method (empty default implementation).
   */
   virtual void tearDown()
   {}

   /**
   * Set verbosity level.
   *
   * \param verbose verbosity level (0 = silent).
   */
   void setVerbose(int verbose)
   {  verbose_ = verbose; }

   /**
   * Set file prefix.
   */
   void setFilePrefix(const std::string& prefix)
   {  filePrefix_  = prefix; }

   /**
   * Get file prefix string
   */
   const std::string& filePrefix()
   {  return filePrefix_; }

   /**
   * Should this processor read and write to file?
   */
   bool isIoProcessor() const
   {  return isIoProcessor_; } 

   #ifdef TEST_MPI
   void setCommunicator(MPI::Intracomm& communicator)
   {  
      communicatorPtr_ = &communicator; 
      mpiRank_ = communicator.Get_rank();
      if (mpiRank_ == 0) {
         isIoProcessor_ = true; 
      } else {
         isIoProcessor_ = false; 
      }
   }

   /**
   * Return rank of this processor in MPI::COMM_WORLD
   */
   int mpiRank()
   {  return mpiRank_; } 

   bool hasCommunicator()
   { return bool(communicatorPtr_ != 0); }

   MPI::Intracomm& communicator()
   { return *communicatorPtr_; }
   #endif

protected:

   /**
   * Print name of a class method .
   */
   void printMethod(const char* methodName)
   {  if (isIoProcessor()) {
         std::cout << std::endl;
         std::cout << std::string(methodName); 
      }
   }

   void printEndl()
   {  if (isIoProcessor()) std::cout << std::endl; } 

   virtual void endMarker()
   {
      if (isIoProcessor()) {
         std::cout << std::endl;
         std::cout << "----------------------------------------------------";
         std::cout << std::endl << std::endl;
      }
   }

   /**
   * Open input file.
   *
   * \param name base file name (added to filePrefix).
   * \param in input file (opened on return).
   */
   void openInputFile(const std::string& name, std::ifstream& in) const
   {   
      std::string filename = filePrefix_;
      filename += name;
      in.open(filename.c_str());
   }

   /**
   * Open output file stream.
   *
   * \param name base file name (added to filePrefix).
   * \param out  output file (opened on return).
   */
   void openOutputFile(const std::string& name, std::ofstream& out) const
   {   
      std::string filename = filePrefix_;
      filename += name;
      out.open(filename.c_str());
   }

   int verbose() const
   {  return verbose_; }
 
   /**
   * Return true if two integers are equal.
   */
   bool eq(int s1, int s2) const
   {  return (s1 == s2); }

   /**
   * Return true if two double precision floats are equal.
   */
   bool eq(double s1, double s2) const
   {
      double epsilon = 1.0E-10; 
      return ( fabs(s1-s2) < epsilon ); 
   }

private:

   /**
   * Prefix added to file names
   */
   std::string  filePrefix_;

   #ifdef TEST_MPI
   MPI::Intracomm* communicatorPtr_;

   int  mpiRank_;
   #endif

   int  verbose_;

   bool isIoProcessor_;

};

#endif
