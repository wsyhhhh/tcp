#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define maxline 4096

using namespace std;
int main(int argc,char **argv){
    int socket_fd,n;
    char recvline[4096],sendline[4096];
    struct sockaddr_in servaddr;

    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0){
       cout<<"create socket error"<<endl;
       return -1;
    }
  
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(6666);
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){
         cout<<"inet_pton error"<<endl;
         return -2;
    }
    
    if(connect(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
         cout<<"connect error: "<<strerror(errno)<<" errno: "<<errno<<endl;
         return -3;
    }

    cout<<"send msg to server: "<<endl;
    fgets(sendline,4096,stdin);
    if(send(socket_fd,sendline,strlen(sendline),0)<0){
         cout<<"send error: "<<strerror(errno)<<" errno: "<<errno<<endl;
         return -4;
    }
    close(socket_fd);
    return 0;
}
