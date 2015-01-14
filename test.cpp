#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <cppunit/extensions/TypeInfoHelper.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include"test.h"
#include"p.h"

#include <iostream>
//testy jednostkowe

using namespace std;
//tworzymy obiekty klasy P
void poltest1::setUp(){
cout << "END Metoda  poltest1::setUp " << endl;
   p1 = new P("ljan:1:");				// po dwukropku kolejny token
   p2 = new P("ljan: I am in school");

}

// usuwanie obiektow klasy P 
void poltest1::tearDown(){
cout << "Metoda  poltest1::tearDown() " << endl;
 delete p1;
 delete p2;
cout << "Metoda poltest1::tearDown()" << endl;
}
//test jednostkowy, testuje metodê
void poltest1::testToken(){
  cout  << "Metod  poltest::testauthor() " << endl;
   p1->make_token();
  							 //wbudowane funkcje poprzez cpp unit assert testuj¹ce 
  CPPUNIT_ASSERT(p1->getSize_token()==2);
   CPPUNIT_ASSERT_MESSAGE( p1->token[0], p1->token[0]=="ljan");
  CPPUNIT_ASSERT_MESSAGE( p1->token[1], p1->token[1]=="1");

  
  cout << "END Metoda poltest::testauthor() " << endl;
}

//test jednostkowy sprawdzaj¹cy login
void poltest1::testIsRegistr() {
	p1->make_token();
	CPPUNIT_ASSERT(p1->isRegistr(p1->token[0])==1);
	
}

//test jednostkowy logowania i test wysy³ania wiadomoœci
void poltest1::testInsert() {
	p2->make_token();
	
	CPPUNIT_ASSERT(p1->getSize_token()==2);
	CPPUNIT_ASSERT(p2->insert_message()==0);
	
}

//Tworzenie mapy z hierarchia testow
CPPUNIT_REGISTRY_ADD( "pol1", "pol" );

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( poltest1, "pol1" );




