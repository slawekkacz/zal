#ifndef P_H
#define P_H

#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

#include <iostream>
#include <cstring>
#include <pqxx/pqxx> 

using namespace pqxx;
using namespace std;


//Klient i serwer wysy³aj¹ do siebie ci¹gi znaków.

class P {
	string pol;		 
	int size_token;	 //liczba tokenow
	
public:
    string token[100];				 
    //0- login
	
	P(string s);
	
	int make_token();
	int isRegistr(string s);


    int insert_message(); 
	int getSize_token();
	
	vector<string>* getHistory();
	
	
};

#endif
