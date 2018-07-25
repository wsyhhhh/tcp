#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<iostream>
using namespace std;
#define MAXLINE 4096

int main(int argc,char** argv){
     int listen_fd,conn_fd;
     struct sockaddr_in servaddr;
     char buff[4096];
     int n;

     if((listen_fd=socket(AF_INET,SOCK_STREAM,0))<0){
          cout<<"create socket error: "<<strerror(errno)<<" errno:  "<<errno<<endl;
          return -1;
     }
     
     memset(&servaddr,0,sizeof(servaddr));
     servaddr.sin_family=AF_INET;
     servaddr.sin_port=htons(6666);
     servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

     int on=1;	
     if(setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int))<0){
	cout<<"setsocket err: "<<strerror(errno)<<" error: "<<errno<<endl;
	return -1;
     }
     
     if(bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
	   cout<<"bind error: "<<strerror(errno)<<" errno: "<<errno<<endl;
           return -2;
     }
     
     if(listen(listen_fd,10)==-1){
   	cout<<"listen socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	return -3;
     } 
     cout<<"waiting for clients request"<<endl;
     while(1){
  	if((conn_fd=accept(listen_fd,(struct  sockaddr*)NULL,NULL))==-1){
		cout<<"connect socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		continue;
        }
	n=recv(conn_fd,buff,MAXLINE,0);
        buff[n]='\0';
	cout<<"receive msg from client: "<<buff<<endl;
	close(conn_fd);
     }
     close(listen_fd);
     return 0;
}
