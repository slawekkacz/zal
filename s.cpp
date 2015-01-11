#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <cstring>

#include <arpa/inet.h>
#include <fstream>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Configurator.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/SimpleLayout.hh>


#include <pqxx/pqxx> 
#include "p.h"

using namespace std;
using namespace pqxx;
using namespace log4cpp;
int desc[100];
//Odpowiada za obsługę klienta:
//odbiera ciąg znaków


//zapis logów do pliku
ofstream logfile("./logi");
OstreamAppender *a1=new OstreamAppender("Appender",&logfile);
//wypisanie logów na ekran
OstreamAppender *a2=new OstreamAppender("Appender",&cout);
 
//tworzenie hierarchii - umożliwia zapis do pliku jednocześnie wypisując na ekran. Np: error pokaże wiadomość na standard
//owym wyjściu i informacje zostaną zapisane do pliku.
Category& root=Category::getRoot(); 
Category& category = Category::getInstance("Server");
Category& category2= Category::getInstance("Server.Subcat");

// Funkcja umożliwia połączenie użytkownika z serwerem. 
void *th(void *fd) //fd to nowy wątek
{

//wypisuje na erkan metadane nowego użytkownika, socket to numer systemowy nowego użytkownika
category.info("FUNCTION NEW CONNECT ON SOCKET: %d",(int) fd );
logfile.flush();
	int x,i=0;
        unsigned int n=0;
	char buff[400];
	char cstr[400];
	std::string token[3];
	int size_token;

        P* pol;
	struct sockaddr_in  SenderInfo;
	pthread_detach(pthread_self());
	

	
 category.info("---CREATE USER---\n"); fflush(stdout);	//tworzony nowy użytkownik w serwerze, czyli połączenie nowego użytkownika na serwerze

	while(desc[i++]);
	desc[i-1]=(int)fd;


/////////////////////////////// logowanie //////////////////////////////


//Próba logowania do serwera. 
if((n=read((int)fd,buff,400))>0) { //serwer oczekuje na przesłanie ciągu znaków
//wypisanie na serwerze informacji o kliencie
memset(&SenderInfo, 0, sizeof(SenderInfo));
getpeername((int) fd, (struct sockaddr *)&SenderInfo, &n);
category.info("Server: IP used by Client: %s, socket %d \n", inet_ntoa(SenderInfo.sin_addr), (int) fd);
root.info("Server: Port used by Client: %d\n", htons(SenderInfo.sin_port));
root.info("Server: Bytes received: %d\n", n);
root.info("Server: Sending: %s\n", buff);  //to wszystko zapisuje się do logów


//próba zalogowania się na czata
	  std::strcpy(cstr,buff);	

           pol=   new P(cstr);		  //POL cały ciąg znaków
          pol->isRegistr(pol->token[0]);	   //sprawdza czy jest taki login w bazie
        //  cout << pol->token[0] << endl;
           if (pol->isRegistr(pol->token[0]) !=1) {
			   
		           category.warn("Nie udane logowanie %s",buff);	
			   write((int)fd,"You not log ini, connect is close.",100);
		  } else {	  
         
			// informacja o dołączeniu użytkowika
                           category.info(("Login in: " + pol->token[0]).c_str(),100); //jeśli jest taki użytkownik w bazie to wypisuje dane nowego połączenia do logów
		    for(i=0;i<100;i++)						 //pisanie do wszystkich zalogowanych użytkowników
			  if (desc[i]!=0)
			  write(desc[i],("Login in: " + pol->token[0]).c_str(),100);
	            i=0;  

			

                  
		// wysyłanie wiadomości
		while((n=read((int)fd,buff,400))>0) //nasłuchuje czy użytkownik wysyła wiadomości
		{

			memset(&SenderInfo, 0, sizeof(SenderInfo));
			getpeername((int) fd, (struct sockaddr *)&SenderInfo, &n);
			category.info("Server: IP used by Client: %s, socket %d \n", inet_ntoa(SenderInfo.sin_addr), (int) fd);
			root.info("Server: Port used by Client: %d\n", htons(SenderInfo.sin_port));
			root.info("Server: Bytes received: %d\n", n);
			root.info("Server: Sending: %s\n", buff);	  //zapis do logów metadanych o wysłanej wiadomości

			
			  std::strcpy(cstr,buff);	

			   pol=   new P(cstr);
			  pol->isRegistr(pol->token[0]);
			   if (pol->isRegistr(pol->token[0]) !=1) { 
					   category.fatal("Kod 12 ");
					   write((int)fd,"Cric error: not  nformation on loin ",100);
					   break;
				  } else {	  
			 
				    for(i=0;i<100;i++)
					  if (desc[i]!=0)
					  write(desc[i],buff,n); //użytkownik wysyła wiadomość do wszystkich.
				i=0;
			      }
		} // wile to sendig information



	      }
   }




//wyczyszczenie nieaktywnych użytkowników - informacje nie będą do nich dochodziły.
 category.info("---CLEAN USER---\n");
  fflush(stdout);
    i=0;
	while(desc[i++]!=(int)fd);
	desc[i-1]=0;
	close((int)fd);
  fflush(stdout);

category.info("FUNCTION DISCONNECT ON SOCKET: %d",(int) fd );


logfile.flush();
	pthread_exit(NULL);

}


int main()
{
// Ustawienia graficzne dla logów
    PatternLayout *layout1=new PatternLayout();

        const char *format="%r [%d] %p %c %x - %m%n"; //recznie definiowany format, zobacz dokumentacje PatternLayout
        layout1->setConversionPattern(format);

        Layout *layout2=new SimpleLayout();

        a1->setLayout(layout1);
        a2->setLayout(layout2);

        root.setAppender(a1);
        root.setPriority(Priority::DEBUG);
        category.setPriority(Priority::INFO);
       
        root.setAppender(a1);
        category.addAppender(a2);

        // root.info("info root");
        //category.fatal("category fatal");
        

	  logfile.flush();
//uruchamianie serwera

category.info("Program Server run\n");
	int fa,frw,o;
        socklen_t client_size;
	struct sockaddr_in sock, cli_addr, SenderInfo;
	pthread_t t;
	o=1;
	 char recvbuff[1024];
	bzero(desc,400);
	fa=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&sock,sizeof(sock));
	
	sock.sin_family=AF_INET;
	sock.sin_addr.s_addr=INADDR_ANY;
	sock.sin_port=htons(51511);
	
	setsockopt(fa,SOL_SOCKET,SO_REUSEADDR,&o,sizeof(o));

	bind(fa,(struct sockaddr*)&sock,sizeof(sock));
	
	listen(fa,10);
	client_size = sizeof(cli_addr);
	string str;
// nasłuch czy jest nowy użytkownik do zalogowania, uruchamia funkcję th. Tworzenie nowego wątku dla nowego użytkownika.
	while(1)
	{


	root.info("--while Start --\n"); logfile.flush();

		frw=accept(fa,NULL,NULL);

	category.info("--start phread_create --\n"); logfile.flush();
		pthread_create(&t,NULL,th,(void*)frw);
	root.info("--while Koniec --\n"); fflush(stdout);
	}

category.info("Server  stop run");
logfile.flush();
} // end main program 


