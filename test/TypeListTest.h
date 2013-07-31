// TypeListTest.cpp

#ifndef TYPELISTTEST_H
#define TYPELISTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class TypeListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TypeListTest );
    CPPUNIT_TEST(testSList);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testSList();
   //void test_$exception_func();
};
#endif
