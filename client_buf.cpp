#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
using namespace std;
int main(int argc,char** argv){
	int sockfd;
	struct sockaddr_in servadd;

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"create socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}

	memset(&servadd,0,sizeof(servadd));
	servadd.sin_family=AF_INET;
	servadd.sin_port=htons(6666);
	if(inet_pton(AF_INET,argv[1],&servadd.sin_addr)==-1){
		cout<<"inet_pton error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	
	if(connect(sockfd,(struct sockaddr*)&servadd,sizeof(servadd))==-1){
		cout<<"connect error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}

	ssize_t writelen;
	char senmsg[246988]={0};
	int count=0;
	while(1){
		count++;
		if(count==5)
			return 0;
		writelen=write(sockfd,senmsg,sizeof(senmsg));
		if(writelen<0){
			cout<<"write failed"<<endl;
			close(sockfd);
			return 0;
		}
		else
			cout<<"write success "<<writelen<<endl;
	
	}
	close(sockfd);
	return 0;
}	
