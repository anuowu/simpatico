#ifndef MC_SIMULATION_TEST_H
#define MC_SIMULATION_TEST_H

#include <mcMd/mcSimulation/McSimulation.h>
#include <mcMd/mcSimulation/McSystem.h>
#include <mcMd/mdSimulation/MdSystem.h>
//#include <mcMd/mcSimulation/serialize.h>
#include <mcMd/species/Species.h>
#include <mcMd/chemistry/Molecule.h>
#include <mcMd/chemistry/Atom.h>
#include <mcMd/potentials/pair/McPairPotential.h>
#include <mcMd/potentials/bond/BondPotential.h>

#include <util/archives/MemoryCounter.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/TextFileOArchive.h>
#include <util/archives/TextFileIArchive.h>
#include <util/archives/BinaryFileOArchive.h>
#include <util/archives/BinaryFileIArchive.h>
#include <util/archives/Serializable_includes.h>

#include <test/ParamFileTest.h>
#include <test/UnitTestRunner.h>

#include <string>
#include <fstream>

using namespace Util;
using namespace McMd;

class McSimulationTest : public ParamFileTest<McSimulation>
{

public:

   McSimulationTest()
    : ParamFileTest<McSimulation>(),
      system_(object().system())
   { 
      // setVerbose(2); 
   }

   virtual void setUp()
   {
      object().fileMaster().setRootPrefix(filePrefix());
   } 

   virtual void readParam(McSimulation& sim)
   {  
      #ifdef MCMD_ANGLE
      openFile("in/McSimulationAngle"); 
      #else
      openFile("in/McSimulation"); 
      #endif
      //sim.setEcho();
      sim.readParam(file());
      std::cout << std::endl;
   }

   void testReadParam();
   void testPairEnergy();
   void testBondEnergy();
   #ifdef MCMD_ANGLE
   void testAngleEnergy();
   #endif
   void testMdSystemCopy();
   //void testMemorySerialize();
   //void testTextFileSerialize();
   //void testTextFileUnSerialize();
   void testSimulate();
   void testWriteRestart();
   void testReadRestart();

private:

   McSystem& system_;

};

void McSimulationTest::testReadParam()
{
   printMethod(TEST_FUNC);
   readParam(object());
   object().readCommands();

   try {
      object().isValid();
   } catch (Exception e) {
      std::cout << e.message();
      TEST_ASSERT(0);
   }

   if (verbose() > 1) {
      std::cout << std::endl;
      object().writeParam(std::cout);
   }

}


void McSimulationTest::testPairEnergy()
{ 
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   object().simulate(10);

   System::MoleculeIterator molIter;
   Molecule::AtomIterator   atomIter;
   double energy, de;

   energy = 0.0;
   for (int is=0; is < object().nSpecies(); ++is) {
      for (system_.begin(is, molIter); molIter.notEnd(); ++molIter) {
         for (molIter->begin(atomIter); atomIter.notEnd(); ++atomIter) {
            de = system_.pairPotential().atomEnergy(*atomIter);
            std::cout.width(5);
            std::cout << atomIter->id() << "     " << de << std::endl;
            energy += de;
         }
      }
   }
   std::cout << "Total atomPairEnergy = " << 0.5*energy << std::endl;
   std::cout << "TotalPairEnergy      = " << system_.pairPotential().energy() << std::endl;

}

void McSimulationTest::testBondEnergy()
{ 
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   object().simulate(10);

   System::MoleculeIterator molIter;
   Molecule::AtomIterator   atomIter;
   double                   energy, de;

   energy = 0.0;
   for (int is=0; is < object().nSpecies(); ++is) {
      for (system_.begin(is, molIter); molIter.notEnd(); ++molIter) {
         for (molIter->begin(atomIter); atomIter.notEnd(); ++atomIter) {
            de = system_.bondPotential().atomEnergy(*atomIter);
            std::cout.width(5);
            std::cout << atomIter->id() << "     " << de << std::endl;
            energy += de;
         }
      }
   }
   std::cout << "Total atomBondEnergy = " << 0.5*energy << std::endl;
   std::cout << "TotalBondEnergy      = " << system_.bondPotential().energy() << std::endl;
}

#ifdef MCMD_ANGLE
void McSimulationTest::testAngleEnergy()
{ 
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   object().simulate(10);

   System::MoleculeIterator molIter;
   Molecule::AtomIterator   atomIter;
   double                   energy, de;

   energy = 0.0;
   for (int is=0; is < object().nSpecies(); ++is) {
      for (system_.begin(is, molIter); molIter.notEnd(); ++molIter) {
         for (molIter->begin(atomIter); atomIter.notEnd(); ++atomIter) {
            de = system_.atomAngleEnergy(*atomIter);
            std::cout.width(5);
            std::cout << atomIter->id() << "     " << de << std::endl;
            energy += de;
         }
      }
   }
   std::cout << "Total atomAngleEnergy = " << energy/3.0 << std::endl;
   std::cout << "TotalAngleEnergy      = " << system_.angleEnergy() << std::endl;
}
#endif

void McSimulationTest::testMdSystemCopy()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   object().simulate(10);

   MdSystem mdSystem(system_);

   std::ifstream mdSystemFile;
   openInputFile("in/MdSystemCopy", mdSystemFile); 

   mdSystem.readParam(mdSystemFile);

   std::cout << "MC Potential Energy      = " 
             << system_.potentialEnergy() << std::endl;
   std::cout << "MD Potential Energy      = " 
             << mdSystem.potentialEnergy() << std::endl;

   mdSystemFile.close(); 

}

#if 0
void McSimulationTest::testMemorySerialize()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   //object().simulate(10);

   MemoryCounter car;
   car << object();
   int size = car.size();

   MemoryOArchive oar;
   oar.allocate(size);
   oar << object();

   MemoryIArchive iar;
   iar = oar;

   std::cout << "Iar size = " << (size_t) (iar.end() - iar.begin()) << std::endl;

   McSimulation    clone;
   iar >> clone;

   clone.writeParam(std::cout);
}

void McSimulationTest::testTextFileSerialize()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   readParam(object());
   object().readCommands();

   TextFileOArchive oar;
   std::ofstream out;
   openOutputFile("text", out);
   oar.setStream(out);

   oar << object();
   out.close();

}

void McSimulationTest::testTextFileUnSerialize()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   TextFileIArchive iar;
   std::ifstream in;
   openInputFile("text", in); 
   iar.setStream(in);

   iar >> object();

   object().writeParam(std::cout);
   object().simulate(100);
}
#endif

void McSimulationTest::testSimulate()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   openFile("in/McSimulation"); 
   object().readParam(file());
   object().readCommands();

   std::cout << std::endl;

   std::string baseFileName("simulate.0");
   object().writeRestart(baseFileName);

   object().simulate(20);

   baseFileName = "simulate.20";
   object().writeRestart(baseFileName);

}

void McSimulationTest::testWriteRestart()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   openFile("in/McSimulation"); 
   object().readParam(file());
   object().readCommands();

   std::cout << std::endl;

   std::string baseFileName("writeRestart.0");
   object().writeRestart(baseFileName);

   object().simulate(10);
   baseFileName = "writeRestart.10";
   object().writeRestart(baseFileName);

   bool isContinuation = true;
   object().simulate(20, isContinuation);
   baseFileName = "writeRestart.20";
   object().writeRestart(baseFileName);
}

void McSimulationTest::testReadRestart()
{
   printMethod(TEST_FUNC);
   std::cout << std::endl;

   std::string baseFileName("writeRestart.10");
   object().readRestart(baseFileName);

   baseFileName = "readRestart";
   object().writeRestart(baseFileName);
}
TEST_BEGIN(McSimulationTest)
TEST_ADD(McSimulationTest, testReadParam)
TEST_ADD(McSimulationTest, testPairEnergy)
TEST_ADD(McSimulationTest, testBondEnergy)
#ifdef MCMD_ANGLE
TEST_ADD(McSimulationTest, testAngleEnergy)
#endif
TEST_ADD(McSimulationTest, testMdSystemCopy)
//TEST_ADD(McSimulationTest, testMemorySerialize)
//TEST_ADD(McSimulationTest, testTextFileSerialize)
//TEST_ADD(McSimulationTest, testTextFileUnSerialize)
TEST_ADD(McSimulationTest, testSimulate)
TEST_ADD(McSimulationTest, testWriteRestart)
TEST_ADD(McSimulationTest, testReadRestart)
TEST_END(McSimulationTest)

#endif