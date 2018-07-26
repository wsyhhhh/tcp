#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#define MAXLINE 4096
using namespace std;
int main(int argc,char** argv){
    int sockfd;
    struct sockaddr_in servaddr;
    char recvbuf[4096],sendbuf[4096];

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
	cout<<"create socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	return -1; 
    }

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(6666);
    if((inet_pton(AF_INET,argv[1],&servaddr.sin_addr))<=0){
	cout<<"inet_pton error: "<<argv[1]<<endl;
	return -2;
    }

    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
	cout<<"connect error: "<<strerror(errno)<<" errno: "<<errno<<endl;
    	return -3;
	}
    struct timeval sttime;
    sttime.tv_sec=2;
    sttime.tv_usec=0;
    if(setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&sttime,sizeof(sttime))){
	cout<<"setsockopt error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	return -4;
	}
    if(setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&sttime,sizeof(sttime))){
	cout<<"setsockopt error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	return -5;
	}
    ssize_t writeLen;
    char sendmsg[10]={'0','1','2','3','4','5','6','7','8','\0'};
    int count=0;
    writeLen=write(sockfd,sendmsg,sizeof(sendmsg));
    if(writeLen<0){
	cout<<"write error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	close(sockfd);
	return 0;
	}
    else{
	cout<<"write success: "<<writeLen<<" "<<sendmsg<<endl;
	}
    char readmsg[10]={0};
    ssize_t readlen=read(sockfd,readmsg,sizeof(readmsg));
    if(readlen<0){
	cout<<"read error: "<<strerror(errno)<<" errno: "<<errno<<endl;
	close(sockfd);
	return 0;
	}
    else{
	readmsg[9]='\0';
	cout<<"read success: "<<readlen<<" "<<readmsg<<endl;
	}
    close(sockfd);
   return 0;

}
