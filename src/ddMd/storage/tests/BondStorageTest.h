#ifndef BOND_STORAGE_TEST_H
#define BOND_STORAGE_TEST_H

#ifdef UTIL_MPI
#define TEST_MPI
#endif

#include <ddMd/storage/BondStorage.h>
#include <ddMd/storage/BondIterator.h>
#include <ddMd/storage/AtomStorage.h>
#include <ddMd/chemistry/Bond.h>
#include <util/containers/DPArray.h>

#include <test/ParamFileTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;
using namespace DdMd;

class BondStorageTest : public ParamFileTest<BondStorage>
{

public:

   virtual void setUp()
   { 
      #ifdef UTIL_MPI 
      object().setParamCommunicator(communicator());
      #endif

      openFile("in/BondStorage"); 
      object().readParam(file()); 
   }

   void testReadParam();

   void testAdd();

   void testAddRemove();

   void testIterator();

   void testFindBonds();

};

inline void BondStorageTest::testReadParam()
{  
   printMethod(TEST_FUNC); 
   if (verbose() > 0) {
      object().writeParam(std::cout);
   }
}

inline void BondStorageTest::testAdd()
{
   printMethod(TEST_FUNC);

   Bond* ptr53 = object().add(53);
   TEST_ASSERT(object().find(53) == ptr53);
   TEST_ASSERT(ptr53->id() == 53);
   TEST_ASSERT(object().size() == 1);
   TEST_ASSERT(object().isValid());

   Bond* ptr35 = object().add(35);
   TEST_ASSERT(object().find(53) == ptr53);
   TEST_ASSERT(ptr53->id() == 53);
   TEST_ASSERT(object().find(35) == ptr35);
   TEST_ASSERT(ptr35->id() == 35);
   TEST_ASSERT(object().size() == 2);
   TEST_ASSERT(object().isValid());

   Bond* ptr18 = object().add(18);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(ptr18->id() == 18);
   TEST_ASSERT(object().size() == 3);
   TEST_ASSERT(object().isValid());
}

void BondStorageTest::testAddRemove()
{
   printMethod(TEST_FUNC);

   // Add three bonds
   Bond* ptr53 = object().add(53);
   Bond* ptr35 = object().add(35);
   Bond* ptr18 = object().add(18);

   TEST_ASSERT(object().find(53) == ptr53);
   TEST_ASSERT(ptr53->id() == 53);
   TEST_ASSERT(object().find(35) == ptr35);
   TEST_ASSERT(ptr35->id() == 35);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(ptr18->id() == 18);
   TEST_ASSERT(object().size() == 3);
   TEST_ASSERT(object().isValid());

   object().remove(ptr53);
   TEST_ASSERT(object().find(53) == 0);
   TEST_ASSERT(ptr53->id() < 0);
   TEST_ASSERT(object().find(35) == ptr35);
   TEST_ASSERT(ptr35->id() == 35);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(ptr18->id() == 18);
   TEST_ASSERT(object().size() == 2);
   TEST_ASSERT(object().isValid());

   Bond* ptr67 = object().add(67);
   Bond* ptr82 = object().add(82);
   Bond* ptr44 = object().add(44);
   TEST_ASSERT(object().find(53) == 0);
   TEST_ASSERT(object().find(35) == ptr35);
   TEST_ASSERT(ptr35->id() == 35);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(ptr18->id() == 18);
   TEST_ASSERT(object().find(67) == ptr67);
   TEST_ASSERT(ptr67->id() == 67);
   TEST_ASSERT(object().find(82) == ptr82);
   TEST_ASSERT(ptr82->id() == 82);
   TEST_ASSERT(object().find(44) == ptr44);
   TEST_ASSERT(ptr44->id() == 44);
   TEST_ASSERT(object().size() == 5);
   TEST_ASSERT(object().isValid());

   object().remove(ptr35);
   TEST_ASSERT(object().find(53) == 0);
   TEST_ASSERT(object().find(35) == 0);
   TEST_ASSERT(ptr35->id() < 0);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(ptr18->id() == 18);
   TEST_ASSERT(object().find(67) == ptr67);
   TEST_ASSERT(ptr67->id() == 67);
   TEST_ASSERT(object().find(82) == ptr82);
   TEST_ASSERT(ptr82->id() == 82);
   TEST_ASSERT(object().find(44) == ptr44);
   TEST_ASSERT(ptr44->id() == 44);
   TEST_ASSERT(object().size() == 4);
   TEST_ASSERT(object().isValid());

}
 
void BondStorageTest::testIterator()
{
   printMethod(TEST_FUNC);

   DPArray<Bond> bonds;

   bonds.allocate(object().capacity());

   // Add bonds
   bonds.append(*object().add(53));
   bonds.append(*object().add(35));
   bonds.append(*object().add(18));
   bonds.append(*object().add(44));
   bonds.append(*object().add(17));
   bonds.append(*object().add(82));
   bonds.append(*object().add(39));
   TEST_ASSERT(object().size() == 7);
   TEST_ASSERT(object().isValid());
 
   BondIterator localIter;
   int n = 0; 
   for (object().begin(localIter); !localIter.atEnd(); ++localIter) {
      ++n;
      //std::cout << localIter->id() << std::endl;
   }
   TEST_ASSERT(n == object().size());
   TEST_ASSERT(n == 7);

   object().remove(&bonds[1]);
   --n;
   TEST_ASSERT(object().isValid());
   TEST_ASSERT(n == object().size());
   TEST_ASSERT(n == 6);

}

inline void BondStorageTest::testFindBonds()
{
   printMethod(TEST_FUNC);

   DPArray<Bond> bonds;

   bonds.allocate(object().capacity());

   // Add bonds
   Bond* ptr53 = object().add(53); // 0
   Bond* ptr35 = object().add(35); // 1
   Bond* ptr18 = object().add(18); // 2
   Bond* ptr44 = object().add(44); // 3
   Bond* ptr17 = object().add(17); // 4
   Bond* ptr82 = object().add(82); // 5
   Bond* ptr39 = object().add(39); // 6

   bonds.append(*ptr53); // 0
   bonds.append(*ptr35); // 1
   bonds.append(*ptr18); // 2
   bonds.append(*ptr44); // 3
   bonds.append(*ptr17); // 4
   bonds.append(*ptr82); // 5
   bonds.append(*ptr39); // 6
  
   TEST_ASSERT(object().find(53) == ptr53);
   TEST_ASSERT(object().find(82) == ptr82);
   TEST_ASSERT(ptr53->id() == 53);
   TEST_ASSERT(object().find(54) == 0);
   object().remove(ptr82);
   TEST_ASSERT(object().find(53) == ptr53);
   TEST_ASSERT(object().find(18) == ptr18);
   TEST_ASSERT(object().find(44) == ptr44);
   TEST_ASSERT(object().find(17) == ptr17);
   TEST_ASSERT(object().find(82) == 0);
   TEST_ASSERT(object().find(83) == 0);

}

TEST_BEGIN(BondStorageTest)
TEST_ADD(BondStorageTest, testReadParam)
TEST_ADD(BondStorageTest, testAdd)
TEST_ADD(BondStorageTest, testAddRemove)
TEST_ADD(BondStorageTest, testIterator)
TEST_ADD(BondStorageTest, testFindBonds)
TEST_END(BondStorageTest)

#endif
