/*
 * test.hpp
 *
 *  Created on: 05-03-2012
 *      Author: Pietia
 */

#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include "p.h"

class poltest1 : public CPPUNIT_NS::TestFixture{
	P *p1, *p2, *p3;
public:
	void setUp();
	void tearDown(); 
	
	void testToken();
	void testIsRegistr();
	void testInsert();
	
	CPPUNIT_TEST_SUITE(poltest1);
	CPPUNIT_TEST(testToken);
	CPPUNIT_TEST(testIsRegistr);
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST_SUITE_END();

};

#endif /* TEST_HPP_ */
