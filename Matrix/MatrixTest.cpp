/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MatrixTest_init = false;
#include "MatrixTest.h"

static MatrixTest suite_MatrixTest;

static CxxTest::List Tests_MatrixTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MatrixTest( "MatrixTest.h", 6, "MatrixTest", suite_MatrixTest, Tests_MatrixTest );

static class TestDescription_suite_MatrixTest_testConstructors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testConstructors() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 8, "testConstructors" ) {}
 void runTest() { suite_MatrixTest.testConstructors(); }
} testDescription_suite_MatrixTest_testConstructors;

static class TestDescription_suite_MatrixTest_testInserts : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testInserts() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 29, "testInserts" ) {}
 void runTest() { suite_MatrixTest.testInserts(); }
} testDescription_suite_MatrixTest_testInserts;

static class TestDescription_suite_MatrixTest_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testMultiplication() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 51, "testMultiplication" ) {}
 void runTest() { suite_MatrixTest.testMultiplication(); }
} testDescription_suite_MatrixTest_testMultiplication;

static class TestDescription_suite_MatrixTest_testAdditionSubtraction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testAdditionSubtraction() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 74, "testAdditionSubtraction" ) {}
 void runTest() { suite_MatrixTest.testAdditionSubtraction(); }
} testDescription_suite_MatrixTest_testAdditionSubtraction;

static class TestDescription_suite_MatrixTest_testRemoveRowCol : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testRemoveRowCol() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 104, "testRemoveRowCol" ) {}
 void runTest() { suite_MatrixTest.testRemoveRowCol(); }
} testDescription_suite_MatrixTest_testRemoveRowCol;

static class TestDescription_suite_MatrixTest_testMoveFuncs : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testMoveFuncs() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 123, "testMoveFuncs" ) {}
 void runTest() { suite_MatrixTest.testMoveFuncs(); }
} testDescription_suite_MatrixTest_testMoveFuncs;

static class TestDescription_suite_MatrixTest_testInputStream : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testInputStream() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 149, "testInputStream" ) {}
 void runTest() { suite_MatrixTest.testInputStream(); }
} testDescription_suite_MatrixTest_testInputStream;

static class TestDescription_suite_MatrixTest_testInverseMatrix : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testInverseMatrix() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 181, "testInverseMatrix" ) {}
 void runTest() { suite_MatrixTest.testInverseMatrix(); }
} testDescription_suite_MatrixTest_testInverseMatrix;

static class TestDescription_suite_MatrixTest_testDeterminant : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testDeterminant() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 202, "testDeterminant" ) {}
 void runTest() { suite_MatrixTest.testDeterminant(); }
} testDescription_suite_MatrixTest_testDeterminant;

static class TestDescription_suite_MatrixTest_testIterators : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MatrixTest_testIterators() : CxxTest::RealTestDescription( Tests_MatrixTest, suiteDescription_MatrixTest, 216, "testIterators" ) {}
 void runTest() { suite_MatrixTest.testIterators(); }
} testDescription_suite_MatrixTest_testIterators;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
