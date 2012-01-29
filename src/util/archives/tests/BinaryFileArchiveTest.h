#ifndef BINARY_FILE_ARCHIVE_TEST_H
#define BINARY_FILE_ARCHIVE_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/archives/BinaryFileOArchive.h>
#include <util/archives/BinaryFileIArchive.h>
#include "SerializeTestClass.h"

#include <complex>
#include <fstream>

using namespace Util;

class BinaryFileArchiveTest : public UnitTest 
{

private:

public:

   BinaryFileArchiveTest()
   {}

   void setUp() 
   {}

   void tearDown() {}
   void testOArchiveConstructor();
   void testPack();

};


void BinaryFileArchiveTest::testOArchiveConstructor()
{
   printMethod(TEST_FUNC);
   std::ofstream out;
   openOutputFile("binary", out);
   BinaryFileOArchive  v;
   v.setStream(out);
   out.close();
} 

void BinaryFileArchiveTest::testPack()
{
   printMethod(TEST_FUNC);
   std::ofstream out;
   openOutputFile("binary", out);
   BinaryFileOArchive  v;
   v.setStream(out);

   // Declare variables
   int i1, i2;
   double d1, d2;
   std::complex<double> c1, c2;
   std::string s1, s2;
   Vector a1, a2;
   SerializeTestClass o1, o2;
   double b1[4];
   double b2[4];


   // Initialize variables
   i1 = 3;
   d1 = 45.0;
   c1 = std::complex<double>(3.0, 4.0);
   s1 = "My string has spaces";
   a1[0] =  1.3;
   a1[1] = -2.3;
   a1[2] =  3.3;
   o1.i  =  13;
   o1.d  =  26.0;
   b1[0] = 9.0;
   b1[1] = 8.0;
   b1[2] = 7.0;
   b1[3] = 6.0;
  
   // Write variables to OArchive v
   v << i1;
   v & d1;
   v << c1;
   v << s1;
   v << a1;
   v << o1;
   v.pack(b1, 4);
   out.close();

   std::ifstream in;
   openInputFile("binary", in);
   BinaryFileIArchive u;
   u.setStream(in);

   u >> i2;
   TEST_ASSERT(i1 == i2);

   u & d2;
   TEST_ASSERT(d1 == d2);

   u & c2;
   TEST_ASSERT(c1 == c2);

   u >> s2;
   TEST_ASSERT(s1 == s2);

   u >> a2;
   TEST_ASSERT(a1 == a2);

   u >> o2;
   TEST_ASSERT(o2.i == 13);
   TEST_ASSERT(o2.d == 26.0);

   u.unpack(b2, 4);
   for (int j = 0; j < 4; ++j) {
      TEST_ASSERT(b1[j] == b2[j]);
   }
}

TEST_BEGIN(BinaryFileArchiveTest)
TEST_ADD(BinaryFileArchiveTest, testOArchiveConstructor)
TEST_ADD(BinaryFileArchiveTest, testPack)
TEST_END(BinaryFileArchiveTest)

#endif
