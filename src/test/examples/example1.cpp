#include "UnitTest.h"
#include "UnitTestRunner.h"
#include <iostream>

/**
* This example shows how to construct and run a single UnitTest class.
*
* We create a subclass of UnitTest named TestA, which has 3 test methods.
* We then use a set of preprocessor macros to define an associated subclass
* of UnitTestRunner. The name of the UnitTestRunner subclass is given by
* the macro TEST_RUNNER(TestA), which expands to TestA_Runner. Finally, In 
* the main program, we create an instance of TEST_RUNNER(TestA) and call 
* its run method to run all 3 test methods.
*/

/**
* Trivial subclass of UnitTest, for illustration.
*/
class TestA : public UnitTest
{

public:

   void test1() { 
      printMethod(TEST_FUNC);
      TEST_ASSERT(eq(1,2));
   }

   void test2() { 
      printMethod(TEST_FUNC);
      TEST_ASSERT(false);
   }

   void test3() { 
      printMethod(TEST_FUNC); 
      TEST_ASSERT(3 == 3);
   }

};

/*
* Preprocessor macros to define an associated UnitTestRunner.
*/
TEST_BEGIN(TestA)
TEST_ADD(TestA, test1)
TEST_ADD(TestA, test2)
TEST_ADD(TestA, test3)
TEST_END(TestA)

/*
* The above sequence of macros expand into the following code:
*
* class TestA_Runner : public UnitTestRunner<TestA> {
* public:
*
*   TestA_Runner() {
*      addTestMethod(&TestA::test1);
*      addTestMethod(&TestA::test2);
*   }
*
* };
*/

int main() 
{ 
   TEST_RUNNER(TestA) test;
   test.run();
}
