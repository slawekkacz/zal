#include<pthread.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<string.h>
#include<iostream>

//nasłuch na informacje od serwera. serwer -> klient
void *th(void *fd)
{
	int x,n,i=0;
	char buff[400];

//	pthread_detach(pthread_self());
	

	while((n=read((int)fd,buff,400))>0)
	{
                    
		printf("SERWER SEND %d char  :    %s\n",n,buff);
		buff[399]='\0';
	}
	close((int)fd);
	pthread_exit(NULL);
}

int main(int argc,char *argv[]){
	
printf("Program start\n");
//metadane użytkownika
	char buff[200];
	char log[400];
	char command[40];
	int fd,n,j;
	pthread_t t;
	struct sockaddr_in srvaddr;
	struct hostent *hst;	
//podaje dane serwera
	if (argc!=2) {printf("Podaj nazwe hosta\n");_exit(0);}

	bzero(&srvaddr,sizeof(srvaddr));
	
	hst=gethostbyname(argv[1]);
	
	memcpy(&srvaddr.sin_addr,(*hst).h_addr_list[0],4);
	srvaddr.sin_port=htons(51511);
	srvaddr.sin_family=AF_INET;
	
	fd=socket(AF_INET,SOCK_STREAM,0);
	connect(fd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));
	
	pthread_create(&t,NULL,th,(void*)fd);
//logowanie użytkownika do czata
	printf("podaj login:\n");
	fgets(log,sizeof(log),stdin);
	j=strlen(log);
	log[j-1]=':';
	log[j]='\0';
	command[0]='1';
	command[1]=':';
	command[2]='\0';
	strcat(log,command);
	n=strlen(log);
	write(fd,log,n);
	log[j]='\0';
//Program klienta czeka na wypisanie tekstu
	while(1)
	{
		fgets(buff,sizeof(buff),stdin);
		n=strlen(buff);
		buff[n-1]='\0';
                if (strcmp("exit",buff)==0) { printf("EXIT while");   break;} else  { printf("\nBUFFOR: _%s_\n", buff);  }
		strcat(log,buff);
               
		n=strlen(log);
		write(fd,log,n);	//wysłanie do serwera
//	     printf("write %s , %d  \n", log, n);	
	 	log[j]='\0';
//	     printf("\nEND while %s\n ", log);	
	}
printf("program Klient stop\n");
return 0;
}
