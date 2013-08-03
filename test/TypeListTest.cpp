
#include <cppunit/config/SourcePrefix.h>
#include "TypeListTest.h"
#include <string>
#include "../src/Typelist.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TypeListTest );
// helper functions
using namespace std;
using namespace Loki;
using namespace Loki::TL;


void 
TypeListTest::setUp()
{
}


void 
TypeListTest::tearDown()
{
}

void TypeListTest::testDerivation(){
	class Base{};
	class Middle:public Base{};
	class Bottom:public Middle{};

	typedef TYPELIST_3(Base, Middle, Bottom) type_3;
	//the below type_3 can not pass compile
    //typedef TYPELIST_3(Base, Middle, Middle) type_3;
	Bottom b = MostDerived<type_3, Base>::Result();

	typedef TYPELIST_3(Bottom, Middle, Base) df_type_3;
	df_type_3 d = DerivedToFront<type_3>::Result();
}

void TypeListTest::testBasicOp(){
	// Length<TypeList>
	typedef TYPELIST_2(string, string) type_2;
	typedef TYPELIST_4(int, int, string, string) type_4;
	CPPUNIT_ASSERT_EQUAL(int(Length<type_4>::value), 4);

	//TypeAt<TypeList, unsigned int>
	int i = typename TypeAt<type_4, 0>::Result();
	string s = typename TypeAt<type_4, 2>::Result();

	//IndexOf<TList, T>::value
	CPPUNIT_ASSERT_EQUAL(int(IndexOf<type_4, int>::value), 0);
	CPPUNIT_ASSERT_EQUAL(int(IndexOf<type_4, string>::value), 2);
	CPPUNIT_ASSERT_EQUAL(int(IndexOf<type_4, double>::value), -1);

	//Append<TList, T>
	typedef typename Append<type_4, double>::Result type_5;
	CPPUNIT_ASSERT_EQUAL(int(Length<type_5>::value), 5);
	double d = typename TypeAt<type_5, 4>::Result();

	//Erase<TList, T>, invariant, Erase is inverse op of append when erase at the end.
	//type_4 t4 = typename Erase<type_5, int>::Result(); can't compile
	type_4 t4 = typename Erase<type_5, double>::Result();

	//EraseAll<TList, T>
	type_2 t2 = typename EraseAll<type_4, int>::Result();	
	//type_2 t2 = typename EraseAll<type_4, string>::Result();	
	
	//Replace, ReplaceAll, Reverse
	typedef typename ReplaceAll<type_4, int, string>::Result t4_string;
	CPPUNIT_ASSERT_EQUAL(int(Length<t4_string>::value), 4);
	typedef typename Reverse< 
		Replace<typename Replace<t4_string, string, int>::Result,
		 string, int>::Result >::Result rtype_4;
	//type_4 tt4 = rtype_4();
	type_4 tt4 = typename Reverse<rtype_4>::Result();

}
