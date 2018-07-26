#include<iostream>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXLINE 4096
using namespace std;
int main(int argc,char **argv){
	int listenfd, acceptfd;
	struct sockaddr_in servaddr;
	
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"create socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(6666);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
		cout<<"bind error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	
	if(listen(listenfd,10)==-1){
		cout<<"listen error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	cout<<"waiting for client's request"<<endl;
	while(1){
		if((acceptfd=accept(listenfd,(struct sockaddr*)NULL,NULL))==-1){
			cout<<"accept error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		}
		char recvmsg[100];
		ssize_t readlen=read(acceptfd,recvmsg,sizeof(recvmsg));
		if(readlen<0){
			cout<<"read error: "<<strerror(errno)<<" errno: "<<errno<<endl;
			return 0;
		}
		recvmsg[9]='\0';
		cout<<"read msg: "<<readlen<<" "<<recvmsg<<endl;
		sleep(5);
		recvmsg[1]='9';
		ssize_t writelen=write(acceptfd,recvmsg,sizeof(recvmsg));
		
		if(writelen<0){
			cout<<"write error: "<<strerror(errno)<<" errno: "<<errno<<endl;
			return 0;
		}
		cout<<"write msg: "<<writelen<<" "<<recvmsg<<endl;
		close(acceptfd);
	
	}
	close(listenfd);
	return 0;
}
