#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;
int main(int argc,char** argv){
	int listenfd,acceptfd;
	struct sockaddr_in servadd;

	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"create socket error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	memset(&servadd,0,sizeof(servadd));
	servadd.sin_family=AF_INET;
	servadd.sin_port=htons(6666);
	servadd.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(listenfd,(struct sockaddr*)&servadd,sizeof(servadd))==-1){
		cout<<"bind error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}

	if(listen(listenfd,10)==-1){
		cout<<"listen error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	cout<<"waiting for client's request:"<<endl;
	if((acceptfd=accept(listenfd,(struct sockaddr *)NULL,NULL))==-1){
		cout<<"accept error: "<<strerror(errno)<<" errno: "<<errno<<endl;
		return 0;
	}
	else{
		cout<<"accept success"<<endl;
		int rcvbuf_len=87380;
		socklen_t len=sizeof(rcvbuf_len);
		if(setsockopt(acceptfd,SOL_SOCKET,SO_RCVBUF,(const char *)&rcvbuf_len,sizeof(int))<0)
			cout<<"set read buf error"<<endl;
		if(getsockopt(acceptfd,SOL_SOCKET,SO_RCVBUF,(void*)&rcvbuf_len,&len)<0)
			cout<<"getsockopt error"<<endl;
		cout<<"the recv buf len: "<<rcvbuf_len<<endl;
	}	
	char recvmsg[246988]={0};
	ssize_t totallen=0;
	while(1){
		sleep(1);
		ssize_t readlen=read(acceptfd,recvmsg,sizeof(recvmsg));
		cout<<"readlen: "<<readlen<<endl;
		if(readlen<0){
			cout<<"read error"<<endl;
			return -1;
		}
		else if(readlen==0){
			cout<<"read finish: len="<<totallen<<endl;
			close(acceptfd);
			return 0;
		}
		else
			totallen+=readlen;
	}
	close(acceptfd);
	return 0;
}
