#ifndef P_CPP
#define P_CPP

#include "p.h"


#include <iostream>
#include <cstring>
#include <pqxx/pqxx> 

using namespace pqxx;
using namespace std;
//S³u¿y do obs³ugi bazy

//pol ca³y przes³any string znaków
P::P(string p): pol(p), size_token(0) {
	if(0 == p.size()) {
		token[0]="dsgsdgsdfsd";
		size_token=0;
	} else {
		make_token();
    }	
	
}
//ciÄ…g znakÃ³w zamienia na tablice
//tworzy tokeny -czyli dzieli string na 3 czêœci
int P::make_token() {
	char * cstr = new char [pol.length()+1];
     std::strcpy (cstr, pol.c_str());	   //kopiowanie POL do tablica znaków

	      	 
		  char * p = std::strtok (cstr,":");	
		  this->size_token=0;
		  while (p!=0)
		  {
		       
			token[size_token]=p;
			size_token++;
			p = strtok(NULL,":");
		  }
             
	return 1;
}

//liczy tokeny
int P::getSize_token() {
	return size_token;
}

//sprawdzy czy jest zarejestrowany LOGIN
int P::isRegistr(string login) {

 string  sql="SELECT * from dwh.user where login='"+login+"'" ;
//  cout <<  sql << endl;


    try{

       connection C("dbname=dwh user=postgres password=dwh \
       hostaddr=127.0.0.1 port=5432");

       if (C.is_open()) {
      //    cout << "Opened database successfully: " << C.dbname() << endl;
       } else {
       //   cout << "Can't open database" << endl;
          return -1;
       }
 
       nontransaction N(C);
       /// Execute SQL query 
       result R( N.exec( sql.c_str() ));

       C.disconnect ();
       if ( R.size()==1) { return 1 ; } 
       else if (R.size()==0) {return 2;} 
       else if  (R.size()>1) {return 3;} 

    }catch (const std::exception &e){
       cerr << e.what() << std::endl;
       return -2;
    }    

return 1;
}

int P::insert_message() {
	//zapis wiadomoœci do bazy
	string sql ="insert into dwh.message  (id_user,message)  select u.id, '"+
	this->token[1]+
	"' from dwh.user u  where u.login='"+this->token[0]+"'";
	
	
	try{
      connection C("dbname=dwh user=dwh password=dwh \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
     //    cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
    //     cout << "Can't open database" << endl;
         return 1;
      }
    
      work W(C);
      W.exec( sql );
      W.commit();
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
	
}

vector<string>* P::getHistory() {
//select u.login, m.message from dwh.message m join dwh.user u on u.id=m.id_user where u.login='ljan';
	vector<string>* v=new vector<string>();
	
	return v;
}
#endif

