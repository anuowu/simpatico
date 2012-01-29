#ifndef F_ARRAY_PARAM_H
#define F_ARRAY_PARAM_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/


#include <util/param/Parameter.h>
#include <util/containers/FArray.h>
#include <util/global.h>

#include <iomanip> 

class ParamTest;

namespace Util
{

   /**
   * A Parameter associated with a FArray container.
   *
   * \ingroup Param_Module
   */
   template <class Type, int N>
   class FArrayParam : public Parameter
   {
   
   public:
   
      /// Constructor.
      FArrayParam(const char *label, FArray<Type, N>& array);
 
      /** 
      * Read FArray parameter from stream.
      *
      * \param in input stream
      */
      void readParam(std::istream &in);
 
      /** 
      * Write FArray parameter to stream.
      *
      * \param out output stream
      */
      void writeParam(std::ostream &out);

   protected:
   
      /// Pointer to associated FArray.
      FArray<Type, N>* arrayPtr_;
   
   };

   /*
   * FArrayParam<Type, N> constructor.
   */
   template <class Type, int N>
   FArrayParam<Type, N>::FArrayParam(const char *label, FArray<Type, N>& array)
    : Parameter(label),
      arrayPtr_(&array)
   {}

   /*
   * Read a FArray parameter.
   */
   template <class Type, int N>
   void FArrayParam<Type, N>::readParam(std::istream &in)
   {

      if (isParamIoProcessor()) {
         in >> label_;
         for (int i = 0; i < N; ++i) {
            in >> (*arrayPtr_)[i];
         }
         if (ParamComponent::echo()) {
            writeParam(Log::file());
         }
      }
      #ifdef UTIL_MPI
         if (hasParamCommunicator()) 
            bcast<Type>(paramCommunicator(), &((*arrayPtr_)[0]), N, 0); 
      #endif

   }

   /*
   * Write a FArray parameter.
   */
   template <class Type, int N>
   void FArrayParam<Type, N>::writeParam(std::ostream &out) 
   {
      Label space("");
      for (int i = 0; i < N; ++i) {
         if (i == 0) {
            out << indent() << label_;
         } else {
            out << indent() << space;
         }
         out << std::right << std::scientific 
             << std::setprecision(Parameter::Precision) 
             << std::setw(Parameter::Width)
             << (*arrayPtr_)[i] 
             << std::endl;
      }
   }

} 
#endif
