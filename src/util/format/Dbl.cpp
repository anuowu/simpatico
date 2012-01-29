#ifndef DBL_CPP
#define DBL_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "Dbl.h"
#include "Format.h"

#include <iostream>

namespace Util
{

   // Default constructor.
   Dbl::Dbl()
    : value_(0.0),
      width_(Format::defaultWidth()),
      precision_(Format::defaultPrecision())
   {}

   // Constructor, value only.
   Dbl::Dbl(double value)
    : value_(value),
      width_(Format::defaultWidth()),
      precision_(Format::defaultPrecision())
   {}

   // Constructor, value and width.
   Dbl::Dbl(double value, int width)
    : value_(value),
      width_(width),
      precision_(Format::defaultPrecision())
   {}

   // Constructor: value, width, and precision.
   Dbl::Dbl(double value, int width, int precision)
    : value_(value),
      width_(width),
      precision_(precision)
   {}

   void Dbl::setValue(double value)
   {  value_ = value; }

   void Dbl::setWidth(int width)
   { width_ = width; }

   void Dbl::setPrecision(int precision)
   { precision_ = precision; }

   double Dbl::value()
   { return value_; }

   int Dbl::width()
   { return width_; }

   int Dbl::precision()
   { return precision_; }
     
   /**
   * Input stream extractor for an Dbl object.
   *
   * \param in      input stream
   * \param object  Dbl object to be read from stream
   * \return modified input stream
   */
   std::istream& operator>>(std::istream& in, Dbl &object)
   {
      in >> object.value_;
      return in;
   }

   /**
   * Output stream inserter for an Dbl object.
   *
   * \param  out  output stream
   * \param  object   Dbl to be written to stream
   * \return modified output stream
   */
   std::ostream& operator<<(std::ostream& out, const Dbl &object)
   {
      out.setf(std::ios::scientific);
      out.width(object.width_);
      out.precision(object.precision_);
      out << object.value_;
      return out;
   }

}
#endif
